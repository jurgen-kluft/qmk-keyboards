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
        case LAYER_QWERTY: 
        case LAYER_RSTHD:
            current_layer = keyboard_get_layout(); 
            break;
        // case LAYER_QWERTY_CAPS:
        // case LAYER_RSTHD_CAPS:
        //     current_layer = LAYER_QWERTY_CAPS + keyboard_get_layout();
        //     break;
        default: current_layer = layer; break;
    }

    // switch (current_layer)
    // {
    //     case LAYER_QWERTY: send_string_with_delay("QWERTY", MACRO_TIMER); break;
    //     case LAYER_RSTHD: send_string_with_delay("RSTHD", MACRO_TIMER);break;
    //     case LAYER_QWERTY_CAPS: send_string_with_delay("QWERTY_CAPS", MACRO_TIMER);break;
    //     case LAYER_RSTHD_CAPS: send_string_with_delay("RSTHD_CAPS", MACRO_TIMER);break;
    //     case LAYER_NUMBERS: send_string_with_delay("NUMBERS", MACRO_TIMER);break;
    //     case LAYER_SYMBOLS: send_string_with_delay("SYMBOLS", MACRO_TIMER);break;
    //     case LAYER_NAVIGATION: send_string_with_delay("NAV", MACRO_TIMER);break;
    //     case LAYER_RAISE: send_string_with_delay("RAISE", MACRO_TIMER);break;
    // }


    layer_state_set((1<<keyboard_get_layout()) | (1<<current_layer));
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
