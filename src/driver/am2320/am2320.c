/* am2320.c - Driver for Bosch AM2320 temperature and pressure sensor */

/*
 * Copyright (c) 2016, 2017 Intel Corporation
 * Copyright (c) 2017 IpTronix S.r.l.
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <drivers/sensor.h>
#include <init.h>
#include <drivers/gpio.h>
#include <sys/byteorder.h>
#include <sys/__assert.h>

#include <logging/log.h>

#include "am2320.h"

LOG_MODULE_REGISTER(AM2320, CONFIG_SENSOR_LOG_LEVEL);

#if DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) == 0
#warning "AM2320 driver enabled without any devices"
#endif

static int am2320_bus_check_i2c(const struct device *bus, const struct am2320_bus_config *bus_config)
{
	return device_is_ready(bus) ? 0 : -ENODEV;
}

static int am2320_reg_read_i2c(const struct device *bus, const struct am2320_bus_config *bus_config,
                   uint8_t read_adr, uint8_t read_cnt,    
			       uint8_t *buf)
{
    int ret;
    ret = i2c_write(bus, NULL, 0, bus_config->i2c_addr);

    uint8_t rb[3] = {CMDREAD, read_adr, read_cnt};
	ret = i2c_write(bus, rb,  3, bus_config->i2c_addr);
    if (ret < 0)
    {
        return ret;
    }
    k_msleep(2);
	ret = i2c_read(bus, buf, read_cnt+2+2, bus_config->i2c_addr);
    if (ret < 0)
    {
        return ret;
    }
    return 0;
}

const struct am2320_bus_io am2320_bus_io_i2c = {
	.check = am2320_bus_check_i2c,
	.read = am2320_reg_read_i2c,
};

struct am2320_data {
	/* Compensated values. */
	uint32_t temp;
	uint32_t humidity;
};

struct am2320_config {
	const struct device *bus;
	const struct am2320_bus_io *bus_io;
	const struct am2320_bus_config bus_config;
};

static inline struct am2320_data *to_data(const struct device *dev)
{
	return dev->data;
}

static inline const struct am2320_config *to_config(const struct device *dev)
{
	return dev->config;
}

static inline const struct device *to_bus(const struct device *dev)
{
	return to_config(dev)->bus;
}

static inline const struct am2320_bus_config* to_bus_config(const struct device *dev)
{
	return &to_config(dev)->bus_config;
}

static inline int am2320_bus_check(const struct device *dev)
{
	return to_config(dev)->bus_io->check(to_bus(dev), to_bus_config(dev));
}

static inline int am2320_reg_read(const struct device *dev,
                   uint8_t read_adr, uint8_t read_cnt,    
			       uint8_t *buf)
{
	return to_config(dev)->bus_io->read(to_bus(dev), to_bus_config(dev), read_adr, read_cnt,  buf);
}

static int am2320_sample_fetch(const struct device *dev,
			       enum sensor_channel chan)
{
	struct am2320_data *data = to_data(dev);
	int16_t read_data[4];
	int ret;

	__ASSERT_NO_MSG(chan == SENSOR_CHAN_ALL);

	ret = am2320_reg_read(dev, 0, 4, (uint8_t*) &read_data);
	if (ret < 0) {
	 	return ret;
	}
	data->humidity = sys_be16_to_cpu(read_data[1]);
	data->temp = sys_be16_to_cpu(read_data[2]);

	return 0;
}

static int am2320_channel_get(const struct device *dev,
			      enum sensor_channel chan,
			      struct sensor_value *val)
{
	struct am2320_data *data = to_data(dev);

	switch (chan) {
	case SENSOR_CHAN_HUMIDITY:
		val->val1 = data->humidity / 10;
		val->val2 = (data->humidity % 10) * 100000;
		break;
	case SENSOR_CHAN_AMBIENT_TEMP:
		val->val1 = data->temp / 10;
		val->val2 = (data->temp % 10) * 100000;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static const struct sensor_driver_api am2320_api_funcs = {
	.sample_fetch = am2320_sample_fetch,
	.channel_get = am2320_channel_get,
};

static int am2320_chip_init(const struct device *dev)
{
	// struct am2320_data *data = to_data(dev);
	int err;

	LOG_DBG("initializing \"%s\" on bus \"%s\"",
		dev->name, to_bus(dev)->name);

	err = am2320_bus_check(dev);
	if (err < 0) {
		LOG_ERR("bus check failed: %d", err);
		return err;
	}
	err = am2320_sample_fetch(dev, SENSOR_CHAN_ALL);
	if (err < 0) {
		LOG_ERR("%s check failed: %d", dev->name, err);
		return err;
	}
	LOG_DBG("\"%s\" OK", dev->name);
	return 0;
}

/* Initializes a struct am2320_config for an instance on an I2C bus. */
#define AM2320_CONFIG_I2C(inst)						\
	{								\
		.bus = DEVICE_DT_GET(DT_INST_BUS(inst)),		\
		.bus_io = &am2320_bus_io_i2c,				\
		.bus_config.i2c_addr = DT_INST_REG_ADDR(inst),		\
	}

/*
 * Main instantiation macro, which selects the correct bus-specific
 * instantiation macros for the instance.
 */
#define AM2320_DEFINE(inst)						\
	static struct am2320_data am2320_data_##inst;			\
	static const struct am2320_config am2320_config_##inst =	\
			    AM2320_CONFIG_I2C(inst);			\
	DEVICE_DT_INST_DEFINE(inst,					\
			 am2320_chip_init,				\
			 am2320_pm_ctrl,				\
			 &am2320_data_##inst,				\
			 &am2320_config_##inst,				\
			 POST_KERNEL,					\
			 CONFIG_SENSOR_INIT_PRIORITY,			\
			 &am2320_api_funcs);

/* Create the struct device for every status "okay" node in the devicetree. */
DT_INST_FOREACH_STATUS_OKAY(AM2320_DEFINE)
