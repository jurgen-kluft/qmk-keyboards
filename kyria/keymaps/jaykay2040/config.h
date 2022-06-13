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

// F6 = GP27
// F7 = GP26
// B1 = GP22
// B3 = GP20
// 
// B2 = GP23
// B6 = GP21
// B5 = GP9
// B4 = GP8
// E6 = GP7
// D7 = GP6
// C6 = GP5
// D4 = GP4
// 
// F4 = GP29
// F5 = GP28

// clang-format off
#ifdef KYRIA_REV2

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

#else // rev1

    #define MATRIX_ROW_PINS { GP8, GP7, GP6, GP4 }
    #define MATRIX_COL_PINS { GP21, GP23, GP20, GP22, GP26, GP27, GP28, GP29 }
    #define UNUSED_PINS

    #define ENCODERS_PAD_A { GP5 }
    #define ENCODERS_PAD_B { GP9 }
    #define ENCODERS_PAD_A_RIGHT { GP9 }
    #define ENCODERS_PAD_B_RIGHT { GP5 }

    #define I2C_DRIVER I2CD2
    #define I2C1_SDA_PIN GP2
    #define I2C1_SCL_PIN GP3

    //#define SERIAL_USART_DRIVER SIOD0
    //#define SERIAL_USART_TX_PIN GP0
    //#define SERIAL_USART_RX_PIN GP1

    #define RGB_DI_PIN GP0
    #define SOFT_SERIAL_PIN GP1

#endif
// clang-format on

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
//#define EE_HANDS
