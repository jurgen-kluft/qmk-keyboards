#include QMK_KEYBOARD_H
#include "layouts.h"
#include "user_layers.h"
#include "user_keycodes.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    xxxx, KL_00,  KL_01, KL_02, KL_03, KL_04,                                 KL_05,  KL_06, KL_07, KL_08, KL_09, xxxx,
    xxxx, KL_10,  KL_11, KL_12, KL_13, KL_14,                                 KL_15,  KL_16, KL_17, KL_18, KL_19, xxxx,
    xxxx, KL_20,  KL_21, KL_22, KL_23, KL_24, KL_25, xxxx,       xxxx, KL_26, KL_27,  KL_28, KL_29, KL_30, KL_31, xxxx,
                         KL_32, KL_33, KL_34, KL_35, xxxx,       xxxx, KL_36, KL_37,  KL_38, KL_39
  )
};



#undef LAYOUT
#define LAYOUT( \
    L00, L01, L02, L03, L04,                        L05, L06, L07, L08, L09, \
    L10, L11, L12, L13, L14,                        L15, L16, L17, L18, L19, \
    L20, L21, L22, L23, L24, L25,              L26, L27, L28, L29, L30, L31, \
              L32, L33, L34, L35,              L36, L37, L38, L39 \
) \
{ \
    L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, \
    L10, L11, L12, L13, L14, L15, L16, L17, L18, L19, \
    L20, L21, L22, L23, L24, L25, L26, L27, L28, L29, \
    L30, L31, L32, L33, L34, L35, L36, L37, L38, L39  \
}

const uint8_t PROGMEM user_kb_layers[][40] = {
    [LAYER_QWERTY] = LAYOUT(
    TC_Q, TC_W, TC_E,    TC_R,    TC_T,                               TC_Y,    TC_U,     TC_I,     TC_O,   TC_P,    
    TC_A, TC_S, TC_D,    TC_F,    TC_G,                               TC_H,    TC_J,     TC_K,     TC_L,   TC_SCLN, 
    TC_Z, TC_X, TC_C,    TC_V,    TC_B,    CC_PDT,         CC_NDT,    TC_N,    TC_M,     TC_COMMA, TC_DOT, TC_AT,   
                CC_FNUM, CC_FNUM, CC_FNAV, TC_SPACE,       TC_BSPACE, CC_FSYM, CC_FCAPS, CC_FCAPS                   
    ),
    [LAYER_RSTHD] = LAYOUT(
    TC_J,    TC_C, TC_Y,    TC_F,    TC_K,                            TC_Z,    TC_L,     TC_BSPACE, TC_U,   TC_Q,  
    TC_R,    TC_S, TC_T,    TC_H,    TC_D,                            TC_M,    TC_N,     TC_A,      TC_I,   TC_O,  
    TC_SCLN, TC_V, TC_G,    TC_P,    TC_B,    CC_PDT,         CC_NDT, TC_X,    TC_W,     TC_COMMA,  TC_DOT, TC_AT, 
                   CC_FNUM, CC_FNUM, CC_FNAV, TC_SPACE,       TC_E,   CC_FSYM, CC_FCAPS, CC_FCAPS                  
    ),
    [LAYER_NUMBERS] = LAYOUT(
    TC_PLUS, TC_MINUS, TC_ASTR, TC_SLASH, TC_NO,                              TC_6,    TC_0,     TC_9,     TC_8,   TC_7,  
    TC_7,    TC_8,     TC_9,    TC_0,     TC_6,                               TC_5,    TC_1,     TC_2,     TC_3,   TC_4,  
    CC_CMD,  CC_ALT,   CC_CTRL, CC_SHFT,  TC_NO,   TC_NO,          TC_NO,     TC_NO,   TC_EQUAL, TC_COMMA, TC_DOT, TC_NO, 
                       CC_FCNT, CC_FCNT,  CC_FNAV, TC_SPACE,       TC_BSPACE, CC_FSYM, CC_FCNT,  CC_FCNT
    ),
    [LAYER_SYMBOLS] = LAYOUT(
    TC_PERC, TC_AMPR,  TC_PIPE, TC_UNDS,   TC_TILD,                            TC_GRV,  TC_QUOT,  TC_DQUO,  TC_HASH, TC_DLR,  
    TC_EXLM, TC_MINUS, TC_PLUS, TC_EQUAL,  TC_LBRC,                            TC_LABK, TC_LPRN,  TC_LCBR,  TC_RABK, TC_COLN, 
    TC_CIRC, TC_SLASH, TC_ASTR, TC_BSLASH, TC_RBRC, CC_NDOC,        CC_PDOC,   TC_RABK, TC_RPRN,  TC_RCBR,  TC_QUES, TC_AT,   
                       CC_FCNT, CC_FCNT,   CC_FNAV, TC_SPACE,       TC_BSPACE, CC_FSYM, CC_FCAPS, CC_FCAPS                    
    ),
    [LAYER_NAVIGATION] = LAYOUT(
    CC_REDO, CC_CLOSE, TC_ESCAPE, TC_ENTER, TC_TAB,                               TC_INSERT, TC_PGUP,   TC_HOME,  TC_NO,    TC_NO, 
    CC_CMD,  CC_ALT,   CC_CTRL,   CC_SHFT,  TC_DELETE,                            TC_LEFT,   TC_DOWN,   TC_UP,    TC_RIGHT, TC_NO, 
    CC_UNDO, CC_CUT,   CC_COPY,   CC_PASTE, TC_NO,     CC_NAPP,        CC_PAPP,   TC_NO,     TC_PGDOWN, TC_END,   TC_NO,    TC_NO, 
                       CC_FNUM,   CC_FNUM,  CC_FNAV,   TC_SPACE,       TC_BSPACE, CC_FSYM,   CC_FCAPS,  CC_FCAPS                   
    ),
    [LAYER_RAISE] = LAYOUT(
    CC_SECRET_5, CC_SECRET_6, CC_SECRET_7, CC_SECRET_8, TC_NO,                                TC_F12,   TC_F2,    TC_F3,    TC_F4, TC_F1, 
    CC_CMD,      CC_ALT,      CC_CTRL,     CC_SHFT,     TC_NO,                                TC_F5,    TC_F11,   TC_F10,   TC_F9, TC_NO, 
    CC_SECRET_1, CC_SECRET_2, CC_SECRET_3, CC_SECRET_4, TC_NO,     CC_PDT,         CC_NDT,    TC_NO,    TC_F6,    TC_F7,    TC_F8, TC_NO, 
                              CC_FNUM,     CC_FNUM,     CC_FNAV,   TC_SPACE,       TC_BSPACE, CC_FSYM,  CC_FCAPS, CC_FCAPS                
    )
};
// clang-format on

/*
qmk-keyboard-format:json:begin
{
  "name": "Kyria",
  "numkeys": 50,
  "rows": [
      [ -3,  0,  1,  2,  3,  4,  5, -1, -1, -2, -1, -1,  6,  7,  8,  9, 10, 11 ],
      [ -3, 12, 13, 14, 15, 16, 17, -1, -1, -2, -1, -1, 18, 19, 20, 21, 22, 23 ],
      [ -3, 24, 25, 26, 27, 28, 29, 30, 31, -2, 32, 33, 34, 35, 36, 37, 38, 39 ],
      [ -3, -1, -1, -1, 40, 41, 42, 43, 44, -2, 45, 46, 47, 48, 49, -1, -1, -1 ]
  ],
  "spacing": [
      0,
      0,
      0,
      2
  ],
  "svgmapping": [
    [ -1,  1,  2,  3,  4,  5, -1, -1, -1,  6,  7,  8,  9, 10, -1 ],
    [ -1, 13, 14, 15, 16, 17, -1, -1, -1, 18, 19, 20, 21, 22, -1 ],
    [ -1, 25, 26, 27, 28, 29, 30, -1, 33, 34, 35, 36, 37, 38, -1 ],
    [ -1, -1, -1, 40, 41, 42, 43, -1, 46, 47, 48, 49, -1, -1, -1 ]
  ],
  "svglayers": [
      "_QWERTY",
      "_RSTHD",
      "_QWERTY_CAPS",
      "_RSTHD_CAPS",
      "_NUM",
      "_SYM",
      "_NAV",
      "_RAISE"
  ],
  "svgcolors":  {
      "KC_FNAV": "green"
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
      "_QWERTY": "QWERTY Layer",
      "_RSTHD": "RSTHD Layer",
      "_QWERTY_CAPS": "QWERTY Layer (Caps)",
      "_RSTHD_CAPS": "RSTHD Layer (Caps)",
      "_NUM": "Numbers Layer",
      "_MOUS": "Mouse Layer",
      "_SYM": "Symbols Layer",
      "_NAV": "Navigation Layer",
      "_RAISE": "Raise Layer",
      "xxxx": "     ",
      "SH_TG": "  EE ",
      "KC_FCAPS": "Smart Caps",
      "KC_FNUM": "Smart Num",
      "KC_FSYM": " Sym ",
      "KC_FNAV": " Nav ",
      "KC_PASSWORD": "  Ψ  ",
      "LT_MOS": "MOUSE",
      "LA_NAV": " NAV ",
      "LA_RAISE": "RAISE",
      "LA_SYM": " SYM ",
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
      "KC_OS_NDT": " NDT " ,
      "KC_OS_PDT": " PDT " ,
      "KC_OS_REDO": " Redo" ,
      "KC_OS_UNDO": " Undo" ,
      "KC_OS_CUT": " Cut " ,
      "KC_OS_COPY": " Copy" ,
      "KC_OS_PASTE": "Paste" ,
      "KC_OS_CLOSE": "Close" ,
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
      "OS_SHFT": "  ⇧  " ,
      "KC_LCTL": "  ^  " ,
      "KC_RCTL": "  ^  " ,
      "OS_CTRL": "  ^  " ,
      "KC_LALT": "  ⎇  " ,
      "KC_RALT": "  ⎇  " ,
      "OS_ALT": "  ⎇  " ,
      "KC_HYPER": "  ✧  " ,
      "KC_LGUI": "  ⌘  " ,
      "KC_RGUI": "  ⌘  ",
      "OS_CMD": "  ⌘  "
  }
}
qmk-keyboard-format:json:end
*/
