#include QMK_KEYBOARD_H
#include "cukey.h"
#include "user_cushi.h"

static uint16_t cushi_registered_keycode = KC_NO;

#define CUSHI_ENTRY(keycode, normal, shift, ctrl, alt, cmd) \
    case keycode:                                           \
        key_normal = normal;                                \
        shift;                                              \
        ctrl;                                               \
        alt;                                                \
        cmd;                                                \
        break;

uint16_t process_cushi_keys(uint16_t keycode, keyrecord_t* record, bool simulate)
{
    uint16_t key_normal = KC_NO;
    uint16_t key_shift  = KC_NO;
    uint16_t key_ctrl   = KC_NO;
    uint16_t key_alt    = KC_NO;
    uint16_t key_gui    = KC_NO;

    // @NOTE: Add your custom entries in user_cushi.def
    switch (keycode)
    {
#include "user_cushi.def"
        default: return keycode;
    }

    const uint8_t mods       = get_mods();
    uint8_t       modmask    = 0;
    cushi_registered_keycode = key_normal;
    if ((key_shift != KC_NO) && (((mods | get_weak_mods()) & MOD_MASK_SHIFT) != 0))
    {
        modmask                  = MOD_MASK_SHIFT;
        cushi_registered_keycode = key_shift;
    }
    else if ((key_ctrl != KC_NO) && (((mods | get_weak_mods()) & MOD_MASK_CTRL) != 0))
    {
        modmask                  = MOD_MASK_CTRL;
        cushi_registered_keycode = key_ctrl;
    }
    else if ((key_alt != KC_NO) && (((mods | get_weak_mods()) & MOD_MASK_ALT) != 0))
    {
        modmask                  = MOD_MASK_ALT;
        cushi_registered_keycode = key_alt;
    }
    else if ((key_gui != KC_NO) && (((mods | get_weak_mods()) & MOD_MASK_GUI) != 0))
    {
        modmask                  = MOD_MASK_GUI;
        cushi_registered_keycode = key_gui;
    }

    if (!simulate)
    {
        if (modmask != 0)
        {
            del_mods(modmask);
            del_weak_mods(modmask);
        }

        if (record->event.pressed)
        {
            register_code16(cushi_registered_keycode);
        }
        else
        {
            unregister_code16(cushi_registered_keycode);
        }

        if (modmask != 0)
        {
            set_mods(mods); // Restore the mods.
        }
    }
    return cushi_registered_keycode;
}
