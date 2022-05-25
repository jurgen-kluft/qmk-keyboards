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
static int8_t smart_repeat      = 1;

enum esmartcaps
{
    SMARTCAPS_OFF               = 0,
    SMARTCAPS_ON                = 1,
    SMARTCAPS_CAMELCASE         = 2,
    SMARTCAPS_CAMELCASE_SHIFT   = 3,
    SMARTCAPS_CAMELCASE_SHIFTED = 4,
};

void user_smartcaps_on(void) { smartcaps_enabled = SMARTCAPS_ON; }
void user_smartcaps_off(void) { smartcaps_enabled = SMARTCAPS_OFF; }

void user_camelcase_toggle(void)
{
    if (smartcaps_enabled >= SMARTCAPS_CAMELCASE)
    {
        smartcaps_enabled = SMARTCAPS_OFF;
    }
    else
    {
        smartcaps_enabled = SMARTCAPS_CAMELCASE_SHIFT;
    }
}

static int8_t current_layer = LAYER_QWERTY;
void          user_layer_on(int8_t layer)
{
    switch (layer)
    {
        case LAYER_VIM:
        case LAYER_NUMBERS:
        case LAYER_SYMBOLS:
        case LAYER_NAVIGATION:
            smartcaps_enabled = SMARTCAPS_OFF;
            current_layer     = layer;
            break;
        case LAYER_RSTHD:
        case LAYER_QWERTY: current_layer = keyboard_get_layout(); break;
        case LAYER_RAISE:
        default: current_layer = layer; break;
    }
}

int8_t user_layer(void) { return current_layer; }

uint8_t user_layer_get_code(uint16_t keycode, bool pressed)
{
    // Here we need to check the status of VIM, if VIM is active and
    // in NORMAL mode we should read from LAYER_VIM. If VIM is active
    // and in NORMAL_RAISE mode we should read from LAYER_VIM_RAISE.
    uint8_t const ti = keycode - KL_00;
    uint8_t       tc;
    if (pressed)
    {
        if (current_layer == LAYER_SYMBOLS || current_layer == LAYER_NUMBERS)
        {
            tc = pgm_read_byte(&user_kb_layers[(current_layer)][ti]);
        }
        else if (vim_mode() == VIM_MODE_NORMAL)
        {
            tc = pgm_read_byte(&user_kb_layers[(LAYER_VIM)][ti]);
        }
        else
        {
            tc = pgm_read_byte(&user_kb_layers[(current_layer)][ti]);
        }

        user_kb_state[ti] = tc;
    }
    else
    {
        tc                = user_kb_state[ti];
        user_kb_state[ti] = KC_NO;
    }
    return tc;
}

void user_apply_keycode(uint8_t keycode, bool pressed)
{
    if (vim_mode() == VIM_MODE_NORMAL)
        return;

    if (keycode == CC_FCNT)
    {
        if (pressed)
        {
            smart_repeat += 1;
        }
    }

    if (keycode >= TC_RANGE_START && keycode <= TC_RANGE_END)
    {
        uint16_t qmk_keycode = user_get_code16(keycode);
        if (qmk_keycode != KC_NO)
        {
            if (pressed)
            {
                if (smartcaps_enabled == SMARTCAPS_ON)
                {
                    if (qmk_keycode >= KC_A && qmk_keycode <= KC_Z)
                    {
                        qmk_keycode = LSFT(qmk_keycode);
                    }
                    else
                    {
                        if (qmk_keycode == KC_SCLN)
                        {
                            qmk_keycode = KC_UNDS;
                        }
                    }
                    register_code16(qmk_keycode);
                }
                else if (smartcaps_enabled >= SMARTCAPS_CAMELCASE)
                {
                    if (qmk_keycode >= KC_A && qmk_keycode <= KC_Z)
                    {
                        if (smartcaps_enabled == SMARTCAPS_CAMELCASE_SHIFT)
                        {
                            tap_code16(LSFT(qmk_keycode));
                            smartcaps_enabled = SMARTCAPS_CAMELCASE;
                        }
                        else
                        {
                            register_code16(qmk_keycode);
                        }
                    }
                    else if (qmk_keycode == KC_SPACE || qmk_keycode == KC_BSPACE)
                    {
                        register_code16(qmk_keycode);
                    }
                }
                else
                {
                    while (smart_repeat > 1)
                    {
                        tap_code16(qmk_keycode);
                        smart_repeat--;
                    }
                    register_code16(qmk_keycode);
                }
            }
            else
            {
                if (smartcaps_enabled == SMARTCAPS_ON)
                {
                    if (qmk_keycode >= KC_A && qmk_keycode <= KC_Z)
                    {
                        qmk_keycode = LSFT(qmk_keycode);
                    }
                    else
                    {
                        if (qmk_keycode == KC_SCLN)
                        {
                            qmk_keycode = KC_UNDS;
                        }
                    }
                    unregister_code16(qmk_keycode);
                }
                else if (smartcaps_enabled >= SMARTCAPS_CAMELCASE)
                {
                    if (qmk_keycode >= KC_A && qmk_keycode <= KC_Z)
                    {
                        unregister_code16(qmk_keycode);
                    }
                    else if (qmk_keycode == KC_BSPACE)
                    {
                        unregister_code16(qmk_keycode);
                    }
                    else if (qmk_keycode == KC_SPACE)
                    {
                        unregister_code16(qmk_keycode);
                        smartcaps_enabled = SMARTCAPS_CAMELCASE_SHIFT;
                    }
                    else if (qmk_keycode == KC_COMMA)
                    {
                        smartcaps_enabled = SMARTCAPS_CAMELCASE_SHIFT;
                    }
                    else
                    {
                        smartcaps_enabled = SMARTCAPS_OFF;
                    }
                }
                else
                {
                    unregister_code16(qmk_keycode);
                }

                smart_repeat = 1;
            }
        }
    }
}
