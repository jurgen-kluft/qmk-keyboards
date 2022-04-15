#pragma once

#include "user_keycode_ranges.h"

#define CUSHI_ENTRY(custom_keycode, key_normal, key_shift, key_ctrl, key_alt, key_gui) custom_keycode,
enum ecushi_keycodes
{
    CUSHI_SAFE_RANGE_START = CUSHI_KEYCODES_START - 1,
#include "user_cushi.def"
    CUSHI_SAFE_RANGE_END,
};
#undef CUSHI_ENTRY

#if ((CUSHI_SAFE_RANGE_END-1) > CUSHI_KEYCODES_END)
#error "Not enough space for CUSHI keycodes"
#endif
