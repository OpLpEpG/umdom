#include <kernel.h>
#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <canbus/canopen.h>


#define LOG_LEVEL CONFIG_CANOPEN_LOG_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(gpios);

#define GPIO_INPUT_INT_EDGE (GPIO_INT_EDGE_BOTH | GPIO_INPUT)

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
    *conf->od_inp = conf->od_conf->inputMask & v;
    CO_UNLOCK_OD();
}    


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
                    f = GPIO_INPUT_INT_EDGE;
                    if (conf->od_conf->inputPullUp & mask) f |= GPIO_PULL_UP;
                    else if(conf->od_conf->inputPullDown  & mask) f |= GPIO_PULL_DOWN;
                }
                else f = GPIO_DISCONNECTED;
                gpio_pin_configure(conf->dev, pin, f);
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
    for (size_t i = 0; i < ARRAY_SIZE(gpios); i++)
    {
        gpio_init(p);

        k_work_init(&p->work, gpio_input_work);

        CO_OD_configure(CO->SDO[0], p->index, odf_setup, p, 0U, 0U);

        p++;
    }    
}

// static inline int check_out(const OD_configPort_t* conf, uint16_t out)
// {
//     return (out & ~conf->outputMask)?0:1;
// }

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
    }
    
}
