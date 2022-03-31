#include QMK_KEYBOARD_H
#include "cukey.h"

static uint16_t cushi_registered_keycode = KC_NO;

#define CUSHI_ENTRY(keycode, normal, shift, ctrl, alt, cmd) \
    case keycode:                                           \
        key_normal = normal;                                \
        shift;                                              \
        ctrl;                                               \
        alt;                                                \
        cmd;                                                \
        break;

bool process_cushi_keys(uint16_t keycode, keyrecord_t* record)
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
        default: return true;
    }

    if (record->event.pressed)
    {
        const uint8_t mods = get_mods();

        // Release any registered key that we might have going on
        if (cushi_registered_keycode != KC_NO)
        {
            unregister_code16(cushi_registered_keycode);
            cushi_registered_keycode = KC_NO;
        }

        cushi_registered_keycode = key_normal;
        if ((key_shift != KC_NO) && (((mods | get_weak_mods()) & MOD_MASK_SHIFT) != 0))
        {
            del_mods(MOD_MASK_SHIFT);
            del_weak_mods(MOD_MASK_SHIFT);
            cushi_registered_keycode = key_shift;
        }
        else if ((key_ctrl != KC_NO) && (((mods | get_weak_mods()) & MOD_MASK_CTRL) != 0))
        {
            del_mods(MOD_MASK_CTRL);
            del_weak_mods(MOD_MASK_CTRL);
            cushi_registered_keycode = key_ctrl;
        }
        else if ((key_alt != KC_NO) && (((mods | get_weak_mods()) & MOD_MASK_ALT) != 0))
        {
            del_mods(MOD_MASK_ALT);
            del_weak_mods(MOD_MASK_ALT);
            cushi_registered_keycode = key_alt;
        }
        else if ((key_gui != KC_NO) && (((mods | get_weak_mods()) & MOD_MASK_GUI) != 0))
        {
            del_mods(MOD_MASK_GUI);
            del_weak_mods(MOD_MASK_GUI);
            cushi_registered_keycode = key_gui;
        }

        // this could be a custom keycode, so we need to translate it
        cushi_registered_keycode = process_cukey(cushi_registered_keycode);
        if (cushi_registered_keycode != KC_NO)
        {
            register_code16(cushi_registered_keycode);
        }

        set_mods(mods); // Restore the mods.
    }
    else
    {
        // Release any registered key that we might have going on
        if (cushi_registered_keycode != KC_NO)
        {
            unregister_code16(cushi_registered_keycode);
            cushi_registered_keycode = KC_NO;
        }
    }

    return true;
}
