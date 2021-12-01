#include <kernel.h>
#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/adc.h>
#include <drivers/i2c.h>
#include <canopennode.h>


#define LOG_LEVEL CONFIG_CANOPEN_LOG_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(adcs);


static const struct device *adc;
static struct k_poll_signal async;
static struct k_poll_event  event = K_POLL_EVENT_INITIALIZER(
                                    K_POLL_TYPE_SIGNAL,
					                K_POLL_MODE_NOTIFY_ONLY,
					                &async);



static int16_t adcs[10] = {1,2,3,4,5,6,7,8,9,10};


static int channels_setup(uint16_t channels)
{
    struct adc_channel_cfg cf = {
        // .channel_id = id,
        .gain = ADC_GAIN_1,
        .reference = ADC_REF_INTERNAL,
        .acquisition_time = ADC_ACQ_TIME(ADC_ACQ_TIME_TICKS, CONFIG_ADC_STM32_AC_CURRENT_SAMPLE_TIME),
        .differential = 0,
    };
	uint8_t index = 0; 
    uint16_t tst = (channels & OD_configADC.availableMask) ^ channels;
    if (tst)
    {
        LOG_ERR("Error ADC ch: %x %x setup", channels, OD_configADC.availableMask);
        return -1;
    }
	while (channels)
	{
		if (channels & 1)
		{
            cf.channel_id = index;
            int ret = adc_channel_setup(adc, &cf);
            if (ret < 0)
            {
                LOG_ERR("Error ADC ch: %d setup", index);
                return ret;
            }
		}
		index++;
		channels >>= 1;
	}    
    return 0;
}

static void sample_fetch_odf6401(void)
{
    uint16_t channels = OD_configADC.cannelsMask;
    int16_t* pch = &OD_readAnalogueInput16Bit[0];
    int16_t* padc = &adcs[0];

    CO_LOCK_OD();

	while (channels)
	{
		if (channels & 1)
		{
            *pch = *padc++;
        }
		pch++;
		channels >>= 1;
	}    

    CO_UNLOCK_OD();
}

static CO_SDO_abortCode_t odf_2005(CO_ODF_arg_t *odf_arg)
{
    if (odf_arg->reading) {
		return CO_SDO_AB_NONE;
	}
    uint16_t value = CO_getUint16(odf_arg->data);
    switch(odf_arg->subIndex) {
        case 1:
           return channels_setup(value)?CO_SDO_AB_INVALID_VALUE:CO_SDO_AB_NONE; 
        break;
        case 2:
           return CO_SDO_AB_READONLY;
        break;
     }
     return CO_SDO_AB_SUB_UNKNOWN;
}

void adcs_init(void)
{
    adc = device_get_binding("ADC_1");

	if (adc == NULL) {
		LOG_ERR("ADC_1 Error: no device found.");
        return;
	}
    k_poll_signal_init(&async);

    channels_setup(OD_configADC.cannelsMask);

    CO_OD_configure(CO->SDO[0], OD_2005_configADC,  odf_2005, NULL, 0U, 0U); 
}

void adcs_process(uint16_t timeDifference_ms)
{
	if (adc == NULL) return;

    static uint16_t timer;
    timer += timeDifference_ms;

    if (k_poll(&event, 1, K_NO_WAIT) == 0)
    {
        sample_fetch_odf6401();
        event.signal->signaled = 0;
        event.state = K_POLL_STATE_NOT_READY;
    }
    

    if(timer >= CONFIG_ADCS_UPDATE_TIME){
        timer -= CONFIG_ADCS_UPDATE_TIME;

        struct adc_sequence sq = {
            .resolution = 12,
            .channels = OD_configADC.cannelsMask,
            .buffer = adcs,
            .buffer_size = sizeof(adcs),
        };
        if (event.state == K_POLL_STATE_NOT_READY)
        {
            event.state = K_POLL_STATE_CANCELLED;
            int ret = adc_read_async(adc, &sq, &async);
            if (ret < 0)
            {
		        LOG_ERR("ADC_1 Error: adc_read_async %d.", ret);
            }
        }
        
    }
}
