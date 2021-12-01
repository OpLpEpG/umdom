
#include <kernel.h>
#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/sensor.h>
#include <drivers/i2c.h>
#include <canopennode.h>


#define LOG_LEVEL CONFIG_CANOPEN_LOG_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(sensor);


struct sensor_data{
	const struct device *dev;
	void  *od_data;
};

struct sensor_config {
	const char *name;
	const uint16_t od;
    int (* const sample_fetch) (const struct sensor_config* sens);
	struct sensor_data * const data;
};

#ifdef OD_2006_BH1750
   static struct sensor_data sd_2006_BH1750;
#endif
#ifdef OD_2007_BH1750
   static struct sensor_data sd_2007_BH1750;
#endif
#ifdef OD_2008_BH1750
   static struct sensor_data sd_2008_BH1750;
#endif
#ifdef OD_2009_BH1750
   static struct sensor_data sd_2009_BH1750;
#endif
#ifdef OD_200C_BME280
   static struct sensor_data sd_200C_BME280;
#endif
#ifdef OD_200D_BME280
   static struct sensor_data sd_200D_BME280;
#endif
#ifdef OD_200E_BME280
   static struct sensor_data sd_200E_BME280;
#endif
#ifdef OD_200F_BME280
   static struct sensor_data sd_200F_BME280;
#endif
#ifdef OD_200A_AM2320
   static struct sensor_data sd_200A_AM2320;
#endif
#ifdef OD_200B_AM2320
   static struct sensor_data sd_200B_AM2320;
#endif

static int sample_fetch_BH1750(const struct sensor_config * sens);
static int sample_fetch_BME280(const struct sensor_config * sens);
static int sample_fetch_AM2320(const struct sensor_config * sens);

static const struct sensor_config allSensor[] = {
#ifdef OD_2006_BH1750
    {
        .name="BH1750_1",
        .od=OD_2006_BH1750,
        .sample_fetch=sample_fetch_BH1750,
        .data = &sd_2006_BH1750
     },
#endif
#ifdef OD_2007_BH1750
    {
        .name="BH1750_2",
        .od=OD_2007_BH1750,
        .sample_fetch=sample_fetch1_BH1750,
        .data = &sd_2007_BH1750
     },
#endif
#ifdef OD_2008_BH1750
    {
        .name="BH1750_3",
        .od=OD_2008_BH1750,
        .sample_fetch=sample_fetch1_BH1750,
        .data = &sd_2008_BH1750
     },
#endif
#ifdef OD_2009_BH1750
    {
        .name="BH1750_4",
        .od=OD_2009_BH1750,
        .sample_fetch=sample_fetch_BH1750,
        .data = &sd_2009_BH1750
     },
#endif
#ifdef OD_200C_BME280
    {
        .name="BME280_1",
        .od=OD_200C_BME280,
        .sample_fetch=sample_fetch_BME280,
        .data = &sd_200C_BME280
     },
#endif
#ifdef OD_200D_BME280
    {
        .name="BME280_2",
        .od=OD_200D_BME280,
        .sample_fetch=sample_fetch_BME280,
        .data = &sd_200D_BME280
     },
#endif
#ifdef OD_200E_BME280
    {
        .name="BME280_3",
        .od=OD_200E_BME280,
        .sample_fetch=sample_fetch_BME280,
        .data = &sd_200E_BME280
     },
#endif
#ifdef OD_200F_BME280
    {
        .name="BME280_4",
        .od=OD_200F_BME280,
        .sample_fetch=sample_fetch_BME280,
        .data = &sd_200F_BME280
     },
#endif
#ifdef OD_200A_AM2320
    {
        .name="AM2320_1",
        .od=OD_200A_AM2320,
        .sample_fetch=sample_fetch_AM2320,
        .data = &sd_200A_AM2320
     },
#endif
#ifdef OD_200B_AM2320
    {
        .name="AM2320_2",
        .od=OD_200B_AM2320,
        .sample_fetch=sample_fetch_AM2320,
        .data = &sd_200B_AM2320
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

static int sample_fetch(const struct sensor_config * sens)
{
    const struct device * d = sens->data->dev;
        if (d)
        {
            int err;
		    err = sensor_sample_fetch(d);
            if (err < 0)
            {
                LOG_ERR("Error: Device %s", sens->name);
                i2c_recover_bus(to_bus(d));
            }
            return err;
        }
        else return -1;
}

static int sample_fetch_BH1750(const struct sensor_config * sens)
{

    int ret = sample_fetch(sens);
    OD_BH1750_t *od = sens->data->od_data;
    const struct device * d = sens->data->dev;

    if (ret < 0){
        CO_LOCK_OD();
        od->lux = 0x8000;
        CO_UNLOCK_OD();
    }
    else {
        struct sensor_value lux;
	    sensor_channel_get(d, SENSOR_CHAN_LIGHT, &lux);
        CO_LOCK_OD();
        od->lux = lux.val1;
        CO_UNLOCK_OD();
    }
    return ret;
}

static int sample_fetch_BME280(const struct sensor_config * sens)
{

    int ret = sample_fetch(sens);
    OD_BME280_t *od = sens->data->od_data;
    const struct device * d = sens->data->dev;

    if (ret < 0){
        CO_LOCK_OD();
        od->temp = 0x80;
        od->humid = 0x80;
        od->press = 0x8000;
        CO_UNLOCK_OD();
    }
    else {
        struct sensor_value sv;
	    sensor_channel_get(d, SENSOR_CHAN_AMBIENT_TEMP, &sv);
        CO_LOCK_OD();
        od->temp = sv.val1;
        CO_UNLOCK_OD();
	    sensor_channel_get(d, SENSOR_CHAN_HUMIDITY, &sv);
        CO_LOCK_OD();
        od->humid = sv.val1;
        CO_UNLOCK_OD();
	    sensor_channel_get(d, SENSOR_CHAN_PRESS, &sv);
        int16_t press = (sv.val1*1000 + sv.val2/1000)/133;
        CO_LOCK_OD();
        od->press = press;
        CO_UNLOCK_OD();
    }
    return ret;
}

static int sample_fetch_AM2320(const struct sensor_config * sens)
{

    int ret = sample_fetch(sens);
    OD_AM2320_t *od = sens->data->od_data;
    const struct device * d = sens->data->dev;

    if (ret < 0){
        CO_LOCK_OD();
        od->temp = 0x80;
        od->humid = 0x80;
        CO_UNLOCK_OD();
    }
    else {
        struct sensor_value sv;
	    sensor_channel_get(d, SENSOR_CHAN_AMBIENT_TEMP, &sv);
        CO_LOCK_OD();
        od->temp = sv.val1;
        CO_UNLOCK_OD();
	    sensor_channel_get(d, SENSOR_CHAN_HUMIDITY, &sv);
        CO_LOCK_OD();
        od->humid = sv.val1;
        CO_UNLOCK_OD();
    }
    return ret;
}

static void check_dev(const struct sensor_config* sens,void *od_data)
{
    const struct device * d = device_get_binding(sens->name);
    sens->data->od_data = od_data;

	if (d == NULL) {
		// No such node, or the node does not have status "okay".
		LOG_ERR("%s Error: no device found.", sens->name);
	}
    else {
	    const struct device* bus = to_bus(d);

	    if (!device_is_ready(d)) {
		    LOG_ERR("Error: Device \"%s %s\" is not ready; "
                    "check the driver initialization logs for errors.",
		            d->name, bus->name);
	    }
	    LOG_DBG("Found device \"%s  %s\", getting sensor data\n", d->name, bus->name);
    }
    sens->data->dev = d;
    sens->sample_fetch(sens);
}


void sensors_init(void)
{     
    const struct sensor_config *sens = allSensor;

    #ifdef OD_BH1750   
        OD_BH1750_t* od_BH1750 = (OD_BH1750_t*) &OD_BH1750;
        while (sens->sample_fetch == sample_fetch_BH1750)
            check_dev(sens++, od_BH1750++);
    #endif
    #ifdef OD_BME280  
        OD_BME280_t* od_BME280 = (OD_BME280_t*) &OD_BME280;
        while (sens->sample_fetch == sample_fetch_BME280)
            check_dev(sens++, od_BME280++);
    #endif
    #ifdef OD_AM2320   
        OD_AM2320_t* od_AM2320 = (OD_AM2320_t*) &OD_AM2320;
        while (sens->sample_fetch == sample_fetch_AM2320)
            check_dev(sens++, od_AM2320++);
    #endif
}

void sensors_process(uint16_t timeDifference_ms)
{
    static uint16_t timer;
    static const struct sensor_config *sens;
    static int8_t index;

    timer += timeDifference_ms;
    if(timer >= CONFIG_SENSORS_UPDATE_TIME){
        timer -= CONFIG_SENSORS_UPDATE_TIME;
        sens = allSensor;
        index = ARRAY_SIZE(allSensor);
    }

    if (index)
    {
        sens->sample_fetch(sens);
        index--;
        sens++;
    }
}
