#pragma once

#include "user_keycode_ranges.h"

enum ecukey_keycodes
{
    KC_OS_UNDO = CUKEY_KEYCODES_START,
    KC_OS_REDO,
    KC_OS_CUT,
    KC_OS_COPY,
    KC_OS_PASTE,
    KC_OS_NDT,
    KC_OS_PDT,
    KC_OS_CLOSE,
    CUKEY_SAFE_RANGE_END
};

#if ((CUKEY_SAFE_RANGE_END-1) > CUKEY_KEYCODES_END)
#error "Not enough space for CUKEY keycodes"
#endif

enum eOS
{
    OS_MAC     = 0,
    OS_WINDOWS = 1,
    OS_UBUNTU  = 2,
};

void     keyboard_set_os(uint8_t os);
uint8_t  keyboard_get_os(void);
uint16_t process_cukey(uint16_t keycode);
