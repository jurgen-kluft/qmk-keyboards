#pragma once

#include "user_keycode_ranges.h"

enum esecret_keycodes
{
    KC_SECRET_1 = SECRET_KEYCODES_START,
    KC_SECRET_2,
    KC_SECRET_3,
    KC_SECRET_4,
    KC_SECRET_5,
    KC_SECRET_6,
    KC_SECRET_7,
    KC_SECRET_8,    
    SECRET_SAFE_RANGE_END
};

#if ((SECRET_SAFE_RANGE_END-1) > SECRET_KEYCODES_END)
#error "Not enough space for SECRET keycodes"
#endif

