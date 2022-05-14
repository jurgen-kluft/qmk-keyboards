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
    LAYER_VIM_RAISE,
    LAYER_NONE = -1,
    LAYER_BASE = LAYER_QWERTY,
};

void user_layer_base(int8_t layer);
void user_layer_on(int8_t layer);
int8_t user_layer(void);

void user_smartcaps_on(void);
void user_smartcaps_off(void);

uint16_t user_layer_get_code(uint16_t keycode, bool pressed);
void user_apply_keycode(uint16_t keycode, bool pressed);