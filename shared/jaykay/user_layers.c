#include QMK_KEYBOARD_H
#include "config.h"
#include "cukey.h"
#include "oneshot.h"
#include "user_layers.h"
#include "user_keycodes.h"

static int8_t current_layer = LAYER_QWERTY;
void          user_layer_on(int8_t layer)
{
    switch (layer)
    {
        case LAYER_RSTHD:
        case LAYER_QWERTY: current_layer = keyboard_get_layout(); break;
        case LAYER_NUMBERS:
        case LAYER_SYMBOLS:
        case LAYER_NAVIGATION:
        case LAYER_RAISE:
        default: current_layer = layer; break;
    }
    layer_state_set(1<<current_layer);
}

int8_t user_layer_current(void) { return current_layer; }

void register_keycode_press(uint16_t kc)
{
    uint16_t qmk_keycode = kc;
    if (qmk_keycode != KC_NO)
    {
        register_code16(qmk_keycode);
    }
}

void register_keycode_press_with_shift(uint16_t kc)
{
    uint16_t qmk_keycode = kc;
    if (qmk_keycode != KC_NO)
    {
        if (qmk_keycode >= KC_A && qmk_keycode <= KC_Z)
        {
            qmk_keycode = LSFT(qmk_keycode);
        }
        register_code16(qmk_keycode);
    }
}

void register_keycode_press_nomods(uint16_t kc)
{
    const uint8_t mods = get_mods();
    del_mods(MOD_MASK_SHIFT|MOD_MASK_CTRL|MOD_MASK_ALT|MOD_MASK_GUI);
    del_weak_mods(MOD_MASK_SHIFT|MOD_MASK_CTRL|MOD_MASK_ALT|MOD_MASK_GUI);
    register_keycode_press(kc);
    set_mods(mods); // Restore the mods.
}

void register_keycode_release(uint16_t kc)
{
    unregister_code16(kc);
}

void register_keycode_release_nomods(uint16_t kc)
{
    const uint8_t mods = get_mods();
    del_mods(MOD_MASK_SHIFT|MOD_MASK_CTRL|MOD_MASK_ALT|MOD_MASK_GUI);
    del_weak_mods(MOD_MASK_SHIFT|MOD_MASK_CTRL|MOD_MASK_ALT|MOD_MASK_GUI);
    register_keycode_release(kc);
    set_mods(mods); // Restore the mods.
}

void register_keycode_tap(uint16_t kc)
{
    uint16_t qmk_keycode = kc;
    tap_code16(qmk_keycode);
}

void register_keycode_tap_with_shift(uint16_t kc)
{
    uint16_t qmk_keycode = kc;
    qmk_keycode          = LSFT(qmk_keycode);
    tap_code16(qmk_keycode);
}
