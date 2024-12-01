#include QMK_KEYBOARD_H
#include "config.h"
#include "cukey.h"
#include "oneshot.h"
#include "user_layers.h"
#include "user_keycodes.h"

#ifndef MACRO_TIMER
#    define MACRO_TIMER 3
#endif

static int8_t current_layer = LAYER_QWERTY;
void          user_layer_on(int8_t layer)
{
    switch (layer)
    {
        case LAYER_QWERTY:
        case LAYER_RSTHD:
        case LAYER_GRAPHITE:
        case LAYER_ENGRAM2:
        case LAYER_STURDY: current_layer = keyboard_get_layout(); break;
        default: current_layer = layer; break;
    }

    layer_state_set((1 << keyboard_get_layout()) | (1 << current_layer));
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
    uint8_t mod = get_mods();
    clear_mods();
    turnoff_oneshot_modifiers();
    register_keycode_press(kc);
    set_mods(mod);
}

void register_keycode_release(uint16_t kc) { unregister_code16(kc); }

void register_keycode_release_nomods(uint16_t kc)
{
    uint8_t mod = get_mods();
    clear_mods();
    register_keycode_release(kc);
    set_mods(mod);
}

void tap_code16_nomods(uint16_t kc)
{
    uint8_t mod = get_mods();
    clear_mods();
    tap_code16(kc);
    set_mods(mod);
}

void tap_code16_shift(uint16_t kc)
{
    uint16_t qmk_keycode = kc;
    qmk_keycode          = LSFT(qmk_keycode);
    tap_code16(qmk_keycode);
}

void register_string(const char* str)
{
    uint8_t mod = get_mods();
    clear_mods();
    while (*str != '\0')
    {
        send_char(*str);
        {
            uint8_t ms = MACRO_TIMER;
            while (ms--)
                wait_ms(1);
        }
        str++;
    }
    set_mods(mod);
}
