#pragma once

enum ecustom_layers
{
    LAYER_QWERTY = 0,
    LAYER_RSTHD,
    LAYER_NUMBERS,
    LAYER_SYMBOLS,
    LAYER_NAVIGATION,
    LAYER_RAISE,
    LAYER_VIM,
    LAYER_GAMEL,
    LAYER_GAMER,
    LAYER_NONE = -1,
    LAYER_BASE = LAYER_QWERTY,
};

void user_layer_base(int8_t layer);
void user_layer_on(int8_t layer);
int8_t user_layer_current(void);

uint8_t get_keycode_index(uint16_t kcb);
uint8_t get_keycode_code(uint8_t ti, bool pressed);

void register_keycode_press(uint8_t ti, uint8_t tc);
void register_keycode_press_with_shift(uint8_t ti, uint8_t tc);
void register_keycode_press_modmask(uint8_t ti, uint8_t tc, uint8_t modmask);
void register_keycode_release(uint8_t ti, uint8_t tc);

void register_keycode_tap(uint8_t ti, uint8_t tc);
void register_keycode_tap_with_shift(uint8_t ti, uint8_t tc);
