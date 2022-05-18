#include QMK_KEYBOARD_H
#include "config.h"
#include "cukey.h"
#include "vim.h"
#include "oneshot.h"
#include "user_layers.h"
#include "user_keycodes.h"

#if defined(KEYBOARD_HILLSIDE) || defined(KEYBOARD_KYRIA)

static uint8_t               user_kb_state[40] = {KC_NO};
extern const uint8_t PROGMEM user_kb_layers[][40];

#elif defined(KEYBOARD_MOONLANDER)

static uint8_t               user_kb_state[72] = {KC_NO};
extern const uint8_t PROGMEM user_kb_layers[][72];

#endif

static int8_t smartcaps_enabled = 0;
static int8_t current_layer     = LAYER_QWERTY;

void user_layer_on(int8_t layer)
{
    switch (layer)
    {
        case LAYER_RSTHD:
        case LAYER_QWERTY: current_layer = keyboard_get_layout(); break;
        case LAYER_SYMBOLS:
        case LAYER_NAVIGATION:
        case LAYER_NUMBERS:
        case LAYER_RAISE:
        case LAYER_VIM:
        default: current_layer = layer; break;
    }
}

int8_t user_layer(void) { return current_layer; }

void user_smartcaps_on() { smartcaps_enabled = 1; }
void user_smartcaps_off() { smartcaps_enabled = 0; }

void user_camelcase_toggle(void) 
{
    if (smartcaps_enabled == 2)
    {
        smartcaps_enabled = 0;
    }
    else if (smartcaps_enabled == 0)
    {
        smartcaps_enabled = 2;
        tap_oneshot_modifier(ONESHOT_LSFT);
    } 
}

uint16_t user_layer_get_code(uint16_t keycode, bool pressed)
{
    // Here we need to check the status of VIM, if VIM is active and
    // in NORMAL mode we should read from LAYER_VIM. If VIM is active
    // and in NORMAL_RAISE mode we should read from LAYER_VIM_RAISE.
    uint8_t const ti = keycode - KL_00;
    if (pressed)
    {
        if ((current_layer == keyboard_get_layout()) && vim_mode() == VIM_MODE_NORMAL)
        {
            keycode = pgm_read_byte(&user_kb_layers[(LAYER_VIM)][ti]);
        }
        else
        {
            keycode = pgm_read_byte(&user_kb_layers[(current_layer)][ti]);
        }

        user_kb_state[ti] = keycode;
    }
    else
    {
        keycode           = user_kb_state[ti];
        user_kb_state[ti] = KC_NO;
    }
    return keycode;
}

void user_apply_keycode(uint16_t keycode, bool pressed)
{
    if (vim_mode() == VIM_MODE_NORMAL)
        return;

    if (keycode >= TC_RANGE_START && keycode <= TC_RANGE_END)
    {
        uint16_t kc = user_get_code16(keycode);
        if (kc != KC_NO)
        {
            if (pressed)
            {
                if (smartcaps_enabled == 1)
                {
                    if (kc >= KC_A && kc <= KC_Z)
                    {
                        kc = LSFT(kc);
                    }
                    else
                    {
                        if (kc == KC_SCLN)
                        {
                            kc = KC_UNDS;
                        }
                    }
                    register_code16(kc);
                }
                else if (smartcaps_enabled == 2)
                {
                    register_code16(kc);
                }
                else
                {
                    register_code16(kc);
                }
            }
            else
            {
                if (smartcaps_enabled == 1)
                {
                    if (kc >= KC_A && kc <= KC_Z)
                    {
                        kc = LSFT(kc);
                    }
                    else
                    {
                        if (kc == KC_SCLN)
                        {
                            kc = KC_UNDS;
                        }
                    }
                    unregister_code16(kc);
                }
                else if (smartcaps_enabled == 2)
                {
                    unregister_code16(kc);
                    if (keycode == TC_SPACE)
                    {
                        tap_oneshot_modifier(ONESHOT_LSFT);
                    }
                }
                else
                {
                    unregister_code16(kc);
                }
            }
        }
    }
}
