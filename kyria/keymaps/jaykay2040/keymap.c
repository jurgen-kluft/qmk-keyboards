#include QMK_KEYBOARD_H
#include "user_layers.h"
#include "user_keycodes.h"

// clang-format off
#define LAYOUTX( \
    L01, L02, L03, L04, L05,                     R06, R07, R08, R09, R10, \
    L13, L14, L15, L16, L17,                     R18, R19, R20, R21, R22, \
    L25, L26, L27, L28, L29, L30,           R33, R34, R35, R36, R37, R38, \
              L40, L41, L42, L43,           R46, R47, R48, R49 \
) \
{ \
    { KC_NO, KC_NO, L05,   L04,   L03,   L02,   L01,   KC_NO }, \
    { KC_NO, KC_NO, L17,   L16,   L15,   L14,   L13,   KC_NO }, \
    { KC_NO, L30,   L29,   L28,   L27,   L26,   L25,   KC_NO }, \
    { KC_NO, L43,   L42,   L41,   KC_NO, L40,   KC_NO, KC_NO }, \
    { KC_NO, KC_NO, R06,   R07,   R08,   R09,   R10,   KC_NO }, \
    { KC_NO, KC_NO, R18,   R19,   R20,   R21,   R22,   KC_NO }, \
    { KC_NO, R33,   R34,   R35,   R36,   R37,   R38,   KC_NO }, \
    { KC_NO, R46,   R47,   R48,   KC_NO, R49,   KC_NO, KC_NO }, \
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
      "LAYER_RAISE",
      "LAYER_VIM"
  ],
  "svgcolors":  {
      "CC_FNAV": "green"
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
      "TC_NO": "     ",
      "TC_0": "  0  " ,
      "TC_1": "  1  " ,
      "TC_2": "  2  " ,
      "TC_3": "  3  " ,
      "TC_4": "  4  " ,
      "TC_5": "  5  " ,
      "TC_6": "  6  " ,
      "TC_7": "  7  " ,
      "TC_8": "  8  " ,
      "TC_9": "  9  " ,
      "TC_F0": "  F0 " ,
      "TC_F1": "  F1 " ,
      "TC_F2": "  F2 " ,
      "TC_F3": "  F3 " ,
      "TC_F4": "  F4 " ,
      "TC_F5": "  F5 " ,
      "TC_F6": "  F6 " ,
      "TC_F7": "  F7 " ,
      "TC_F8": "  F8 " ,
      "TC_F9": "  F9 " ,
      "TC_F10": " F10 " ,
      "TC_F11": " F11 " ,
      "TC_F12": " F12 " ,
      "TC_A": "  a  " ,
      "TC_B": "  b  " ,
      "TC_C": "  c  " ,
      "TC_D": "  d  " ,
      "TC_E": "  e  " ,
      "TC_F": "  f  " ,
      "TC_G": "  g  " ,
      "TC_H": "  h  " ,
      "TC_I": "  i  " ,
      "TC_J": "  j  " ,
      "TC_K": "  k  " ,
      "TC_L": "  l  " ,
      "TC_M": "  m  " ,
      "TC_N": "  n  " ,
      "TC_O": "  o  " ,
      "TC_P": "  p  " ,
      "TC_Q": "  q  " ,
      "TC_R": "  r  " ,
      "TC_S": "  s  " ,
      "TC_T": "  t  " ,
      "TC_U": "  u  " ,
      "TC_V": "  v  " ,
      "TC_W": "  w  " ,
      "TC_X": "  x  " ,
      "TC_Y": "  y  " ,
      "TC_Z": "  z  " ,
      "S(TC_A)": "  A  " ,
      "S(TC_B)": "  B  " ,
      "S(TC_C)": "  C  " ,
      "S(TC_D)": "  D  " ,
      "S(TC_E)": "  E  " ,
      "S(TC_F)": "  F  " ,
      "S(TC_G)": "  G  " ,
      "S(TC_H)": "  H  " ,
      "S(TC_I)": "  I  " ,
      "S(TC_J)": "  J  " ,
      "S(TC_K)": "  K  " ,
      "S(TC_L)": "  L  " ,
      "S(TC_M)": "  M  " ,
      "S(TC_N)": "  N  " ,
      "S(TC_O)": "  O  " ,
      "S(TC_P)": "  P  " ,
      "S(TC_Q)": "  Q  " ,
      "S(TC_R)": "  R  " ,
      "S(TC_S)": "  S  " ,
      "S(TC_T)": "  T  " ,
      "S(TC_U)": "  U  " ,
      "S(TC_V)": "  V  " ,
      "S(TC_W)": "  W  " ,
      "S(TC_X)": "  X  " ,
      "S(TC_Y)": "  Y  " ,
      "S(TC_Z)": "  Z  " ,
      "TC_COMMA": " , < " ,
      "TC_COMM": " , < " ,
      "TC_DOT": " . > " ,
      "TC_COLN": "  :  ",
      "TC_DCOLN": " ::  ",
      "TC_SCOLON": " ; : ",
      "TC_SCLN": " ; : ",
      "TC_SLASH": "  \/  ",
      "TC_SLSH": "  \/  ",
      "TC_BSLASH": "  \\  ",
      "TC_BSLS": "  \\  ",
      "TC_EXLM": "  !  ",
      "TC_QUES": "  ?  ",
      "TC_PIPE": "  |  ",
      "TC_QUOT": "  '  ",
      "TC_QUOTE": "  '  ",
      "TC_DQUO": "  \"  ",
      "TC_DQT": "  \"  ",
      "TC_HASH": "  #  ",
      "TC_AMPR": "  &  ",
      "TC_PERC": "  %  ",
      "TC_TILDE": "  ~  ",
      "TC_AT": "  @  ",
      "TC_DLR": "  $  ",
      "TC_CIRC": "  ^  ",
      "TC_EQL": "  =  ",
      "TC_EQUAL": "  =  ",
      "TC_ASTR": "  *  ",
      "TC_MINS": "  -  ",
      "TC_MINUS": "  -  ",
      "TC_UNDS": "  _  ",
      "TC_PLUS": "  +  ",
      "TC_LCBR": "  {  ",
      "TC_LBRACKET": "  {  ",
      "TC_RCBR": "  }  ",
      "TC_RBRACKET": "  }  ",
      "TC_LPRN": "  (  ",
      "TC_COMMA_QUES": " , ? ",
      "TC_DOT_EXCL": " . ! ",
      "TC_RPRN": "  )  ",
      "TC_GRV": "  `  ",
      "TC_LBRC": "  [  ",
      "TC_RBRC": "  ]  ",
      "TC_LABK": "  <  ",
      "TC_RABK": "  >  ",
      "TC_TILD": "  ~  ",
      "TC_ESC": " Esc " ,
      "TC_ESCAPE": " Esc " ,
      "TC_NDT": " NDT " ,
      "TC_PDT": " PDT " ,
      "TC_REDO": " Redo" ,
      "TC_UNDO": " Undo" ,
      "TC_CUT": " Cut " ,
      "TC_COPY": " Copy" ,
      "TC_PASTE": "Paste" ,
      "TC_CLOSE": "Close" ,
      "TC_COPY": " Copy",
      "TC_PASTE": "Paste",
      "TC_CUT":    " Cut " ,
      "TC_UNDO":   " Undo" ,
      "TC_REDO": " Redo " ,
      "TC_VOLU": "  🕪  " ,
      "TC_VOLD": "  🕩  " ,
      "TC_MUTE":   "  🕨  " ,
      "TC_TAB": " Tab " ,
      "TC_MENU": "  𝌆  " ,
      "TC_CAPSLOCK": "  ⇪  " ,
      "TC_NUMLK": "  ⇭  " ,
      "TC_SCRLK": "  ⇳  " ,
      "TC_PRSCR": "  ⎙  " ,
      "TC_PAUSE": "  ⎉  " ,
      "TC_BREAK": "  ⎊  " ,
      "TC_ENTER": "  ⏎  " ,
      "TC_SPACE":  "  ␣  " ,
      "TC_BSPACE": "  ⌫  " ,
      "TC_DELETE": "  ⌦  " ,
      "TC_INSERT": " Ins " ,
      "TC_LEFT":  "  ←  " ,
      "TC_RIGHT": "  →  " ,
      "TC_UP":    "  ↑  " ,
      "TC_DOWN":  "  ↓  " ,
      "TC_HOME": "  ⇤  " ,
      "TC_END": "  ⇥  " ,
      "TC_PGUP": "  ⇞  " ,
      "TC_PGDOWN": "  ⇟  " ,
      "TC_LSFT": "  ⇧  " ,
      "TC_RSFT": "  ⇧  " ,
      "CC_SHFT": "  ⇧  " ,
      "TC_LCTL": "  ^  " ,
      "TC_RCTL": "  ^  " ,
      "CC_CTRL": "  ^  " ,
      "TC_LALT": "  ⎇  " ,
      "TC_RALT": "  ⎇  " ,
      "CC_ALT": "  ⎇  " ,
      "TC_HYPER": "  ✧  " ,
      "TC_LGUI": "  ⌘  " ,
      "TC_RGUI": "  ⌘  ",
      "CC_CMD": "  ⌘  "
  }
}
qmk-keyboard-format:json:end
*/
