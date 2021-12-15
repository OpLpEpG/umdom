#include <kernel.h>
#include <zephyr.h>
#include <power/reboot.h>
#include <drivers/gpio.h>
#include <drivers/i2c.h>
#include <shell/shell.h>
#include <shell/shell_uart.h>
#include <device.h>
#include <stdlib.h>
#include <devicetree.h>
#include <drivers/sensor.h>
#include <drivers/pwm.h>
#include "settings/settings.h"
#include <drivers/adc.h>
#include <kernel/thread.h>
#include <canopennode.h>
#include <drivers/watchdog.h>

#ifdef CONFIG_SHELL_BACKEND_CANOPEN
  #include "driver/shell/shell_canopen.h"
#endif
#include "process_sensor.h"
#include "process_adc.h"
#include "process_gpio.h"

#define LOG_LEVEL CONFIG_CANOPEN_LOG_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(app);

#if DT_HAS_COMPAT_STATUS_OKAY(st_stm32_watchdog)
#define WDT_NODE DT_INST(0, st_stm32_watchdog)
#define WDT_DEV_NAME DT_LABEL(WDT_NODE)
#else
#error "WDT not found"
#endif

#if !DT_HAS_CHOSEN(zephyr_can_primary)
# error CANopen CAN interface not set
#else 
#  define CAN_DT_NAME DT_CHOSEN(zephyr_can_primary)
#  define CAN_INTERFACE DT_LABEL(CAN_DT_NAME)
#  define CAN_BITRATE (DT_PROP(CAN_DT_NAME, bus_speed) / 1000)
#endif

static const struct device *green_led = DEVICE_DT_GET(DT_NODELABEL(gpioc));	

static void led_callback(bool value, void *arg)
{
	gpio_pin_set(green_led, 13, value);
}

void main(void)
{	
	CO_NMT_reset_cmd_t reset = CO_RESET_NOT;
	CO_ReturnError_t err;
	struct canopen_context can;
	uint16_t timeout;
	uint32_t elapsed;
	int64_t timestamp;
	const struct device *wdt;

#if (CONFIG_CANOPENNODE_LEDS || CONFIG_DEBUG_LED)  
    const struct device *led = device_get_binding("GPIOC");
	if (led == NULL) {
		/* No such node, or the node does not have status "okay". */
		LOG_ERR("GPIOC Error: no device found.");
	}
	gpio_pin_configure(led, 13, GPIO_OUTPUT_LOW);
#endif
	can.dev = device_get_binding(CAN_INTERFACE);
	if (!can.dev) {
		LOG_ERR("CAN interface not found");
		return;
	}
#ifdef CONFIG_CANOPENNODE_STORAGE
	int ret;
	ret = settings_subsys_init();
	if (ret) {
		LOG_ERR("failed to initialize settings subsystem (err = %d)", ret);
		return;
	}
	ret = settings_load();
	if (ret) {
		LOG_ERR("failed to load settings (err = %d)", ret);
		return;
	}
#endif /* CONFIG_CANOPEN_STORAGE */
	
	while (reset != CO_RESET_APP) 
	{
		elapsed =  0U; /* milliseconds */

		err = CO_init(&can, CONFIG_CANOPEN_NODE_ID, CAN_BITRATE);
		if (err != CO_ERROR_NO) {
			LOG_ERR("CO_init failed (err = %d)", err);
			return;
		}
		
		LOG_INF("CANopen stack initialized");

		#ifdef CONFIG_CANOPENNODE_STORAGE
		canopen_storage_attach(CO->SDO[0], CO->em);
		#endif /* CONFIG_CANOPEN_STORAGE */

		#if  ( CONFIG_CANOPENNODE_LEDS && !CONFIG_DEBUG_LED )
    	canopen_leds_init(CO->NMT, led_callback, NULL, NULL, NULL); 
		#endif /* CONFIG_CANOPEN_LEDS */


		#ifdef CONFIG_SHELL_BACKEND_CANOPEN
		shell_canopen_init_od();
		#endif
		sensors_init();
		adcs_init();
		gpios_init();

		CO->TPDO[4]->defaultCOB_ID = 0x1C0;
		CO->TPDO[4]->CANtxBuff->ident = 0x1C0 + CONFIG_CANOPEN_NODE_ID;
		CO->TPDO[5]->defaultCOB_ID = 0x2C0;
		CO->TPDO[5]->CANtxBuff->ident = 0x2C0 + CONFIG_CANOPEN_NODE_ID;
		CO->TPDO[6]->defaultCOB_ID = 0x3C0;
		CO->TPDO[6]->CANtxBuff->ident = 0x3C0 + CONFIG_CANOPEN_NODE_ID;

		CO_CANsetNormalMode(CO->CANmodule[0]);

		wdt = device_get_binding(WDT_DEV_NAME);
		if (wdt == NULL) {
			/* No such node, or the node does not have status "okay". */
			LOG_ERR("IWDT Error: no device found.");
		}


		while (true) {
			timeout = 1U; /* default timeout in milliseconds */
			timestamp = k_uptime_get();
			reset = CO_process(CO, (uint16_t)elapsed, &timeout);

			if (reset != CO_RESET_NOT) {
				break;
			}

			if (timeout > 0) {
				/*
				 * Try to sleep for as long as the
				 * stack requested and calculate the
				 * exact time elapsed.
				 */
				k_sleep(K_MSEC(timeout));
				uint16_t dt = (uint16_t) (k_uptime_get() - timestamp);

				if (OD_RTR)
				{
					for(uint8_t i=0; i<CO_NO_TPDO-1; i++)
					{
						CO->TPDO[i]->sendRequest = 1;
					}	
					CO_LOCK_OD();
					OD_RTR = 0;
					CO_UNLOCK_OD();
				}

				if (CO->SYNC->timer < CO->SYNC->periodTimeoutTime)
				{
					wdt_feed(wdt, 0);
					if (CO_isError(CO->em, CO_EM_SYNC_TIME_OUT))
						CO_errorReset(CO->em, CO_EM_SYNC_TIME_OUT, 0);
				}

				sensors_process(dt);
				adcs_process(dt);
				gpios_process(dt);
				#ifdef CONFIG_SHELL_BACKEND_CANOPEN
				process_shell();
				#endif

				elapsed = (uint32_t)k_uptime_delta(&timestamp);
			} else {
				/*
				 * Do not sleep, more processing to be
				 * done by the stack.
				 */
				elapsed = 0U;
			}
		} // while(true)

		if (reset == CO_RESET_COMM) {
			LOG_INF("Resetting communication");
		}
	} // while (reset != CO_RESET_APP) 

	LOG_INF("Resetting device");

	CO_delete(&can);
	sys_reboot(SYS_REBOOT_COLD);
}
