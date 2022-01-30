#pragma once

#define CUSHI_ENTRY(custom_keycode, cushi_normal, cushi_shift, cushi_ctrl) custom_keycode,

enum eCustomKeyCodes {
    KC_QWERTY = SAFE_RANGE,
    KC_RSTHD,
    KC_PASSWORD,
    KC_OLED,
    KC_SCAPS,
    KC_SNUM,
    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    OS_MODE,
    OS_MODE_SHOW,
    KC_OS_UNDO,
    KC_OS_REDO,
    KC_OS_CUT,
    KC_OS_COPY,
    KC_OS_PASTE,
    KC_OS_NDT,
    KC_OS_PDT,
    KC_OS_CLOSE,

#include "cushi.def"
};

#undef CUSHI_ENTRY
