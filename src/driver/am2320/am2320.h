/*
 * Copyright (c) 2016, 2017 Intel Corporation
 * Copyright (c) 2017 IpTronix S.r.l.
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_SENSOR_AM2320_AM2320_H_
#define ZEPHYR_DRIVERS_SENSOR_AM2320_AM2320_H_

#include <zephyr/types.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/i2c.h>

#define DT_DRV_COMPAT aosong_am2320

#define AM2320_BUS_I2C DT_ANY_INST_ON_BUS_STATUS_OKAY(i2c)

struct am2320_bus_config {
	uint16_t i2c_addr;
};

typedef int (*am2320_bus_check_fn)(const struct device *bus, const struct am2320_bus_config *bus_config);
typedef int (*am2320_reg_read_fn)(const struct device *bus, const struct am2320_bus_config *bus_config,
                   uint8_t read_adr, uint8_t read_cnt,    
			       uint8_t *buf);

struct am2320_bus_io {
	am2320_bus_check_fn check;
	am2320_reg_read_fn read;
};

extern const struct am2320_bus_io am2320_bus_io_i2c;

#define CMDREAD 0x03

#endif /* ZEPHYR_DRIVERS_SENSOR_AM2320_AM2320_H_ */
