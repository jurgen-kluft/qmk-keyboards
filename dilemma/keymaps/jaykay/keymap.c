#include QMK_KEYBOARD_H
#include "layouts.h"
#include "user_layers.h"
#include "user_keycodes.h"

#define MATRIX_ROWS 8 // Rows are doubled-up.
#define MATRIX_COLS 5


// clang-format off
#define LAYOUTX(                                                  \
  k00, k01, k02, k03, k04,               k44, k43, k42, k41, k40, \
  k10, k11, k12, k13, k14,               k54, k53, k52, k51, k50, \
  k20, k21, k22, k23, k24, k90,     k91, k64, k63, k62, k61, k60, \
            k92, k93, k30, k32,     k72, k70, k94, k95            \
)                                                       \
{                                                       \
  {   k00,   k01,   k02,   k03,   k04 },                \
  {   k10,   k11,   k12,   k13,   k14 },                \
  {   k20,   k21,   k22,   k23,   k24 },                \
  {   k30, KC_NO,   k32, KC_NO, KC_NO },                \
  {   k40,   k41,   k42,   k43,   k44 },                \
  {   k50,   k51,   k52,   k53,   k54 },                \
  {   k60,   k61,   k62,   k63,   k64 },                \
  {   k70, KC_NO,   k72, KC_NO, KC_NO },                \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_QWERTY] = LAYOUTX(
    KC_Q, KC_W, KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,     KC_I,     KC_O,   KC_P,    
    KC_A, KC_S, KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,     KC_K,     KC_L,   KC_SCLN, 
    KC_Z, KC_X, KC_C,    KC_V,    KC_B,    CC_PDT,         CC_NDT,    KC_N,    KC_M,     KC_COMMA, KC_DOT, KC_AT,   
                CC_FNUM, CC_FNUM, CC_FNAV, KC_SPACE,       KC_BSPACE, CC_FSYM, CC_FCAPS, CC_FCAPS                   
    ),
    [LAYER_RSTHD] = LAYOUTX(
    KC_J,    KC_C, KC_Y,    KC_F,    KC_K,                            KC_Z,    KC_L,     KC_BSPACE, KC_U,   KC_Q,  
    KC_R,    KC_S, KC_T,    KC_H,    KC_D,                            KC_M,    KC_N,     KC_A,      KC_I,   KC_O,  
    KC_SCLN, KC_V, KC_G,    KC_P,    KC_B,    CC_PDT,         CC_NDT, KC_X,    KC_W,     KC_COMMA,  KC_DOT, KC_AT, 
                   CC_FNUM, CC_FNUM, CC_FNAV, KC_SPACE,       KC_E,   CC_FSYM, CC_FCAPS, CC_FCAPS                  
    ),
    [LAYER_NUMBERS] = LAYOUTX(
    KC_7,    KC_8,     KC_9,    KC_0,     KC_6,                               KC_6,    KC_0,     KC_9,     KC_8,   KC_7,  
    CC_CMD,  CC_ALT,   CC_CTRL, CC_SHFT,  KC_5,                               KC_5,    KC_1,     KC_2,     KC_3,   KC_4,  
    KC_NO,   KC_NO,    KC_NO,   KC_NO,    KC_X,    KC_NO,          KC_NO,     KC_B,    KC_NO,    KC_COMMA, KC_DOT, KC_NO, 
                       CC_FNUM, CC_FNUM,  CC_FNAV, KC_SPACE,       KC_BSPACE, CC_FSYM, CC_FCAPS, CC_FCAPS                 
    ),
    [LAYER_SYMBOLS] = LAYOUTX(
    KC_PERC, KC_AMPR,  KC_PIPE, KC_UNDS,   KC_TILD,                            KC_GRV,  KC_QUOT,  KC_DQUO,  KC_HASH, KC_DLR,  
    KC_EXLM, KC_MINUS, KC_PLUS, KC_EQUAL,  KC_LBRC,                            KC_LABK, KC_LPRN,  KC_LCBR,  KC_SCLN, KC_COLN, 
    KC_CIRC, KC_SLASH, KC_ASTR, KC_BSLASH, KC_RBRC, CC_NDOC,        CC_PDOC,   KC_RABK, KC_RPRN,  KC_RCBR,  KC_QUES, KC_AT,   
                       KC_NO,   KC_NO,     CC_FNAV, KC_SPACE,       KC_BSPACE, CC_FSYM, KC_NO,    KC_NO
    ),
    [LAYER_NAVIGATION] = LAYOUTX(
    CC_REDO, CC_CLOSE, KC_ESCAPE, KC_ENTER, KC_TAB,                               KC_INSERT, CC_PGUP,   KC_HOME,  KC_NO,    KC_NO, 
    CC_CMD,  CC_ALT,   CC_CTRL,   CC_SHFT,  KC_DELETE,                            KC_LEFT,   KC_DOWN,   KC_UP,    KC_RIGHT, KC_NO, 
    CC_UNDO, CC_CUT,   CC_COPY,   CC_PASTE, KC_NO,     CC_NAPP,        CC_PAPP,   KC_NO,     CC_PGDOWN, KC_END,   KC_NO,    KC_NO, 
                       CC_FNUM,   CC_FNUM,  CC_FNAV,   KC_SPACE,       KC_BSPACE, CC_FSYM,   CC_FCAPS,  CC_FCAPS                   
    ),
    [LAYER_RAISE] = LAYOUTX(
    CC_SECRET_5, CC_SECRET_6, CC_SECRET_7, CC_SECRET_8, KC_NO,                                KC_F12,   KC_F2,    KC_F3,    KC_F4, KC_F1, 
    CC_CMD,      CC_ALT,      CC_CTRL,     CC_SHFT,     KC_NO,                                KC_F5,    KC_F11,   KC_F10,   KC_F9, KC_NO, 
    CC_SECRET_1, CC_SECRET_2, CC_SECRET_3, CC_SECRET_4, KC_NO,     CC_PDT,         CC_NDT,    KC_NO,    KC_F6,    KC_F7,    KC_F8, KC_NO, 
                              CC_FNUM,     CC_FNUM,     CC_FNAV,   KC_SPACE,       KC_BSPACE, CC_FSYM,  CC_FCAPS, CC_FCAPS                
    ),
    [LAYER_MOUSE] = LAYOUTX(
    KC_NO, KC_NO, KC_NO,   SNIPING, KC_NO,                    KC_WH_U, DPI_RMOD,DPI_MOD, S_D_RMOD,S_D_MOD,
    KC_NO, KC_NO, KC_BTN2, KC_BTN1, KC_NO,                    KC_WH_D, KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN6,
    KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO, KC_BTN7, KC_BTN4, KC_BTN5, KC_BTN8, KC_NO,
                  KC_NO,   KC_NO,   CC_FNAV, KC_NO,    KC_NO, KC_NO,   KC_NO,   KC_NO
    )
};

// clang-format on

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    for (int32_t i = 0; i < 40; i++) {
        __asm__ volatile("nop" ::: "memory");
    }
}


