#include QMK_KEYBOARD_H


#define LAYOUTX( \
    L01, L02, L03, L04, L05,                 R05, R04, R03, R02, R01, \
    L06, L07, L08, L09, L10,                 R10, R09, R08, R07, R06, \
	L11, L12, L13, L14, L15, L90        R90, R15, R14, R13, R12, R11, \
	          L91, L92, L16, L17,       R17, R16, R91, R92 \
) \
{ \
  { L05, L10, L15, L17,    R05, R10, R15, R17   }, \
  { L04, L09, L14, L16,    R04, R09, R14, R16   }, \
  { L03, L08, L13, KC_NO,  R03, R08, R13, KC_NO }, \
  { L02, L07, L12, KC_NO,  R02, R07, R12, KC_NO }, \
  { L01, L06, L11, KC_NO,  R01, R06, R11, KC_NO }, \
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
    KC_PLUS, KC_MINUS, KC_ASTR, KC_SLASH, KC_NO,                              KC_6,    KC_0,     KC_9,     KC_8,   KC_7,  
    KC_7,    KC_8,     KC_9,    KC_0,     KC_6,                               KC_5,    KC_1,     KC_2,     KC_3,   KC_4,  
    CC_CMD,  CC_ALT,   CC_CTRL, CC_SHFT,  KC_NO,   KC_NO,          KC_NO,     KC_NO,   KC_EQUAL, KC_COMMA, KC_DOT, KC_NO, 
                       CC_FNUM, CC_FNUM,  CC_FNAV, KC_SPACE,       KC_BSPACE, CC_FSYM, CC_FCAPS, CC_FCAPS                 
    ),
    [LAYER_SYMBOLS] = LAYOUTX(
    KC_PERC, KC_AMPR,  KC_PIPE, KC_UNDS,   KC_TILD,                            KC_GRV,  KC_QUOT,  KC_DQUO,  KC_HASH, KC_DLR,  
    KC_EXLM, KC_MINUS, KC_PLUS, KC_EQUAL,  KC_LBRC,                            KC_LABK, KC_LPRN,  KC_LCBR,  KC_SCLN, KC_COLN, 
    KC_CIRC, KC_SLASH, KC_ASTR, KC_BSLASH, KC_RBRC, CC_NDOC,        CC_PDOC,   KC_RABK, KC_RPRN,  KC_RCBR,  KC_QUES, KC_AT,   
                       CC_FCNT, CC_FCNT,   CC_FNAV, KC_SPACE,       KC_BSPACE, CC_FSYM, CC_FCNT,  CC_FCNT
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
    )
};

