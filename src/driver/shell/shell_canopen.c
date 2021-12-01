#include "shell_canopen.h"
#include <init.h>
#include <logging/log.h>
#include <canopennode.h>

SHELL_CANOPEN_DEFINE(shell_transport_canopen);
SHELL_DEFINE(shell_canopen, CONFIG_SHELL_PROMPT_CANOPEN, &shell_transport_canopen,
	     CONFIG_SHELL_BACKEND_CANOPEN_LOG_MESSAGE_QUEUE_SIZE,
	     CONFIG_SHELL_BACKEND_CANOPEN_LOG_MESSAGE_QUEUE_TIMEOUT,
	     SHELL_FLAG_OLF_CRLF);

LOG_MODULE_REGISTER(shell_canopen, CONFIG_SHELL_CANOPEN_LOG_LEVEL);

static bool canopen_enabled;
static bool canopen_blockin;
static bool canopen_tx_busy;
static bool canopen_rx_new;

static CO_SDO_abortCode_t odf_1026(CO_ODF_arg_t *odf_arg)
{
    if (canopen_enabled && !odf_arg->reading && (odf_arg->subIndex == 1)) 
    {
		struct shell_canopen *sh_canopen = (struct shell_canopen *)odf_arg->object;
		canopen_rx_new = true;
		sh_canopen->handler(SHELL_TRANSPORT_EVT_RX_RDY, sh_canopen->context);
   }
    return CO_SDO_AB_NONE;    
}

static int init(const struct shell_transport *transport,
		const void *config,
		shell_transport_handler_t evt_handler,
		void *context)
{
	struct shell_canopen *sh_canopen = (struct shell_canopen *)transport->ctx;

	sh_canopen->handler = evt_handler;
	sh_canopen->context = context;

	return 0;
}

static int uninit(const struct shell_transport *transport)
{
	canopen_enabled = false;
	return 0;
}

void shell_canopen_init_od(void)
{
	struct shell_canopen *sh_canopen = (struct shell_canopen *)shell_transport_canopen.ctx;
	CO_OD_configure(CO->SDO[0], 0x1026, odf_1026, sh_canopen, 0U, 0U);	
}

static int enable(const struct shell_transport *transport, bool blocking)
{
	canopen_blockin = blocking;
	canopen_enabled = true;
	return 0;
}

void process_shell(void)
{
    // CO_LOCK_OD();
	if (canopen_tx_busy && !CO->TPDO[CO_NO_TPDO-1]->sendRequest)
	{
		struct shell_canopen *sh_canopen = (struct shell_canopen *)shell_transport_canopen.ctx;
		canopen_tx_busy = false;
		sh_canopen->handler(SHELL_TRANSPORT_EVT_TX_RDY, sh_canopen->context);
	}
	// CO_UNLOCK_OD();
}

static int write(const struct shell_transport *transport,
		 const void *data, size_t length, size_t *cnt)
{
	const uint8_t *data8 = (const uint8_t *)data;
	if (!CO || CO->TPDO[CO_NO_TPDO-1]->sendRequest) 
	{
		*cnt = 0;
		canopen_tx_busy = true;
	}
	else 
	{
		CO_LOCK_OD();
		OD_OSPrompt.stdOut = *data8;
		CO->TPDO[CO_NO_TPDO-1]->sendRequest = 1;
		CO_UNLOCK_OD();
		*cnt = 1;
	}
	return 0;
}

static int read(const struct shell_transport *transport,
		void *data, size_t length, size_t *cnt)
{
	if (canopen_rx_new)
	{
		*(uint8_t*)data = OD_OSPrompt.stdIn;
		*cnt = 1;
		canopen_rx_new = false;
	}
	else *cnt = 0;

	return 0;
}

const struct shell_transport_api shell_canopen_transport_api = {
	.init = init,
	.uninit = uninit,
	.enable = enable,
	.write = write,
	.read = read
};

static int enable_shell_canopen(const struct device *arg)
{
	ARG_UNUSED(arg);
	bool log_backend = CONFIG_SHELL_CANOPEN_INIT_LOG_LEVEL > 0;
	uint32_t level = (CONFIG_SHELL_CANOPEN_INIT_LOG_LEVEL > LOG_LEVEL_DBG) ?
		      CONFIG_LOG_MAX_LEVEL : CONFIG_SHELL_CANOPEN_INIT_LOG_LEVEL;

	struct shell_backend_config_flags f =	SHELL_DEFAULT_BACKEND_CONFIG_FLAGS;	  

	shell_init(&shell_canopen, NULL, f, log_backend, level);

	return 0;
}

/* Function is used for testing purposes */
const struct shell *shell_backend_canopen_get_ptr(void)
{
	return &shell_canopen;
}
SYS_INIT(enable_shell_canopen, POST_KERNEL, 0);
