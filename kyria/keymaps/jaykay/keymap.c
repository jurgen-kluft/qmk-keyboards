#include QMK_KEYBOARD_H
#include "user_layers.h"
#include "user_keycodes.h"

#define XXX KC_NO

// clang-format off
#define LAYOUTX( \
    L01, L02, L03, L04, L05,                     R06, R07, R08, R09, R10, \
    L13, L14, L15, L16, L17,                     R18, R19, R20, R21, R22, \
    L25, L26, L27, L28, L29, L30,           R33, R34, R35, R36, R37, R38, \
              L40, L41, L42, L43,           R46, R47, R48, R49 \
) \
{ \
    { XXX, XXX, L05, L04, L03, L02, L01, XXX }, \
    { XXX, XXX, L17, L16, L15, L14, L13, XXX }, \
    { XXX, L30, L29, L28, L27, L26, L25, XXX }, \
    { XXX, L43, L42, L41, XXX, L40, XXX, XXX }, \
    { XXX, XXX, R06, R07, R08, R09, R10, XXX }, \
    { XXX, XXX, R18, R19, R20, R21, R22, XXX }, \
    { XXX, R33, R34, R35, R36, R37, R38, XXX }, \
    { XXX, R46, R47, R48, XXX, R49, XXX, XXX }, \
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
    )
    [LAYER_MOUSE] = LAYOUTX(
    CC_SECRET_5, CC_SECRET_6, CC_SECRET_7, CC_SECRET_8, KC_NO,                                KC_F12,   KC_F2,    KC_F3,    KC_F4, KC_F1, 
    CC_CMD,      CC_ALT,      CC_CTRL,     CC_SHFT,     KC_NO,                                KC_F5,    KC_F11,   KC_F10,   KC_F9, KC_NO, 
    CC_SECRET_1, CC_SECRET_2, CC_SECRET_3, CC_SECRET_4, KC_NO,     CC_PDT,         CC_NDT,    KC_NO,    KC_F6,    KC_F7,    KC_F8, KC_NO, 
                              CC_FNUM,     CC_FNUM,     CC_FNAV,   KC_SPACE,       KC_BSPACE, CC_FSYM,  CC_FCAPS, CC_FCAPS                
    )
};

// clang-format on

/*
qmk-keyboard-format:json:begin
{
  "name": "Kyria",
  "numkeys": 40,
  "rows": [
      [ -3,  0,  1,  2,  3,  4, -1, -1, -2, -1, -1,  5, 6,  7,  8,  9 ],
      [ -3, 10, 11, 12, 13, 14, -1, -1, -2, -1, -1, 15, 16, 17, 18, 19 ],
      [ -3, 20, 21, 22, 23, 24, 25, -1, -2, -1, 26, 27, 28, 29, 30, 31 ],
      [ -3, -1, -1, 32, 33, 34, 35, -1, -2, -1, 36, 37, 38, 39, -1, -1 ]
  ],
  "spacing": [
      0,
      0,
      0,
      2
  ],
  "svgmapping": [
      [ -1,  0,  1,  2,  3,  4, -1, -1, -1,  5,  6,  7,  8,  9, -1],
      [ -1, 10, 11, 12, 13, 14, -1, -1, -1, 15, 16, 17, 18, 19, -1],
      [ -1, 20, 21, 22, 23, 24, 25, -1, 26, 27, 28, 29, 30, 31, -1],
      [ -1, -1, -1, 32, 33, 34, 35, -1, 36, 37, 38, 39, -1, -1, -1]
  ],
  "svglayers": [
      "LAYER_QWERTY",
      "LAYER_RSTHD",
      "LAYER_NUMBERS",
      "LAYER_SYMBOLS",
      "LAYER_NAVIGATION",
      "LAYER_RAISE"
  ],
  "svgcolors":  {
      "CC_FNAV": "green",
      "CC_FSYM": "red"
  },
  "vizcellwidth": 5,
  "vizemits": [
  ],
  "vizline": "//#",
  "vizemits": [
      { "line": "LAYOUT => _QWERTY", "layer": "_QWERTY" },
      { "line": "LAYOUT => _QWERTY_CAPS", "layer": "_QWERTY_CAPS" },
      { "line": "LAYOUT => _NUM", "layer": "_NUM" },
      { "line": "LAYOUT => _SYM", "layer": "_SYM" },
      { "line": "LAYOUT => _NAV", "layer": "_NAV" },
      { "line": "LAYOUT => _RAISE", "layer": "_RAISE" }
  ],
  "vizboard": [
      "    //#   _001_  _002_   _003_   _004_   _005_                                   _006_   _007_   _008_   _009_   _010_ ",
      "    //#   _013_  _014_   _015_   _016_   _017_                                   _018_   _019_   _020_   _021_   _022_ ",
      "    //#   _025_  _026_   _027_   _028_   _029_   _030_   _031_   _032_   _033_   _034_   _035_   _036_   _037_   _038_ ",
      "    //#                   _040_  _041_   _042_   _043_   _044_   _045_   _046_   _047_   _048_   _049_ "
  ],
  "vizsymbols": {
      "LAYER_QWERTY": "QWERTY Layer",
      "LAYER_RSTHD": "RSTHD Layer",
      "LAYER_NUMBERS": "Numbers Layer",
      "LAYER_MOUS": "Mouse Layer",
      "LAYER_SYMBOLS": "Symbols Layer",
      "LAYER_NAVIGATION": "Navigation Layer",
      "LAYER_RAISE": "Raise Layer",
      "LAYER_VIM": "VIM Layer",
      "xxxx": "     ",
      "SH_TG": "  EE ",
      "CC_FCAPS": "Smart Caps",
      "CC_FNUM": "Smart Num",
      "CC_FSYM": " Sym ",
      "CC_FNAV": " Nav ",
      "CC_PASSWORD": "  Ψ  ",
      "LT_MOS": "MOUSE",
      "_______": "     ",
      "KC_NO": "     ",
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
      "KC_F0": "  F0 " ,
      "KC_F1": "  F1 " ,
      "KC_F2": "  F2 " ,
      "KC_F3": "  F3 " ,
      "KC_F4": "  F4 " ,
      "KC_F5": "  F5 " ,
      "KC_F6": "  F6 " ,
      "KC_F7": "  F7 " ,
      "KC_F8": "  F8 " ,
      "KC_F9": "  F9 " ,
      "KC_F10": " F10 " ,
      "KC_F11": " F11 " ,
      "KC_F12": " F12 " ,
      "KC_A": "  a  " ,
      "KC_B": "  b  " ,
      "KC_C": "  c  " ,
      "KC_D": "  d  " ,
      "KC_E": "  e  " ,
      "KC_F": "  f  " ,
      "KC_G": "  g  " ,
      "KC_H": "  h  " ,
      "KC_I": "  i  " ,
      "KC_J": "  j  " ,
      "KC_K": "  k  " ,
      "KC_L": "  l  " ,
      "KC_M": "  m  " ,
      "KC_N": "  n  " ,
      "KC_O": "  o  " ,
      "KC_P": "  p  " ,
      "KC_Q": "  q  " ,
      "KC_R": "  r  " ,
      "KC_S": "  s  " ,
      "KC_T": "  t  " ,
      "KC_U": "  u  " ,
      "KC_V": "  v  " ,
      "KC_W": "  w  " ,
      "KC_X": "  x  " ,
      "KC_Y": "  y  " ,
      "KC_Z": "  z  " ,
      "S(KC_A)": "  A  " ,
      "S(KC_B)": "  B  " ,
      "S(KC_C)": "  C  " ,
      "S(KC_D)": "  D  " ,
      "S(KC_E)": "  E  " ,
      "S(KC_F)": "  F  " ,
      "S(KC_G)": "  G  " ,
      "S(KC_H)": "  H  " ,
      "S(KC_I)": "  I  " ,
      "S(KC_J)": "  J  " ,
      "S(KC_K)": "  K  " ,
      "S(KC_L)": "  L  " ,
      "S(KC_M)": "  M  " ,
      "S(KC_N)": "  N  " ,
      "S(KC_O)": "  O  " ,
      "S(KC_P)": "  P  " ,
      "S(KC_Q)": "  Q  " ,
      "S(KC_R)": "  R  " ,
      "S(KC_S)": "  S  " ,
      "S(KC_T)": "  T  " ,
      "S(KC_U)": "  U  " ,
      "S(KC_V)": "  V  " ,
      "S(KC_W)": "  W  " ,
      "S(KC_X)": "  X  " ,
      "S(KC_Y)": "  Y  " ,
      "S(KC_Z)": "  Z  " ,
      "KC_COMMA": " , < " ,
      "KC_COMM": " , < " ,
      "KC_DOT": " . > " ,
      "KC_COLN": "  :  ",
      "KC_DCOLN": " ::  ",
      "KC_SCOLON": " ; : ",
      "KC_SCLN": " ; : ",
      "KC_SLASH": "  \/  ",
      "KC_SLSH": "  \/  ",
      "KC_BSLASH": "  \\  ",
      "KC_BSLS": "  \\  ",
      "KC_EXLM": "  !  ",
      "KC_QUES": "  ?  ",
      "KC_PIPE": "  |  ",
      "KC_QUOT": "  '  ",
      "KC_QUOTE": "  '  ",
      "KC_DQUO": "  \"  ",
      "KC_DQT": "  \"  ",
      "KC_HASH": "  #  ",
      "KC_AMPR": "  &  ",
      "KC_PERC": "  %  ",
      "KC_TILDE": "  ~  ",
      "KC_AT": "  @  ",
      "KC_DLR": "  $  ",
      "KC_CIRC": "  ^  ",
      "KC_EQL": "  =  ",
      "KC_EQUAL": "  =  ",
      "KC_ASTR": "  *  ",
      "KC_MINS": "  -  ",
      "KC_MINUS": "  -  ",
      "KC_UNDS": "  _  ",
      "KC_PLUS": "  +  ",
      "KC_LCBR": "  {  ",
      "KC_LBRACKET": "  {  ",
      "KC_RCBR": "  }  ",
      "KC_RBRACKET": "  }  ",
      "KC_LPRN": "  (  ",
      "KC_COMMA_QUES": " , ? ",
      "KC_DOT_EXCL": " . ! ",
      "KC_RPRN": "  )  ",
      "KC_GRV": "  `  ",
      "KC_LBRC": "  [  ",
      "KC_RBRC": "  ]  ",
      "KC_LABK": "  <  ",
      "KC_RABK": "  >  ",
      "KC_TILD": "  ~  ",
      "KC_ESC": " Esc " ,
      "KC_ESCAPE": " Esc " ,
      "KC_NDT": " NDT " ,
      "KC_PDT": " PDT " ,
      "KC_REDO": " Redo" ,
      "KC_UNDO": " Undo" ,
      "KC_CUT": " Cut " ,
      "KC_COPY": " Copy" ,
      "KC_PASTE": "Paste" ,
      "KC_CLOSE": "Close" ,
      "KC_COPY": " Copy",
      "KC_PASTE": "Paste",
      "KC_CUT":    " Cut " ,
      "KC_UNDO":   " Undo" ,
      "KC_REDO": " Redo " ,
      "KC_VOLU": "  🕪  " ,
      "KC_VOLD": "  🕩  " ,
      "KC_MUTE":   "  🕨  " ,
      "KC_TAB": " Tab " ,
      "KC_MENU": "  𝌆  " ,
      "KC_CAPSLOCK": "  ⇪  " ,
      "KC_NUMLK": "  ⇭  " ,
      "KC_SCRLK": "  ⇳  " ,
      "KC_PRSCR": "  ⎙  " ,
      "KC_PAUSE": "  ⎉  " ,
      "KC_BREAK": "  ⎊  " ,
      "KC_ENTER": "  ⏎  " ,
      "KC_SPACE":  "  ␣  " ,
      "KC_BSPACE": "  ⌫  " ,
      "KC_DELETE": "  ⌦  " ,
      "KC_INSERT": " Ins " ,
      "KC_LEFT":  "  ←  " ,
      "KC_RIGHT": "  →  " ,
      "KC_UP":    "  ↑  " ,
      "KC_DOWN":  "  ↓  " ,
      "KC_HOME": "  ⇤  " ,
      "KC_END": "  ⇥  " ,
      "KC_PGUP": "  ⇞  " ,
      "KC_PGDOWN": "  ⇟  " ,
      "KC_LSFT": "  ⇧  " ,
      "KC_RSFT": "  ⇧  " ,
      "CC_SHFT": "  ⇧  " ,
      "KC_LCTL": "  ^  " ,
      "KC_RCTL": "  ^  " ,
      "CC_CTRL": "  ^  " ,
      "KC_LALT": "  ⎇  " ,
      "KC_RALT": "  ⎇  " ,
      "CC_ALT": "  ⎇  " ,
      "KC_HYPER": "  ✧  " ,
      "KC_LGUI": "  ⌘  " ,
      "KC_RGUI": "  ⌘  ",
      "CC_CMD": "  ⌘  "
  }
}
qmk-keyboard-format:json:end
*/
