//
//  mod_mediabug.c
//  mod_mediabug
//
//  Created by zhanwang-sky on 2025/3/3.
//

#include <switch.h>

SWITCH_MODULE_LOAD_FUNCTION(mod_mediabug_load);
SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_mediabug_shutdown);
SWITCH_MODULE_RUNTIME_FUNCTION(mod_mediabug_runtime);
SWITCH_MODULE_DEFINITION(mod_mediabug, mod_mediabug_load, mod_mediabug_shutdown, NULL);

/* Macro expands to: switch_status_t mod_my_echo_load(switch_loadable_module_interface_t **module_interface, switch_memory_pool_t *pool) */
SWITCH_MODULE_LOAD_FUNCTION(mod_mediabug_load) {
  /* connect my internal structure to the blank pointer passed to me */
  *module_interface = switch_loadable_module_create_module_interface(pool, modname);

  switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "%s loaded\n", modname);

  return SWITCH_STATUS_SUCCESS;
}

SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_mediabug_shutdown) {
  switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "shutting down %s\n", modname);
  return SWITCH_STATUS_SUCCESS;
}

SWITCH_MODULE_RUNTIME_FUNCTION(mod_mediabug_runtime) {
  return SWITCH_STATUS_TERM;
}
