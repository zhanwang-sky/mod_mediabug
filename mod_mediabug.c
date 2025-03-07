//
//  mod_mediabug.c
//  mod_mediabug
//
//  Created by zhanwang-sky on 2025/3/3.
//

#include <switch.h>

SWITCH_MODULE_LOAD_FUNCTION(mod_mediabug_load);
SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_mediabug_shutdown);
SWITCH_MODULE_DEFINITION(mod_mediabug, mod_mediabug_load, mod_mediabug_shutdown, NULL);

typedef enum {
  AUDIO_MANIP_OP_DEFAULT,
  AUDIO_MANIP_OP_READ,
  AUDIO_MANIP_OP_WRITE,
} audio_manip_op_t;

typedef struct {
  audio_manip_op_t op;
  void* tech_pvt;
} audio_manip_session_t;

static switch_bool_t
audio_manip_cb(switch_media_bug_t* bug, void* data, switch_abc_type_t type) {
  switch_core_session_t* session = switch_core_media_bug_get_session(bug);
  audio_manip_session_t* ams = (audio_manip_session_t*) data;
  switch_frame_t* frame = NULL;
  switch_codec_t* read_codec = NULL;
  int sample_rate = -1;
  int16_t* pcm_data = NULL;

  switch (type) {
    case SWITCH_ABC_TYPE_INIT:
      read_codec = switch_core_session_get_read_codec(session);
      if (read_codec && read_codec->implementation) {
        sample_rate = read_codec->implementation->samples_per_second;
      }
      switch_log_printf(SWITCH_CHANNEL_SESSION_LOG(session), SWITCH_LOG_INFO,
                        "audio_manip_session initialized, "
                        "ams=%p, op=%d, sample_rate=%d\n",
                        ams, ams->op, sample_rate);
      break;

    case SWITCH_ABC_TYPE_WRITE_REPLACE:
      frame = switch_core_media_bug_get_write_replace_frame(bug);
      pcm_data = frame->data;
      for (uint32_t i = 0; i != frame->samples; ++i) {
        pcm_data[i] = 0;
      }
      break;

    case SWITCH_ABC_TYPE_READ_REPLACE:
      frame = switch_core_media_bug_get_read_replace_frame(bug);
      pcm_data = frame->data;
      for (uint32_t i = 0; i != frame->samples; ++i) {
        pcm_data[i] >>= 4;
      }
      break;

    case SWITCH_ABC_TYPE_CLOSE:
      switch_log_printf(SWITCH_CHANNEL_SESSION_LOG(session), SWITCH_LOG_INFO,
                        "audio_manip_session ended, ams=%p\n", ams);
      break;

    default:
      break;
  }

  return SWITCH_TRUE;
}

// static void name(switch_core_session_t *session, const char *data)
SWITCH_STANDARD_APP(audio_manip_func) {
  audio_manip_session_t* ams = NULL;
  switch_media_bug_t* bug = NULL;

  switch_log_printf(SWITCH_CHANNEL_SESSION_LOG(session), SWITCH_LOG_INFO,
                    "application=audio_manip, data=%s\n", data);

  if (!(ams = switch_core_session_alloc(session, sizeof(audio_manip_session_t)))) {
    switch_log_printf(SWITCH_CHANNEL_SESSION_LOG(session), SWITCH_LOG_WARNING,
                      "Fail to alloc audio_manip_session\n");
    return;
  }

  if (strcmp(data, "read") == 0) {
    ams->op = AUDIO_MANIP_OP_READ;
  } else if (strcmp(data, "write") == 0) {
    ams->op = AUDIO_MANIP_OP_WRITE;
  } else {
    ams->op = AUDIO_MANIP_OP_DEFAULT;
  }

  if (switch_core_media_bug_add(session, "audio_manip", NULL, audio_manip_cb, ams, 0,
                                SMBF_WRITE_REPLACE | SMBF_READ_REPLACE | SMBF_READ_PING,
                                &bug) != SWITCH_STATUS_SUCCESS) {
    switch_log_printf(SWITCH_CHANNEL_SESSION_LOG(session), SWITCH_LOG_WARNING,
                      "Fail to add media bug!\n");
    return;
  }

  switch_log_printf(SWITCH_CHANNEL_SESSION_LOG(session), SWITCH_LOG_INFO,
                    "media bug attached, ams=%p\n", ams);
}

// switch_status_t mod_mediabug_load(switch_loadable_module_interface_t **module_interface, switch_memory_pool_t *pool)
SWITCH_MODULE_LOAD_FUNCTION(mod_mediabug_load) {
  switch_application_interface_t* app_interface = NULL;

  /* connect my internal structure to the blank pointer passed to me */
  *module_interface = switch_loadable_module_create_module_interface(pool, modname);

  SWITCH_ADD_APP(app_interface,
                 "audio_manip", "audio manipulation", "mod_mediabug - audio manipulation",
                 audio_manip_func, "<operation>", SAF_MEDIA_TAP);

  switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "%s loaded\n", modname);

  return SWITCH_STATUS_SUCCESS;
}

// switch_status_t mod_mediabug_shutdown(void)
SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_mediabug_shutdown) {
  switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "shutting down %s\n", modname);
  return SWITCH_STATUS_SUCCESS;
}
