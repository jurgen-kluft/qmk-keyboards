#include QMK_KEYBOARD_H
#include "config.h"
#include "cukey.h"
#include "vim.h"
#include "oneshot.h"
#include "user_layers.h"
#include "user_keycodes.h"

#if defined(KEYBOARD_HILLSIDE) || defined(KEYBOARD_KYRIA)

static uint8_t               user_kb_state[40] = {TC_NO};
static uint16_t              qmk_kb_state[40]  = {KC_NO};
extern const uint8_t PROGMEM user_kb_layers[][40];

#elif defined(KEYBOARD_MOONLANDER)

static uint8_t               user_kb_state[72] = {TC_NO};
static uint16_t              qmk_kb_state[72]  = {KC_NO};
extern const uint8_t PROGMEM user_kb_layers[][72];

#endif

static int8_t smart_repeat  = 1;
static int8_t current_layer = LAYER_QWERTY;
void          user_layer_on(int8_t layer)
{
    switch (layer)
    {
        case LAYER_RSTHD:
        case LAYER_QWERTY: current_layer = keyboard_get_layout(); break;

        case LAYER_VIM:
        case LAYER_NUMBERS:
        case LAYER_SYMBOLS:
        case LAYER_NAVIGATION:
        case LAYER_RAISE:
        default: current_layer = layer; break;
    }
}

int8_t user_layer(void) { return current_layer; }

uint8_t get_keycode_index(uint16_t kcb) { return kcb - KL_00; }
uint8_t get_keycode_code(uint8_t ti, bool pressed)
{
    // Here we need to check the status of VIM, if VIM is active and
    // in NORMAL mode we should read from LAYER_VIM. If VIM is active
    // and in NORMAL_RAISE mode we should read from LAYER_VIM_RAISE.
    uint8_t tc;
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
        user_kb_state[ti] = TC_NO;
    }
    return tc;
}

void register_keycode_press(uint8_t ti, uint8_t tc)
{
    if (tc >= TC_RANGE_START && tc <= TC_RANGE_END)
    {
        uint16_t qmk_keycode = user_get_code16(tc);
        if (qmk_keycode != KC_NO)
        {
            while (smart_repeat > 1)
            {
                tap_code16(qmk_keycode);
                smart_repeat--;
            }
            register_code16(qmk_keycode);
            qmk_kb_state[ti] = qmk_keycode;
        }
    }
    else if (tc == CC_FCNT)
    {
        smart_repeat += 1;
    }
}

void register_keycode_press_with_shift(uint8_t ti, uint8_t tc)
{
    if (tc >= TC_RANGE_START && tc <= TC_RANGE_END)
    {
        uint16_t qmk_keycode = user_get_code16(tc);
        if (qmk_keycode != KC_NO)
        {
            if (tc >= TC_A && tc <= TC_Z)
            {
                qmk_keycode = LSFT(qmk_keycode);
            }

            while (smart_repeat > 1)
            {
                tap_code16(qmk_keycode);
                smart_repeat--;
            }
            register_code16(qmk_keycode);
            qmk_kb_state[ti] = qmk_keycode;
        }
    }
    else if (tc == CC_FCNT)
    {
        smart_repeat += 1;
    }
}

void register_keycode_release(uint8_t ti, uint8_t tc)
{
    if (tc >= TC_RANGE_START && tc <= TC_RANGE_END)
    {
        uint16_t qmk_keycode = qmk_kb_state[ti];
        if (qmk_keycode != KC_NO)
        {
            unregister_code16(qmk_keycode);
        }
        qmk_kb_state[ti] = KC_NO;
    }
}

void register_keycode_tap(uint8_t ti, uint8_t tc)
{
    if (tc >= TC_RANGE_START && tc <= TC_RANGE_END)
    {
        uint16_t qmk_keycode = user_get_code16(tc);
        tap_code16(qmk_keycode);
    }
}

void register_keycode_tap_with_shift(uint8_t ti, uint8_t tc)
{
    if (tc >= TC_RANGE_START && tc <= TC_RANGE_END)
    {
        uint16_t qmk_keycode = user_get_code16(tc);
        qmk_keycode          = LSFT(qmk_keycode);
        tap_code16(qmk_keycode);
    }
}
