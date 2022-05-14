#pragma once

#define LAYER_STATE_8BIT

#define NO_MUSIC_MODE
#define NO_ACTION_ONESHOT
#define NO_ACTION_TAPPING
#define NO_ACTION_LAYER

#define COMBO_TERM 200
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define MACRO_TIMER 5

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

#define USB_POLLING_INTERVAL_MS 1
#define DEBOUNCE 4
#define SPLIT_USB_DETECT
#define KEYBOARD_HILLSIDE

// If you have encoders and want to not have them swap left/right when you plug USB to the other half
// then define EE_HANDS and flash your sides with 'avrdude-split-left' and 'avrdude-split-right'.
// This makes sure that the firmware on the left sides identifies itself as 'left' and the right side
// identifies itself as 'right'.
// #define EE_HANDS
