#pragma once

enum ecustom_layers
{
    LAYER_QWERTY = 0,
    LAYER_RSTHD,
    LAYER_GRAPHITE,
    LAYER_ENGRAM2,
    LAYER_STURDY,
    LAYER_NUMBERS,
    LAYER_SYMBOLS,
    LAYER_NAVIGATION,
    LAYER_RAISE,
    LAYER_MOUSE,
    LAYER_GAMEL,
    LAYER_GAMER,
    LAYER_NONE = -1,
    LAYER_BASE = LAYER_QWERTY,
};

void user_layer_base(int8_t layer);
void user_layer_on(int8_t layer);
int8_t user_layer_current(void);

void register_keycode_press(uint16_t kc);
void register_keycode_press_with_shift(uint16_t kc);
void register_keycode_press_nomods(uint16_t kc);
void register_keycode_release(uint16_t kc);
void register_keycode_release_nomods(uint16_t kc);
void tap_code16_nomods(uint16_t kc);
void tap_code16_shift(uint16_t kc);
void register_string(const char *str);
