/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR

#undef TAPPING_TERM
#define TAPPING_TERM 300
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

#undef RGB_DISABLE_TIMEOUT
#define RGB_DISABLE_TIMEOUT 600000

#define USB_SUSPEND_WAKEUP_DELAY 0
#define MK_COMBINED
#define MOUSEKEY_DELAY 100
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MOVE_DELTA 25
#define MOUSEKEY_MAX_SPEED 5
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 50
#define MOUSEKEY_WHEEL_DELAY 100
#define MOUSEKEY_WHEEL_INTERVAL 50
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 100

#define CAPS_LOCK_STATUS
#define FIRMWARE_VERSION u8"l7M4a/vqoAR"
#define RGB_MATRIX_STARTUP_SPD 60
