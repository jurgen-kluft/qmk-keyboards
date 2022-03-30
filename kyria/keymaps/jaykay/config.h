#pragma once

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
  #define OLED_TIMEOUT 300000
  #define OLED_FONT_HEIGHT 8
  #define OLED_FONT_WIDTH 6
  #define OLED_FONT_H "oledfont.c"
#endif

#ifdef RGBLIGHT_ENABLE
  //#define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 150
  #define RGBLIGHT_LAYERS
  #define RGBLIGHT_MAX_LAYERS 16
  #define RGBLIGHT_TIMEOUT_MINS 5    // in minutes (<=5)
#endif

#define LAYER_STATE_16BIT

#define NO_MUSIC_MODE
#define NO_ACTION_ONESHOT
#define NO_ACTION_TAPPING
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

#define COMBO_TERM 200
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define MACRO_TIMER 5
#define TAP_CODE_DELAY 20

#define MK_COMBINED
#define MOUSEKEY_DELAY 100
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MOVE_DELTA 20
#define MOUSEKEY_MAX_SPEED 5
#define MOUSEKEY_TIME_TO_MAX 100
#define MOUSEKEY_WHEEL_DELAY 100
#define MOUSEKEY_WHEEL_INTERVAL 50
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 100

// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping
// every other tick, lower the resolution to 2.
#define ENCODER_RESOLUTION 2

#define KEYBOARD_KYRIA