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
#define MACRO_TIMER 5

#define LAYER_STATE_8BIT
#define NO_ACTION_LAYER

#define USB_POLLING_INTERVAL_MS 1
#define DEBOUNCE 4
#define QMK_KEYS_PER_SCAN 4

#undef RGB_DISABLE_TIMEOUT
#define RGB_DISABLE_TIMEOUT 600000

#define USB_SUSPEND_WAKEUP_DELAY 0
#define MK_COMBINED
#define MOUSEKEY_MOVE_DELTA 25

#define CAPS_LOCK_STATUS
#define FIRMWARE_VERSION       u8"l7M4a/vqoAR"
#define RGB_MATRIX_STARTUP_SPD 60

#define KEYBOARD_MOONLANDER

