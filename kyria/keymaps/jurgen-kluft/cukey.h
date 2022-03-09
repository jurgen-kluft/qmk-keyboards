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
    KC_SECRET_5,
    KC_SECRET_6,
    KC_SECRET_7,
    KC_SECRET_8,

    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    KC_SMART_BEGIN,
    KC_FCAPS = KC_SMART_BEGIN,
    KC_FNUM,
    KC_FSYM,
    KC_FNAV,
    
    KC_SCAPS,
    KC_SNUM,
    KC_SSYM,

    KC_DCOLN,

#include "cushi.def"

    KC_SMART_END,

    SC_BEGIN,
    SC_A = SC_BEGIN,
    SC_B,
    SC_C,
    SC_D,
    SC_E,
    SC_F,
    SC_G,
    SC_H,
    SC_I,
    SC_J,
    SC_K,
    SC_L,
    SC_M,
    SC_N,
    SC_O,
    SC_P,
    SC_Q,
    SC_R,
    SC_S,
    SC_T,
    SC_U,
    SC_V,
    SC_W,
    SC_X,
    SC_Y,
    SC_Z,
    SC_SCN,
    SC_SPC,
    SC_BPC,
    SC_CMA,
    SC_DOT,
    SC_SLS,
    SC_END,
};

#undef CUSHI_ENTRY

uint16_t process_cukey(uint16_t keycode);