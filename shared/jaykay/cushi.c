#include QMK_KEYBOARD_H
#include "config.h"
#include "cushi.h"
#include "user_keycodes.h"
#include "user_layers.h"

static uint8_t cushi_registered_keycode = KC_NO;

#define CUSHI_ENTRY(keycode, normal, shift, ctrl, alt, cmd) \
    case keycode:                                           \
        key_normal = normal;                                \
        shift;                                              \
        ctrl;                                               \
        alt;                                                \
        cmd;                                                \
        break;

cushi_t process_cushi_keys(uint8_t ti, uint8_t tc, keyrecord_t* record)
{
    uint8_t key_normal = TC_NO;
    uint8_t key_shift  = TC_NO;
    uint8_t key_ctrl   = TC_NO;
    uint8_t key_alt    = TC_NO;
    uint8_t key_gui    = TC_NO;

    // @NOTE: Add your custom entries in user_cushi.def and make sure you define your
    //        custom keycodes in 'user_keycodes.h'.
    switch (tc)
    {
#include "user_cushi.def"
        default: { cushi_t c = { .replaced = false, .tc = TC_NO, .modmask = 0 }; return c; }
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

    cushi_t c = { .replaced = true, .tc = cushi_registered_keycode, .modmask = modmask };
    return c;
}
