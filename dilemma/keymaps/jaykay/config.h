#pragma once

#define LAYER_STATE_16BIT

#define MACRO_TIMER 5
#define TAP_CODE_DELAY 20

/** Dilemma-specific features. */
#ifdef POINTING_DEVICE_ENABLE
// Flip horizontal direction for drag-scroll.
#    define DILEMMA_DRAGSCROLL_REVERSE_X
// #define DILEMMA_DRAGSCROLL_REVERSE_Y
#endif // POINTING_DEVICE_ENABLE

#define KEYBOARD_DILEMMA

