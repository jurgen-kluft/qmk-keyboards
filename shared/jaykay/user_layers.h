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
};

void user_layer_on(uint8_t layer);
void user_layer_off(uint8_t layer);
uint8_t user_current_layer(void);

void user_smartshift_on(void);
void user_smartshift_off(void);

uint16_t user_layer_get_code(uint16_t keycode, bool pressed);
void user_apply_keycode(uint16_t keycode, bool pressed);