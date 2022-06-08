#pragma once

#undef MATRIX_ROW_PINS
#undef MATRIX_ROW_PINS_RIGHT
#undef MATRIX_COL_PINS
#undef MATRIX_COL_PINS_RIGHT
#undef ENCODERS_PAD_A
#undef ENCODERS_PAD_B
#undef ENCODERS_PAD_A_RIGHT
#undef ENCODERS_PAD_B_RIGHT 
#undef SOFT_SERIAL_PIN
#undef RGB_DI_PIN
#undef SPLIT_HAND_MATRIX_GRID

#define MATRIX_ROW_PINS {GP27, GP26, GP22, GP20}
#define MATRIX_ROW_PINS_RIGHT {GP4, GP5, GP6, GP7}
#define MATRIX_COL_PINS {GP23, GP21, GP9, GP8, GP7, GP6, GP5, GP4}
#define MATRIX_COL_PINS_RIGHT {GP8, GP9, GP21, GP23, GP20, GP22, GP26, GP27}

#define ENCODERS_PAD_A {GP29}
#define ENCODERS_PAD_B {GP28}
#define ENCODERS_PAD_A_RIGHT {GP28}
#define ENCODERS_PAD_B_RIGHT {GP29}

#define SERIAL_USART_TX_PIN GP1
#define RGB_DI_PIN GP0
#define SPLIT_HAND_MATRIX_GRID GP7, GP20
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP16
#define I2C1_SCL_PIN GP17
// #define SPLIT_POINTING_ENABLE
// #define POINTING_DEVICE_RIGHT
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_ANIMATIONS
    #define RGBLIGHT_SLEEP
    #define RGBLIGHT_HUE_STEP 5
    #define RGBLIGHT_SAT_STEP 5
#endif

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

// If you have encoders and want to not have them swap left/right when you plug USB to the other half
// then define EE_HANDS and flash your sides with 'avrdude-split-left' and 'avrdude-split-right'.
// This makes sure that the firmware on the left sides identifies itself as 'left' and the right side
// identifies itself as 'right'.
#define EE_HANDS
