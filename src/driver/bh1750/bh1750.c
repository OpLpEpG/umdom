/* bh1750.c - Driver for Bosch BH1750 temperature and pressure sensor */

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

#include "bh1750.h"

LOG_MODULE_REGISTER(BH1750, CONFIG_SENSOR_LOG_LEVEL);

#if DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) == 0
#warning "BH1750 driver enabled without any devices"
#endif

static int bh1750_bus_check_i2c(const struct device *bus, const struct bh1750_bus_config *bus_config)
{
	return device_is_ready(bus) ? 0 : -ENODEV;
}

static int bh1750_reg_read_i2c(const struct device *bus, const struct bh1750_bus_config *bus_config,
			       uint8_t *buf, int size)
{
	return i2c_read(bus, buf,  size, bus_config->i2c_addr);
}

static int bh1750_reg_write_i2c(const struct device *bus, const struct bh1750_bus_config *bus_config,
				uint8_t *buf, int size)
{
	return i2c_write(bus, buf,  size, bus_config->i2c_addr);
}

const struct bh1750_bus_io bh1750_bus_io_i2c = {
	.check = bh1750_bus_check_i2c,
	.read = bh1750_reg_read_i2c,
	.write = bh1750_reg_write_i2c,
};

struct bh1750_data {
	uint32_t comp_lux;
};

struct bh1750_config {
	const struct device *bus;
	const struct bh1750_bus_io *bus_io;
	const struct bh1750_bus_config bus_config;
};

static inline struct bh1750_data *to_data(const struct device *dev)
{
	return dev->data;
}

static inline const struct bh1750_config *to_config(const struct device *dev)
{
	return dev->config;
}

static inline const struct device *to_bus(const struct device *dev)
{
	return to_config(dev)->bus;
}

static inline const struct bh1750_bus_config* to_bus_config(const struct device *dev)
{
	return &to_config(dev)->bus_config;
}

static inline int bh1750_bus_check(const struct device *dev)
{
	return to_config(dev)->bus_io->check(to_bus(dev), to_bus_config(dev));
}

static inline int bh1750_reg_read(const struct device *dev,
				  uint8_t *buf, int size)
{
	return to_config(dev)->bus_io->read(to_bus(dev), to_bus_config(dev), buf, size);
}

static inline int bh1750_reg_write(const struct device *dev, 
				  uint8_t *buf, int size)
{
	return to_config(dev)->bus_io->write(to_bus(dev), to_bus_config(dev), buf, size);
}

static int bh1750_sample_fetch(const struct device *dev,
			       enum sensor_channel chan)
{
	struct bh1750_data *data = to_data(dev);
	uint8_t wbuf[1] = {ONETMODEL};
	uint16_t lux_data;
	int ret;

	__ASSERT_NO_MSG(chan == SENSOR_CHAN_ALL);

	ret = bh1750_reg_write(dev, wbuf, 1);
	if (ret < 0) {
	 	return ret;
	}

	// k_msleep(180); //ONETMODEH 0x20
	k_msleep(24); //ONETMODEL 0x23

	ret = bh1750_reg_read(dev, (uint8_t*) &lux_data, 2);
	if (ret < 0) {
	 	return ret;
	}
	data->comp_lux = sys_be16_to_cpu(lux_data);

	return 0;
}

static int bh1750_channel_get(const struct device *dev,
			      enum sensor_channel chan,
			      struct sensor_value *val)
{
	struct bh1750_data *data = to_data(dev);

	switch (chan) {
	case SENSOR_CHAN_LIGHT:
		val->val1 = data->comp_lux;
		val->val2 = 0;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static const struct sensor_driver_api bh1750_api_funcs = {
	.sample_fetch = bh1750_sample_fetch,
	.channel_get = bh1750_channel_get,
};

static int bh1750_chip_init(const struct device *dev)
{
	// struct bh1750_data *data = to_data(dev);
	int err;

	LOG_DBG("initializing \"%s\" on bus \"%s\"",
		dev->name, to_bus(dev)->name);

	err = bh1750_bus_check(dev);
	if (err < 0) {
		LOG_DBG("bus check failed: %d", err);
		return err;
	}
	err = bh1750_sample_fetch(dev, SENSOR_CHAN_ALL);
	if (err < 0) {
		LOG_ERR("%s check failed: %d", dev->name, err);
		return err;
	}
	LOG_DBG("\"%s\" OK", dev->name);
	return 0;
}

/* Initializes a struct bh1750_config for an instance on an I2C bus. */
#define BH1750_CONFIG_I2C(inst)						\
	{								\
		.bus = DEVICE_DT_GET(DT_INST_BUS(inst)),		\
		.bus_io = &bh1750_bus_io_i2c,				\
		.bus_config.i2c_addr = DT_INST_REG_ADDR(inst),		\
	}

/*
 * Main instantiation macro, which selects the correct bus-specific
 * instantiation macros for the instance.
 */
#define BH1750_DEFINE(inst)						\
	static struct bh1750_data bh1750_data_##inst;			\
	static const struct bh1750_config bh1750_config_##inst =	\
			    BH1750_CONFIG_I2C(inst);			\
	DEVICE_DT_INST_DEFINE(inst,					\
			 bh1750_chip_init,				\
			 bh1750_pm_ctrl,				\
			 &bh1750_data_##inst,				\
			 &bh1750_config_##inst,				\
			 POST_KERNEL,					\
			 CONFIG_SENSOR_INIT_PRIORITY,			\
			 &bh1750_api_funcs);

/* Create the struct device for every status "okay" node in the devicetree. */
DT_INST_FOREACH_STATUS_OKAY(BH1750_DEFINE)
