
#include <kernel.h>
#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/sensor.h>
#include <drivers/i2c.h>
#include <canbus/canopen.h>


#define LOG_LEVEL CONFIG_CANOPEN_LOG_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(sensor);

struct sensor_conf {
	const char *name;
	const uint16_t od;
	const struct device *dev;
	void  *od_data;
};

static struct sensor_conf bh1750[] = {
#ifdef OD_2006_BH1750
    {
        .name="BH1750_1",
        .od=OD_2006_BH1750,
     },
#endif
#ifdef OD_2007_BH1750
    {
        .name="BH1750_2",
        .od=OD_2007_BH1750,
     },
#endif
#ifdef OD_2008_BH1750
    {
        .name="BH1750_3",
        .od=OD_2008_BH1750,
     },
#endif
#ifdef OD_2009_BH1750
    {
        .name="BH1750_4",
        .od=OD_2009_BH1750,
     },
#endif//*/
};

static struct sensor_conf bme280[] = {
#ifdef OD_200C_BME280
    {
        .name="BME280_1",
        .od=OD_200C_BME280,
     },
#endif
#ifdef OD_200D_BME280
    {
        .name="BME280_2",
        .od=OD_200D_BME280,
     },
#endif
#ifdef OD_200E_BME280
    {
        .name="BME280_3",
        .od=OD_200E_BME280,
     },
#endif
#ifdef OD_200F_BME280
    {
        .name="BME280_4",
        .od=OD_200F_BME280,
     },
#endif
};

static struct sensor_conf am2320[] = {
#ifdef OD_200A_AM2320
    {
        .name="AM2320_1",
        .od=OD_200A_AM2320,
     },
#endif
#ifdef OD_200B_AM2320
    {
        .name="AM2320_2",
        .od=OD_200B_AM2320,
     },
#endif
};

struct i2cdev_conf {
	const struct device *bus;
};

static inline const struct i2cdev_conf *to_config(const struct device *dev)
{
	return dev->config;
}

static inline const struct device *to_bus(const struct device *dev)
{
	return to_config(dev)->bus;
}

static int sample_fetch(struct sensor_conf * sens)
{
        if (sens->dev)
        {
            int err;
		    err = sensor_sample_fetch(sens->dev);
            if (err < 0)
            {
                LOG_ERR("Error: Device %s", sens->name);
                i2c_recover_bus(to_bus(sens->dev));
            }
            return err;
        }
        else return -1;
}

static int sample_fetch_BH1750(struct sensor_conf * sens)
{

    int ret = sample_fetch(sens);
    OD_BH1750_t *od = sens->od_data;

    if (ret < 0){
        CO_LOCK_OD();
        od->lux = 0x8000;
        CO_UNLOCK_OD();
    }
    else {
        struct sensor_value lux;
	    sensor_channel_get(sens->dev, SENSOR_CHAN_LIGHT, &lux);
        CO_LOCK_OD();
        od->lux = lux.val1;
        CO_UNLOCK_OD();
    }
    return ret;
}
static int sample_fetch_BME280(struct sensor_conf * sens)
{

    int ret = sample_fetch(sens);
    OD_BME280_t *od = sens->od_data;

    if (ret < 0){
        CO_LOCK_OD();
        od->temp = 0x80;
        od->humid = 0x80;
        od->press = 0x8000;
        CO_UNLOCK_OD();
    }
    else {
        struct sensor_value sv;
	    sensor_channel_get(sens->dev, SENSOR_CHAN_AMBIENT_TEMP, &sv);
        CO_LOCK_OD();
        od->temp = sv.val1;
        CO_UNLOCK_OD();
	    sensor_channel_get(sens->dev, SENSOR_CHAN_HUMIDITY, &sv);
        CO_LOCK_OD();
        od->humid = sv.val1;
        CO_UNLOCK_OD();
	    sensor_channel_get(sens->dev, SENSOR_CHAN_PRESS, &sv);
        int32_t press = (sv.val1*1000 + sv.val2/1000)/133;
        CO_LOCK_OD();
        od->press = press;
        CO_UNLOCK_OD();
    }
    return ret;
}
static int sample_fetch_AM2320(struct sensor_conf * sens)
{

    int ret = sample_fetch(sens);
    OD_BME280_t *od = sens->od_data;

    if (ret < 0){
        CO_LOCK_OD();
        od->temp = 0x80;
        od->humid = 0x80;
        CO_UNLOCK_OD();
    }
    else {
        struct sensor_value sv;
	    sensor_channel_get(sens->dev, SENSOR_CHAN_AMBIENT_TEMP, &sv);
        CO_LOCK_OD();
        od->temp = sv.val1;
        CO_UNLOCK_OD();
	    sensor_channel_get(sens->dev, SENSOR_CHAN_HUMIDITY, &sv);
        CO_LOCK_OD();
        od->humid = sv.val1;
        CO_UNLOCK_OD();
    }
    return ret;
}

static const struct device* check_dev(struct sensor_conf      *sens,
                                        void                  *od_data)
{
    sens->dev = device_get_binding(sens->name);
    sens->od_data = od_data;

	if (sens->dev == NULL) {
		// No such node, or the node does not have status "okay".
		LOG_ERR("%s Error: no device found.", sens->name);
        return NULL;
	}
    else {
	    const struct device* bus = to_bus(sens->dev);

	    if (!device_is_ready(sens->dev)) {
		    LOG_ERR("Error: Device \"%s %s\" is not ready; "
                    "check the driver initialization logs for errors.",
		            sens->dev->name, bus->name);
		    return NULL;
	    }
	    LOG_DBG("Found device \"%s  %s\", getting sensor data\n", sens->dev->name, bus->name);
    }
    return sens->dev;
}

void sensors_init(void)
{     
     struct sensor_conf *sens = bh1750;
     OD_BH1750_t* od_BH1750 = (OD_BH1750_t*) &OD_BH1750;

     for (size_t i = 0; i < ARRAY_SIZE(bh1750); i++)
     {
       check_dev(sens, od_BH1750);//, BH1750_odf_2006_9);
       sample_fetch_BH1750(sens);
       od_BH1750++;
       sens++;
     }

     sens = bme280;     
     OD_BME280_t* od_BME280 = (OD_BME280_t*) &OD_BME280;

     for (size_t i = 0; i < ARRAY_SIZE(bme280); i++)
     {
       check_dev(sens, od_BME280);//, BME280_odf_200C_F);
       sample_fetch_BME280(sens);
       od_BME280++;
       sens++;
     }

     sens = am2320;     
     OD_AM2320_t* od_AM2320 = (OD_AM2320_t*) &OD_AM2320;

     for (size_t i = 0; i < ARRAY_SIZE(am2320); i++)
     {
       check_dev(sens, od_AM2320);//, AM2320_odf_200A_B);
       sample_fetch_AM2320(sens);
       od_AM2320++;
       sens++;
     }
}

void sensors_process(uint16_t timeDifference_ms)
{
    static uint16_t timer;
    static struct sensor_conf *sens;
    static int8_t index_type;
    static int8_t index;

    timer += timeDifference_ms;
    if(timer >= CONFIG_SENSORS_UPDATE_TIME){
        timer -= CONFIG_SENSORS_UPDATE_TIME;
        sens = bh1750;
        index_type = 3;
        index = ARRAY_SIZE(bh1750);
    }
    if (index_type)
    {
        if (index > 0)
        {
            switch (index_type)
            {
                case 3:
                    sample_fetch_BH1750(sens++);
                break;
                case 2:
                    sample_fetch_BME280(sens++);
                break;        
                case 1:
                    sample_fetch_AM2320(sens++);
                break;
            }
        }
        if(--index <= 0)
        {
            index_type--;

            if (index_type)
            {
                if (index_type == 2)
                {
                    index = ARRAY_SIZE(bme280);                
                    sens = bme280;     
                }
                else 
                {
                    index = ARRAY_SIZE(am2320);            
                    sens = am2320;     
                }
            }
        }                
    }
}
