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
