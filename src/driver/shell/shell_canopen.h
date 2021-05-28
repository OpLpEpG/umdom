/*
 * Copyright (c) 2018 Makaio GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SHELL_CANOPEN_H__
#define SHELL_CANOPEN_H__

#include <shell/shell.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const struct shell_transport_api shell_canopen_transport_api;

struct shell_canopen {
	shell_transport_handler_t handler;
	// struct k_timer timer;
	void *context;
};

#define SHELL_CANOPEN_DEFINE(_name)					\
	static struct shell_canopen _name##_shell_canopen;			\
	struct shell_transport _name = {				\
		.api = &shell_canopen_transport_api,			\
		.ctx = (struct shell_canopen *)&_name##_shell_canopen		\
	}
void shell_canopen_init_od(void);
void process_shell(void);
/**
 * @brief Function provides pointer to shell canopen backend instance.
 *
 * Function returns pointer to the shell canopen instance. This instance can be
 * next used with shell_execute_cmd function in order to test commands behavior.
 *
 * @returns Pointer to the shell instance.
 */
const struct shell *shell_backend_canopen_get_ptr(void);
#ifdef __cplusplus
}
#endif

#endif /* SHELL_CANOPEN_H__ */
