#pragma once

#define MACRO_TIMER 5
#define TAP_CODE_DELAY 20

#define CIRQUE_PINNACLE_TAP_ENABLE

/** Dilemma-specific features. */
#ifdef POINTING_DEVICE_ENABLE
// Flip horizontal direction for drag-scroll.
#    define DILEMMA_DRAGSCROLL_REVERSE_X
// #define DILEMMA_DRAGSCROLL_REVERSE_Y
#endif 

#define KEYBOARD_DILEMMA

// USB activity will determine which half is master
// RP2040 seems to need a bit more time to boot up
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 3500