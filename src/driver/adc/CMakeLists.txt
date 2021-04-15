# SPDX-License-Identifier: Apache-2.0
zephyr_library()

zephyr_library_sources_ifdef(CONFIG_ADC_STM32_AC_CURRENT adc_stm32_ac.c)
