#include <kernel.h>
#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <canbus/canopen.h>


#define LOG_LEVEL CONFIG_CANOPEN_LOG_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(gpios);

// #define GPIO_INPUT_INT_EDGE (GPIO_INT_EDGE_BOTH | GPIO_INPUT)

struct gpio_conf {
    const uint16_t index;
	const struct device *dev;
	OD_configPort_t *od_conf;
    uint16_t* od_out; 
    uint16_t* od_inp; 
    uint16_t old_out;
    struct gpio_callback input_gpio_callback;
    struct k_work work;
};



static struct gpio_conf gpios[] = {
    {
        .index = 0x2002,
        .od_conf = &OD_configPort[0],
        .od_out = &OD_writeOutput16Bit[0],
        .od_inp = &OD_readInput16Bit[0],
    },
    {
        .index = 0x2003,
        .od_conf = &OD_configPort[1],
        .od_out = &OD_writeOutput16Bit[1],
        .od_inp = &OD_readInput16Bit[1],
    },
    {
        .index = 0x2004,
        .od_conf = &OD_configPort[2],
        .od_out = &OD_writeOutput16Bit[2],
        .od_inp = &OD_readInput16Bit[2],
    },
};

// 10000001 00000000    PA15 PA8
// 11110000 11111000    PB5-3v only
// 11000000 00000000    PC15-3v PC14-3v
// BBBBAACC BBBBB000 - pack gpios
static uint16_t abc_to_pack(uint16_t a,uint16_t b, uint16_t c)
{
    return (b & 0xF0F8) | ((c>>6) & 0x0300) | ((a<<2) & 0x0400) | ((a>>4) & 0x0800);
}
static void pack_to_abc(uint16_t pack, uint16_t* a,uint16_t* b, uint16_t* c)
{
    *b = pack & 0xF0F8;
    *c = (pack & 0x0300) << 6;
    *a = ((pack>>2) & 0x0100) | ((pack<<4) & 0x8000);
}
static inline void update_pack_iomask(void)
{
    uint16_t ma = gpios[0].od_conf->inputMask;
    uint16_t mb = gpios[1].od_conf->inputMask;
    uint16_t mc = gpios[2].od_conf->inputMask;
    OD_GPIOPack.inputMask = abc_to_pack(ma,mb,mc);
    LOG_INF("OD_GPIOPack.inputMask %x", OD_GPIOPack.inputMask);
    ma = gpios[0].od_conf->outputMask;
    mb = gpios[1].od_conf->outputMask;
    mc = gpios[2].od_conf->outputMask;
    OD_GPIOPack.outputMask = abc_to_pack(ma,mb,mc);
    LOG_INF("OD_GPIOPack.outputMask %x", OD_GPIOPack.outputMask);
}

static inline void update_pack_State(void)
{
    uint16_t a = *gpios[0].od_inp;
    uint16_t b = *gpios[1].od_inp;
    uint16_t c = *gpios[2].od_inp;
    OD_GPIOPack.state = abc_to_pack(a,b,c);
}

static void gpio_input_isr_callback(const struct device *port,
				struct gpio_callback *cb,
				uint32_t pins)
{
    struct gpio_conf* conf = CONTAINER_OF(cb, struct gpio_conf, input_gpio_callback);
 	k_work_submit(&conf->work);
}

static void gpio_input_work(struct k_work *item)
{
    struct gpio_conf *conf = CONTAINER_OF(item, struct gpio_conf, work);
    gpio_port_value_t v;
    gpio_port_get_raw(conf->dev, &v);
    CO_LOCK_OD();
    *conf->od_inp = (conf->od_conf->inputMask | conf->od_conf->outputMask) & v; // all input and output physical pin state
    CO_UNLOCK_OD();
    update_pack_State();
    // LOG_INF("Update input");
}    

static CO_SDO_abortCode_t odf_2080_GPIO_pack(CO_ODF_arg_t *odf_arg)
{
    if (!odf_arg->reading && (odf_arg->subIndex == 4)) 
    {
        if (OD_GPIOPack.setReset)
        {
            uint16_t pin[3];

            uint16_t set = OD_GPIOPack.setReset;

            if (set)
            {
                pack_to_abc(set, &pin[0], &pin[1], &pin[2]);
                for (size_t i = 0; i < 3; i++)
                {
                    if (pin[i])
                    {
                       gpio_port_set_bits_raw(gpios[i].dev, pin[i]); 
                       k_work_submit(&gpios[i].work);
                    }
                }
            }
            else 
            {
                uint16_t res = OD_GPIOPack.setReset >> 16;
                pack_to_abc(res, &pin[0], &pin[1], &pin[2]);
                for (size_t i = 0; i < 3; i++)
                {
                    if (pin[i])
                    {
                       gpio_port_clear_bits_raw(gpios[i].dev, pin[i]); 
                       k_work_submit(&gpios[i].work);
                    }
                }
            }
            CO_LOCK_OD();
            OD_GPIOPack.setReset = 0;
            CO_UNLOCK_OD();
        }
    }
    return CO_SDO_AB_NONE;    
}


static bool FlagUpdateODF;

static CO_SDO_abortCode_t odf_setup(CO_ODF_arg_t *odf_arg)
{
    struct gpio_conf *conf = odf_arg->object;

    if (odf_arg->reading) return CO_SDO_AB_NONE;

    uint16_t data = CO_getUint16(odf_arg->data);

    if (data & ~conf->od_conf->availableMask) return CO_SDO_AB_INVALID_VALUE;

    switch(odf_arg->subIndex) {
        case 2:
        /* Output Mask*/
          if (data & conf->od_conf->inputMask)
          {
              CO_LOCK_OD();
              conf->od_conf->inputMask &= ~data;
              CO_UNLOCK_OD();
          }
        break;
        case 3:
        /* Output Start Value*/
         if (data & ~conf->od_conf->outputMask) return CO_SDO_AB_INVALID_VALUE;        
        break;
        case 4:
        /* Input Mask*/
          if (data & conf->od_conf->outputMask)
          {
              CO_LOCK_OD();
              conf->od_conf->outputMask &= ~data;
              CO_UNLOCK_OD();
          }
        break;
        case 5:
        case 6:
        /* Input PullUp PullDown */
         if (data & ~conf->od_conf->inputMask) return CO_SDO_AB_INVALID_VALUE;        
        break;
        default: return CO_SDO_AB_READONLY;
    }
    FlagUpdateODF = true;
    return CO_SDO_AB_NONE;
}

static const struct device* gpio_init(struct gpio_conf *conf)
{
    conf->dev = device_get_binding(conf->od_conf->port);

    if (conf->dev)
    {
        for (gpio_pin_t pin = 0; pin < 16; pin++)
        {
            gpio_flags_t f;
            uint16_t mask = BIT(pin);   

            if (conf->od_conf->availableMask & mask)
            {
                if (conf->od_conf->outputMask & mask)    
                {
                    f = (conf->od_conf->outputStartValue & mask)?GPIO_OUTPUT_HIGH:GPIO_OUTPUT_LOW;
                }
                else if (conf->od_conf->inputMask & mask)     
                {
                    f = GPIO_INPUT | GPIO_INT_EDGE_BOTH;
                    if (conf->od_conf->inputPullUp & mask) f |= GPIO_PULL_UP;
                    else if(conf->od_conf->inputPullDown  & mask) f |= GPIO_PULL_DOWN;
                }
                else f = GPIO_DISCONNECTED;

                if (f)
                {
                    int err = gpio_pin_configure(conf->dev, pin, f);
                
                    if (err) {
                        LOG_ERR("failed to add input gpio pin configure %s", conf->dev->name);
                    }
                    if (f & GPIO_INT_ENABLE)
                    {
                        err = gpio_pin_interrupt_configure(conf->dev, pin, f);
                        if (err) {
                            LOG_ERR("failed to add input gpio interrupt configure %s %d %x err:%d", conf->dev->name, pin, f, err);
                        }
                        else{
                            LOG_INF("add input gpio interrupt %s %d %x", conf->dev->name, pin, f);
                        }
                    }
                }
            }         
        }   
        if (conf->od_conf->inputMask)
        {
            gpio_init_callback(&conf->input_gpio_callback, gpio_input_isr_callback, conf->od_conf->inputMask);

            gpio_remove_callback(conf->dev, &conf->input_gpio_callback);

            int err = gpio_add_callback(conf->dev, &conf->input_gpio_callback);

            if (err) {
                LOG_ERR("failed to add input gpio callback %s", conf->dev->name);
            }
        }
    }
    else
    {
        LOG_ERR("Error: GPIO device '%s' not found", conf->od_conf->port);
    }

    return conf->dev;
}

void gpios_init(void)
{
    struct gpio_conf *p = &gpios[0];

    CO_OD_configure(CO->SDO[0], 0x2080, odf_2080_GPIO_pack, NULL, 0U, 0U);

    for (size_t i = 0; i < ARRAY_SIZE(gpios); i++)
    {
        gpio_init(p);

        k_work_init(&p->work, gpio_input_work);

        CO_OD_configure(CO->SDO[0], p->index, odf_setup, p, 0U, 0U);

       	k_work_submit(&p->work);

        p++;
    }
    update_pack_iomask();    
}

void gpios_process(uint16_t timeDifference_ms)
{
    static uint16_t timer;
    timer += timeDifference_ms;

    if(timer >= CONFIG_OUTPUT_UPDATE_TIME){
        timer -= CONFIG_OUTPUT_UPDATE_TIME;

        struct gpio_conf* cf = &gpios[0];
        /* process outputs */
        for (size_t i = 0; i < ARRAY_SIZE(gpios); i++)
        {
            if (cf->dev)
            {
                uint16_t mask = cf->od_conf->outputMask;
                uint16_t old = cf->old_out;
                uint16_t new = *cf->od_out;

                if (old ^ new) 
                {
                    if (!(new & ~mask))
                    {
                        cf->old_out = new;
                        gpio_port_set_masked_raw(cf->dev, mask, new);
                    }
                    else
                    {
                        CO_LOCK_OD();
                        *cf->od_out = old;
                        CO_UNLOCK_OD();
                        
                        LOG_ERR("GPIO %s: Output Error OUT:%x OLD:%x MASK:%x.", cf->dev->name, new, old, mask);
                        // TODO: prepare CAN emergency message
                    }
                }
            }
            cf++;
        }

        if (FlagUpdateODF)
        {
            FlagUpdateODF = false;

            update_pack_iomask();
        }
    }    
}
