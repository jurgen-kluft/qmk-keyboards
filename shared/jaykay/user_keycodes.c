#include QMK_KEYBOARD_H
#include "config.h"
#include "layers.h"
#include "user_keycodes.h"

// clang-format off
static const uint16_t kb_keycodes[TC_RANGE_COUNT] = {
    [TC_0] = KC_0,
    [TC_1] = KC_1,
    [TC_2] = KC_2,
    [TC_3] = KC_3,
    [TC_4] = KC_4,
    [TC_5] = KC_5,
    [TC_6] = KC_6,
    [TC_7] = KC_7,
    [TC_8] = KC_8,
    [TC_9] = KC_9,
    [TC_A] = KC_A,
    [TC_B] = KC_B,
    [TC_C] = KC_C,
    [TC_D] = KC_D,
    [TC_E] = KC_E,
    [TC_F] = KC_F,
    [TC_G] = KC_G,
    [TC_H] = KC_H,
    [TC_I] = KC_I,
    [TC_J] = KC_J,
    [TC_K] = KC_K,
    [TC_L] = KC_L,
    [TC_M] = KC_M,
    [TC_N] = KC_N,
    [TC_O] = KC_O,
    [TC_P] = KC_P,
    [TC_Q] = KC_Q,
    [TC_R] = KC_R,
    [TC_S] = KC_S,
    [TC_T] = KC_T,
    [TC_U] = KC_U,
    [TC_V] = KC_V,
    [TC_W] = KC_W,
    [TC_X] = KC_X,
    [TC_Y] = KC_Y,
    [TC_Z] = KC_Z,
    [TC_AT] = KC_AT,
    [TC_F1] = KC_F1,
    [TC_F2] = KC_F2,
    [TC_F3] = KC_F3,
    [TC_F4] = KC_F4,
    [TC_F5] = KC_F5,
    [TC_F6] = KC_F6,
    [TC_F7] = KC_F7,
    [TC_F8] = KC_F8,
    [TC_F9] = KC_F9,
    [TC_UP] = KC_UP,
    [TC_DLR] = KC_DLR,
    [TC_DOT] = KC_DOT,
    [TC_END] = KC_END,
    [TC_F10] = KC_F10,
    [TC_F11] = KC_F11,
    [TC_F12] = KC_F12,
    [TC_GRV] = KC_GRV,
    [TC_TAB] = KC_TAB,
    [TC_AMPR] = KC_AMPR,
    [TC_ASTR] = KC_ASTR,
    [TC_CIRC] = KC_CIRC,
    [TC_COLN] = KC_COLN,
    [TC_DOWN] = KC_DOWN,
    [TC_DQUO] = KC_DQUO,
    [TC_EXLM] = KC_EXLM,
    [TC_HASH] = KC_HASH,
    [TC_UNDS] = KC_UNDS,
    [TC_HOME] = KC_HOME,
    [TC_LABK] = KC_LABK,
    [TC_LBRC] = KC_LBRC,
    [TC_LCBR] = KC_LCBR,
    [TC_LEFT] = KC_LEFT,
    [TC_LPRN] = KC_LPRN,
    [TC_PERC] = KC_PERC,
    [TC_PGUP] = KC_PGUP,
    [TC_PIPE] = KC_PIPE,
    [TC_PLUS] = KC_PLUS,
    [TC_QUES] = KC_QUES,
    [TC_QUOT] = KC_QUOT,
    [TC_RABK] = KC_RABK,
    [TC_RBRC] = KC_RBRC,
    [TC_RCBR] = KC_RCBR,
    [TC_RPRN] = KC_RPRN,
    [TC_SCLN] = KC_SCLN,
    [TC_TILD] = KC_TILD,
    [TC_COMMA] = KC_COMMA,
    [TC_ENTER] = KC_ENTER,
    [TC_EQUAL] = KC_EQUAL,
    [TC_MINUS] = KC_MINUS,
    [TC_RIGHT] = KC_RIGHT,
    [TC_SLASH] = KC_SLASH,
    [TC_SPACE] = KC_SPACE,
    [TC_BSLASH] = KC_BSLASH,
    [TC_BSPACE] = KC_BSPACE,
    [TC_DELETE] = KC_DELETE,
    [TC_ESCAPE] = KC_ESCAPE,
    [TC_INSERT] = KC_INSERT,
    [TC_PGDOWN] = KC_PGDOWN
};
// clang-format on

uint16_t user_get_code16(uint16_t keycode)
{
    return kb_keycodes[keycode];
}