#pragma once

#define CUSHI_ENTRY(custom_keycode, key_normal, key_shift, key_ctrl, key_alt, key_gui) custom_keycode,

enum eCustomKeyCodes {
    KC_QWERTY = SAFE_RANGE,
    KC_RSTHD,
    KC_OLED,
    KC_OS_MODE,
    KC_OS_PMODE,
    KC_OS_UNDO,
    KC_OS_REDO,
    KC_OS_CUT,
    KC_OS_COPY,
    KC_OS_PASTE,
    KC_OS_NDT,
    KC_OS_PDT,
    KC_OS_CLOSE,

    KC_SECRET_1,
    KC_SECRET_2,
    KC_SECRET_3,
    KC_SECRET_4,

    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    KC_SMART_BEGIN,

    KC_FCAPS,
    KC_FNUM,
    KC_FSYM,
    KC_FNAV,
    
    KC_SCAPS,
    KC_SNUM,
    KC_SSYM,

    KC_DCOLN,

#include "cushi.def"

    KC_SMART_END,
};

#undef CUSHI_ENTRY

uint16_t process_cukey(uint16_t keycode);