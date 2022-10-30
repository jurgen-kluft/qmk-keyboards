#include QMK_KEYBOARD_H
#include "cukey.h"
#include "user_keycodes.h"
#include "user_layers.h"

#undef LAYOUT
#define LAYOUT LAYOUT_moonlander

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_QWERTY] = LAYOUT(
   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,    KC_NO,  KC_NO,    KC_NO,  KC_NO,  KC_NO,     KC_NO,    KC_NO,  KC_NO,    CC_GAMEL, 
   KC_NO, KC_Q,  KC_W,  KC_E,    KC_R,     KC_T,   CC_NDT,   CC_PDT, KC_Y,   KC_U,      KC_I,     KC_O,   KC_P,     KC_NO,    
   KC_NO, KC_A,  KC_S,  KC_D,    KC_F,     KC_G,   CC_PDT,   CC_NDT, KC_H,   KC_J,      KC_K,     KC_L,   KC_SCLN,  KC_NO,    
   KC_NO, KC_Z,  KC_X,  KC_C,    KC_V,     KC_B,                     KC_N,   KC_M,      KC_COMMA, KC_DOT, KC_SLASH, KC_NO,    
   KC_NO, KC_NO, KC_NO, CC_FNUM, CC_FNAV,  CC_PDT,                   CC_NDT, CC_FSYM,   CC_FCAPS, KC_NO,  KC_NO,    CC_RSTHD, 
                                 KC_SPACE, KC_NO,  KC_NO,    KC_NO,  KC_NO,  KC_BSPACE                                        
  ),
  [LAYER_RSTHD] = LAYOUT(
   KC_NO, KC_NO,   KC_NO, KC_NO,   KC_NO,    KC_NO,     KC_NO,    KC_NO,  KC_NO,  KC_NO,   KC_NO,     KC_NO,  KC_NO,   CC_GAMEL,  
   KC_NO, KC_J,    KC_C,  KC_Y,    KC_F,     KC_K,      CC_NDT,   CC_PDT, KC_Z,   KC_L,    KC_BSPACE, KC_U,   KC_Q,    KC_NO,     
   KC_NO, KC_R,    KC_S,  KC_T,    KC_H,     KC_D,      CC_PDT,   CC_NDT, KC_M,   KC_N,    KC_A,      KC_I,   KC_O,    KC_NO,     
   KC_NO, KC_UNDS, KC_V,  KC_G,    KC_P,     KC_B,                        KC_X,   KC_W,    KC_COMMA,  KC_DOT, KC_SCLN, KC_NO,     
   KC_NO, KC_NO,   KC_NO, CC_FNUM, CC_FNAV,  CC_PDT,                      CC_NDT, CC_FSYM, CC_FCAPS,  KC_NO,  KC_NO,   CC_QWERTY, 
                                   KC_SPACE, KC_BSPACE, KC_NO,    KC_NO,  KC_NO,  KC_E                                            
  ),
  [LAYER_NUMBERS] = LAYOUT(
   KC_NO, KC_NO,   KC_NO,    KC_NO,   KC_NO,    KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,     KC_NO,    KC_NO,  KC_NO, KC_NO, 
   KC_NO, KC_PLUS, KC_MINUS, KC_ASTR, KC_SLASH, KC_NO, KC_NO,   KC_NO, KC_6,  KC_0,      KC_9,     KC_8,   KC_7,  KC_NO, 
   KC_NO, KC_7,    KC_8,     KC_9,    KC_0,     KC_6,  KC_NO,   KC_NO, KC_5,  KC_1,      KC_2,     KC_3,   KC_4,  KC_NO, 
   KC_NO, CC_CMD,  CC_ALT,   CC_CTRL, CC_SHFT,  KC_NO,                 KC_NO, KC_EQUAL,  KC_COMMA, KC_DOT, KC_NO, KC_NO, 
   KC_NO, KC_NO,   KC_NO,    CC_FNUM, KC_NO,    KC_NO,                 KC_NO, KC_NO,     KC_NO,    KC_NO,  KC_NO, KC_NO, 
                                      KC_SPACE, KC_NO, KC_NO,   KC_NO, KC_NO, KC_BSPACE                                  
  ),
  [LAYER_SYMBOLS] = LAYOUT(
   KC_NO, KC_NO,   KC_NO,    KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,     KC_NO,    KC_NO,   KC_NO,   KC_NO,     
   KC_NO, KC_PERC, KC_AMPR,  KC_PIPE, KC_UNDS,   KC_TILD, KC_NO,   KC_NO, KC_GRV,  KC_QUOT,   KC_DQUO,  KC_HASH, KC_DLR,  KC_NO,     
   KC_NO, KC_EXLM, KC_MINUS, KC_PLUS, KC_EQUAL,  KC_LBRC, KC_NO,   KC_NO, KC_LABK, KC_LPRN,   KC_LCBR,  KC_RABK, KC_COLN, KC_NO,     
   KC_NO, KC_CIRC, KC_SLASH, KC_ASTR, KC_BSLASH, KC_RBRC,                 KC_NO,   KC_RPRN,   KC_RCBR,  KC_QUES, KC_AT,   KC_NO,     
   KC_NO, KC_NO,   KC_NO,    CC_FNUM, CC_FNAV,   CC_PAPP,                 CC_NAPP, CC_FSYM,   CC_FCAPS, KC_NO,   KC_NO,   CC_QWERTY, 
                                      KC_SPACE,  KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_BSPACE                                         
  ),
  [LAYER_NAVIGATION] = LAYOUT(
   KC_NO, KC_NO,   KC_NO,    KC_NO,     KC_NO,    KC_NO,     KC_NO,   KC_NO, KC_NO,     KC_NO,     KC_NO,   KC_NO,    KC_NO, KC_NO, 
   KC_NO, KC_NO,   CC_CLOSE, KC_ESCAPE, KC_ENTER, KC_TAB,    KC_NO,   KC_NO, KC_INSERT, KC_PGUP,   KC_HOME, KC_NO,    KC_NO, KC_NO, 
   KC_NO, CC_CMD,  CC_ALT,   CC_CTRL,   CC_SHFT,  KC_DELETE, KC_NO,   KC_NO, KC_LEFT,   KC_DOWN,   KC_UP,   KC_RIGHT, KC_NO, KC_NO, 
   KC_NO, CC_UNDO, CC_CUT,   CC_COPY,   CC_PASTE, KC_NO,                     KC_DELETE, KC_PGDOWN, KC_END,  KC_NO,    KC_NO, KC_NO, 
   KC_NO, KC_NO,   KC_NO,    KC_NO,     CC_FNAV,  CC_PDOC,                   CC_NDOC,   CC_FSYM,   KC_NO,   KC_NO,    KC_NO, KC_NO, 
                                        KC_NO,    KC_NO,     KC_NO,   KC_NO, KC_NO,     KC_BSPACE                                   
  ),
  [LAYER_RAISE] = LAYOUT(
   KC_NO, KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,     KC_NO,   KC_NO, KC_NO,    KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, 
   KC_NO, CC_SECRET_5, CC_SECRET_6, CC_SECRET_7, CC_SECRET_8, KC_NO,     KC_NO,   KC_NO, KC_F12,   KC_F2,  KC_F3,  KC_F4, KC_F1, KC_NO, 
   KC_NO, CC_CMD,      CC_ALT,      CC_CTRL,     CC_SHFT,     KC_NO,     KC_NO,   KC_NO, KC_F5,    KC_F11, KC_F10, KC_F9, KC_NO, KC_NO, 
   KC_NO, CC_SECRET_1, CC_SECRET_2, CC_SECRET_3, CC_SECRET_4, KC_NO,                     KC_NO,    KC_F6,  KC_F7,  KC_F8, KC_NO, KC_NO, 
   KC_NO, KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,                     KC_NO,    KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, 
                                                 KC_NO,       KC_NO,     KC_NO,   KC_NO, KC_NO,    KC_NO                                
  ),
  [LAYER_GAMEL] = LAYOUT(
   KC_NO,     KC_1,  KC_2,     KC_3,     KC_4,     KC_5,      KC_NO,   KC_0,  KC_6,  KC_7,    KC_8,      KC_9,   KC_NO,    CC_GAMEL, 
   KC_TAB,    KC_Q,  KC_W,     KC_E,     KC_R,     KC_T,      KC_NO,   KC_NO, KC_Y,  KC_U,    KC_I,      KC_O,   KC_P,     KC_NO,    
   KC_ESCAPE, KC_A,  KC_S,     KC_D,     KC_F,     KC_G,      KC_NO,   KC_NO, KC_H,  KC_J,    KC_K,      KC_L,   KC_SCLN,  KC_NO,    
   KC_LSHIFT, KC_Z,  KC_X,     KC_C,     KC_V,     KC_B,                      KC_N,  KC_M,    KC_COMMA,  KC_DOT, KC_SLASH, KC_NO,    
   KC_NO,     KC_NO, CC_GAMER, KC_LCTRL, KC_LALT,  KC_ENTER,                  KC_NO, KC_LALT, KC_LSHIFT, KC_NO,  KC_NO,    KC_NO,    
                                         KC_SPACE, KC_BSPACE, KC_NO,   KC_NO, KC_NO, KC_NO                                           
  ),
  [LAYER_GAMER] = LAYOUT(
   KC_NO,     KC_0,     KC_9,   KC_8,     KC_7,     KC_6,      KC_NO,   KC_0,  KC_6,  KC_7,    KC_8,     KC_9,   KC_NO,    KC_NO,     
   KC_NO,     KC_P,     KC_O,   KC_I,     KC_U,     KC_Y,      KC_NO,   KC_NO, KC_Y,  KC_U,    KC_I,     KC_O,   KC_P,     KC_NO,     
   KC_ESCAPE, KC_SCLN,  KC_L,   KC_K,     KC_J,     KC_H,      KC_NO,   KC_NO, KC_H,  KC_J,    KC_K,     KC_L,   KC_SCLN,  KC_NO,     
   KC_LSHIFT, KC_SLASH, KC_DOT, KC_COMMA, KC_M,     KC_N,                      KC_N,  KC_M,    KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT, 
   KC_NO,     KC_NO,    KC_NO,  KC_LCTRL, KC_LALT,  KC_ENTER,                  KC_NO, KC_LALT, KC_LCTRL, KC_NO,  KC_NO,    KC_NO,     
                                          KC_SPACE, KC_BSPACE, KC_NO,   KC_NO, KC_NO, KC_NO                                           
  )
};

/*
qmk-keyboard-format:json:begin
{
    "name": "moonlander",
    "numkeys": 72,
    "rows": [
        [ -3,  0,  1,  2,  3,  4,  5,  6, -2,  7,  8,  9, 10, 11, 12, 13 ],
        [ -3, 14, 15, 16, 17, 18, 19, 20, -2, 21, 22, 23, 24, 25, 26, 27 ],
        [ -3, 28, 29, 30, 31, 32, 33, 34, -2, 35, 36, 37, 38, 39, 40, 41 ],
        [ -3, 42, 43, 44, 45, 46, 47, -1, -2, -1, 48, 49, 50, 51, 52, 53 ],
        [ -3, 54, 55, 56, 57, 58, 59, -1, -2, -1, 60, 61, 62, 63, 64, 65 ],
        [ -3, -1, -1, -1, -1, 66, 67, 68, -2, 69, 70, 71, -1, -1, -1, -1 ]
    ],
    "spacing": [
        0,
        0,
        0,
        1
    ],
    "vizcellwidth": 5,
    "vizboard": [
        " // ",
        " // .-----------------------------------------------.                                             .-----------------------------------------------.",
        " // | _000_ | _001_ | _002_ | _003_ | _004_ | _005_ |                                             | _006_ | _007_ | _008_ | _009_ | _010_ | _011_ |",
        " // |-------+-------+-------+-------+-------+-------|                                             |-------+-------+-------+-------+-------+-------|",
        " // | _012_ | _013_ | _014_ | _015_ | _016_ | _017_ |                                             | _018_ | _019_ | _020_ | _021_ | _022_ | _023_ |",
        " // |-------+-------+-------+-------+-------+-------|-------+-------.             .-------+-------|-------+-------+-------+-------+-------+-------|",
        " // | _024_ | _025_ | _026_ | _027_ | _028_ | _029_ | _030_ | _031_ |             | _032_ | _033_ | _034_ | _035_ | _036_ | _037_ | _038_ | _039_ |",
        " // .-------+-------+-------+-------+-------+-------+-------+-------|             |-------+-------.-------+-------+-------+-------+-------+-------.",
        " //                         | _040_ | _041_ | _042_ | _043_ | _044_ |             | _045_ | _046_ | _047_ | _048_ | _049_ |                        ",
        " //                         .-------+-------+-------+-------+-------.             .-------|-------|-------|-------|-------.                        ",
        " // "
    ],
    "vizsymbols": {
        "_______": "     ",
        "KC_TRANS": "     ",
        "KC_0": "  0  " ,
        "KC_1": "  1  " ,
        "KC_2": "  2  " ,
        "KC_3": "  3  " ,
        "KC_4": "  4  " ,
        "KC_5": "  5  " ,
        "KC_6": "  6  " ,
        "KC_7": "  7  " ,
        "KC_8": "  8  " ,
        "KC_9": "  9  " ,
        "KC_A": "  A  " ,
        "KC_B": "  B  " ,
        "KC_C": "  C  " ,
        "KC_D": "  D  " ,
        "KC_E": "  E  " ,
        "KC_F": "  F  " ,
        "KC_G": "  G  " ,
        "KC_H": "  H  " ,
        "KC_I": "  I  " ,
        "KC_J": "  J  " ,
        "KC_K": "  K  " ,
        "KC_L": "  L  " ,
        "KC_M": "  M  " ,
        "KC_N": "  N  " ,
        "KC_O": "  O  " ,
        "KC_P": "  P  " ,
        "KC_Q": "  Q  " ,
        "KC_R": "  R  " ,
        "KC_S": "  S  " ,
        "KC_T": "  T  " ,
        "KC_U": "  U  " ,
        "KC_V": "  V  " ,
        "KC_W": "  W  " ,
        "KC_X": "  X  " ,
        "KC_Y": "  Y  " ,
        "KC_Z": "  Z  " ,
        "KC_COMMA": "  ,  ",
        "KC_COMM": "  ,  ",
        "KC_DOT": "  .  ",
        "KC_SCLN": "  ;  ",
        "KC_SCLN": "  :  ",
        "KC_SLASH": "  \/  ",
        "KC_SLSH": "  \/  ",
        "KC_BSLS": "  \\  ",
        "KC_EXLM": "  !  ",
        "KC_PIPE": "  |  ",
        "KC_QUOT": "  '  ",
        "KC_HASH": "  #  ",
        "KC_AMPR": "  &  ",
        "KC_PERC": "  %  ",
        "KC_AT": "  @  ",
        "KC_DLR": "  $  ",
        "KC_CIRC": "  ^  ",
        "KC_EQL": "  =  ",
        "KC_ASTR": "  *  ",
        "KC_MINS": "  -  ",
        "KC_PLUS": "  +  ",
        "KC_LCBR": "  {  ",
        "KC_RCBR": "  }  ",
        "KC_LPRN": "  (  ",
        "KC_RPRN": "  )  ",
        "KC_GRV": "  `  ",
        "KC_LBRC": "  [  ",
        "KC_RBRC": "  ]  ",
        "KC_TILD": "  ~  ",
        "KC_ESC": "  ⎋  " ,
        "KC_CUT": "  ✄  " ,
        "KC_UNDO": "  ↶  " ,
        "KC_REDO": "  ↷  " ,
        "KC_VOLU": "  🕪  " ,
        "KC_VOLD": "  🕩  " ,
        "KC_MUTE":   "  🕨  " ,
        "KC_TAB": "  ⭾  " ,
        "KC_MENU": "  𝌆  " ,
        "KC_CAPSLOCK": "  ⇪  " ,
        "KC_NUMLK": "  ⇭  " ,
        "KC_SCRLK": "  ⇳  " ,
        "KC_PRSCR": "  ⎙  " ,
        "KC_PAUSE": "  ⎉  " ,
        "KC_BREAK": "  ⎊  " ,
        "KC_ENTER": "  ⏎  " ,
        "KC_BSPACE": "  ⌫  " ,
        "KC_DELETE": "  ⌦ " ,
        "KC_INSERT": "  ⎀  " ,
        "KC_LEFT": "  ◁  " ,
        "KC_RIGHT": "  ▷  " ,
        "KC_UP": "  △  " ,
        "KC_DOWN": "  ▽  " ,
        "KC_HOME": "  ⇤  " ,
        "KC_END": "  ⇥  " ,
        "KC_PGUP": "  ⇞  " ,
        "KC_PGDOWN": "  ⇟  " ,
        "KC_LSFT": "  ⇧  " ,
        "KC_RSFT": "  ⇧  " ,
        "KC_LCTL": "  ^  " ,
        "KC_RCTL": "  ^  " ,
        "KC_LALT": "  ⎇  " ,
        "KC_RALT": "  ⎇  " ,
        "KC_HYPER": "  ✧  " ,
        "KC_LGUI": "  ⌘  " ,
        "KC_RGUI": "  ⌘  "
    }
}
qmk-keyboard-format:json:end
*/