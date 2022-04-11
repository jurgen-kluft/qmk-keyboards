#pragma once

#define KC_TRANS KC_TRANSPARENT
#define ____     KC_TRANSPARENT
#define xxxx     KC_NO
#define LT_MOS   TG(_MOUS)

#include "user_keycode_ranges.h"

enum euser_keycodes
{
    KC_OLED = USER_KEYCODES_START,
    KC_QWERTY,
    KC_RSTHD,
};
