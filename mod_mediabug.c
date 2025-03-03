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

SWITCH_MODULE_LOAD_FUNCTION(mod_mediabug_load) {
  switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "mod_mediabug loaded\n");
  return SWITCH_STATUS_SUCCESS;
}

SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_mediabug_shutdown) {
  switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "mod_mediabug shutdown\n");
  return SWITCH_STATUS_SUCCESS;
}

SWITCH_MODULE_RUNTIME_FUNCTION(mod_mediabug_runtime) {
  return SWITCH_STATUS_TERM;
}
