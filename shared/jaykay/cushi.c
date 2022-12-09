#include QMK_KEYBOARD_H
#include "config.h"
#include "cushi.h"
#include "user_keycodes.h"
#include "user_layers.h"

#define CUSHI_ENTRY(keycode, normal, shift, ctrl, alt, cmd) \
    case keycode:                                           \
        key_normal = normal;                                \
        shift;                                              \
        ctrl;                                               \
        alt;                                                \
        cmd;                                                \
        break;

uint16_t process_cushi_keys(uint16_t kc, keyrecord_t* record)
{
    uint16_t key_normal = KC_NO;
    uint16_t key_shift  = KC_NO;
    uint16_t key_ctrl   = KC_NO;
    uint16_t key_alt    = KC_NO;
    uint16_t key_gui    = KC_NO;

    // @NOTE: Add your custom entries in user_cushi.def and make sure you define your
    //        custom keycodes in 'user_keycodes.h'.
    switch (kc)
    {
#include "user_cushi.def"
        default: { return KC_NO; }
    }

    const uint8_t mods = get_mods();
    if ((key_shift != KC_NO) && ((mods & MOD_MASK_SHIFT) != 0))
    {
        return key_shift;
    }
    else if ((key_ctrl != KC_NO) && ((mods & MOD_MASK_CTRL) != 0))
    {
        return key_ctrl;
    }
    else if ((key_alt != KC_NO) && ((mods & MOD_MASK_ALT) != 0))
    {
        return key_alt;
    }
    else if ((key_gui != KC_NO) && ((mods & MOD_MASK_GUI) != 0))
    {
        return key_gui;
    }
    return key_normal;
}
