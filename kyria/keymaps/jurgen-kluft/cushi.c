#include QMK_KEYBOARD_H
#include "cukey.h"

static uint16_t cushi_registered_keycode = KC_NO;

#define CUSHI_ENTRY(entry_cushi_keycode, entry_cushi_key_normal, entry_cushi_key_shift, entry_cushi_key_ctrl) \
    case entry_cushi_keycode:                                                                                 \
        cushi_key_normal = entry_cushi_key_normal;                                                            \
        entry_cushi_key_shift;                                                                                \
        entry_cushi_key_ctrl;                                                                                 \
        break;

bool process_cushi_keys(uint16_t keycode, keyrecord_t *record) {
    // Release any registered key that we might have going on
    if (cushi_registered_keycode != KC_NO) {
        unregister_code16(cushi_registered_keycode);
        cushi_registered_keycode = KC_NO;
    }

    uint16_t cushi_key_normal = KC_NO;
    uint16_t cushi_key_shift  = KC_NO;
    uint16_t cushi_key_ctrl   = KC_NO;

    // @NOTE: Add your custom entries in cushi.def
    switch (keycode) {
#include "cushi.def"
        default:
            return true;
    }

    if (record->event.pressed) {
        const uint8_t mods = get_mods();

        if ((cushi_key_shift != KC_NO) && (((mods | get_weak_mods()) & MOD_MASK_SHIFT) != 0)) {
            del_mods(MOD_MASK_SHIFT);
            del_weak_mods(MOD_MASK_SHIFT);
            cushi_registered_keycode = cushi_key_shift;
        } else if ((cushi_key_ctrl != KC_NO) && (((mods | get_weak_mods()) & MOD_MASK_CTRL) != 0)) {
            del_mods(MOD_MASK_CTRL);
            del_weak_mods(MOD_MASK_CTRL);
            cushi_registered_keycode = cushi_key_ctrl;
        } else {
            cushi_registered_keycode = cushi_key_normal;
        }

        // this could be a custom keycode, so we need to translate it
        cushi_registered_keycode = process_cukey(cushi_registered_keycode);
        if (cushi_registered_keycode != KC_NO) {
            register_code16(cushi_registered_keycode);
        }
        
        set_mods(mods);  // Restore the mods.
    }

    return false;
}
