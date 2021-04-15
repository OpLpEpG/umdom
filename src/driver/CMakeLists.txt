# SPDX-License-Identifier: Apache-2.0
add_subdirectory_ifdef(CONFIG_ADC_STM32_AC_CURRENT		adc)
add_subdirectory_ifdef(CONFIG_AM2320		am2320)
add_subdirectory_ifdef(CONFIG_BH1750		bh1750)

# zephyr_sources_ifdef(CONFIG_USERSPACE sensor_handlers.c)
