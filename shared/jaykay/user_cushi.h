#pragma once

#define CUSHI_ENTRY(custom_keycode, key_normal, key_shift, key_ctrl, key_alt, key_gui) custom_keycode,
enum ecushi_keycodes
{
#include "user_cushi.def"
    CUSHI_COUNT,
};
#undef CUSHI_ENTRY

