/*
 * Copyright (c) 2016, 2017 Intel Corporation
 * Copyright (c) 2017 IpTronix S.r.l.
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_SENSOR_BH1750_BH1750_H_
#define ZEPHYR_DRIVERS_SENSOR_BH1750_BH1750_H_

#include <zephyr/types.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/i2c.h>

#define DT_DRV_COMPAT rohm_bh1750

#define BH1750_BUS_I2C DT_ANY_INST_ON_BUS_STATUS_OKAY(i2c)

struct bh1750_bus_config {
	uint16_t i2c_addr;
};

typedef int (*bh1750_bus_check_fn)(const struct device *bus,
				   const struct bh1750_bus_config *bus_config);
typedef int (*bh1750_reg_read_fn)(const struct device *bus,
				  const struct bh1750_bus_config *bus_config,
				  uint8_t *buf, int size);
typedef int (*bh1750_reg_write_fn)(const struct device *bus,
				   const struct bh1750_bus_config *bus_config,
				  uint8_t *buf, int size);

struct bh1750_bus_io {
	bh1750_bus_check_fn check;
	bh1750_reg_read_fn read;
	bh1750_reg_write_fn write;
};

extern const struct bh1750_bus_io bh1750_bus_io_i2c;

#define ONETMODEH 0x20
#define ONETMODEL 0x23

#endif /* ZEPHYR_DRIVERS_SENSOR_BH1750_BH1750_H_ */
