#include QMK_KEYBOARD_H
#include "user_layers.h"
#include "user_keycodes.h"

// clang-format off
// 50*2=100 bytes
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


// 8*40=320 bytes
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
                       CC_FNUM, CC_FNUM,  CC_FNAV, TC_SPACE,       TC_BSPACE, CC_FSYM, CC_FCAPS, CC_FCAPS                 
    ),
    [LAYER_SYMBOLS] = LAYOUT(
    TC_PERC, TC_AMPR,  TC_PIPE, TC_UNDS,   TC_TILD,                            TC_GRV,  TC_QUOT,  TC_DQUO,  TC_HASH, TC_DLR,  
    TC_EXLM, TC_MINUS, TC_PLUS, TC_EQUAL,  TC_LBRC,                            TC_LABK, TC_LPRN,  TC_LCBR,  TC_RABK, TC_COLN, 
    TC_CIRC, TC_SLASH, TC_ASTR, TC_BSLASH, TC_RBRC, CC_NDOC,        CC_PDOC,   TC_RABK, TC_RPRN,  TC_RCBR,  TC_QUES, TC_AT,   
                       CC_FCNT, CC_FCNT,   CC_FNAV, TC_SPACE,       TC_BSPACE, CC_FSYM, CC_FCNT,  CC_FCNT
    ),
    [LAYER_NAVIGATION] = LAYOUT(
    CC_REDO, CC_CLOSE, TC_ESCAPE, TC_ENTER, TC_TAB,                               TC_INSERT, TC_PGUP,   TC_HOME,  TC_NO,    TC_NO, 
    CC_CMD,  CC_ALT,   CC_CTRL,   CC_SHFT,  TC_DELETE,                            TC_LEFT,   TC_DOWN,   TC_UP,    TC_RIGHT, TC_NO, 
    CC_UNDO, CC_CUT,   CC_COPY,   CC_PASTE, CC_VIM,    CC_NAPP,        CC_PAPP,   CC_VIM,    TC_PGDOWN, TC_END,   TC_NO,    TC_NO, 
                       CC_FNUM,   CC_FNUM,  CC_FNAV,   TC_SPACE,       TC_BSPACE, CC_FSYM,   CC_FCAPS,  CC_FCAPS                   
    ),
    [LAYER_RAISE] = LAYOUT(
    CC_SECRET_5, CC_SECRET_6, CC_SECRET_7, CC_SECRET_8, TC_NO,                                TC_F12,   TC_F2,    TC_F3,    TC_F4, TC_F1, 
    CC_CMD,      CC_ALT,      CC_CTRL,     CC_SHFT,     TC_NO,                                TC_F5,    TC_F11,   TC_F10,   TC_F9, TC_NO, 
    CC_SECRET_1, CC_SECRET_2, CC_SECRET_3, CC_SECRET_4, CC_QWERTY, CC_PDT,         CC_NDT,    CC_RSTHD, TC_F6,    TC_F7,    TC_F8, TC_NO, 
                              CC_FNUM,     CC_FNUM,     CC_FNAV,   TC_SPACE,       TC_BSPACE, CC_FSYM,  CC_FCAPS, CC_FCAPS                
    ),
    [LAYER_VIM] = LAYOUT(
    CC_VIM_CHAR, CC_VIM_WORD,  CC_VIM_END,    CC_VIM_REDO,   CC_VIM_INSIDE,                       CC_VIM_YANK,  CC_VIM_UNDO, CC_VIM_INSERT, CC_VIM_LINE,   CC_VIM_PAGE, 
    CC_VIM_ADD,  CC_VIM_BEGIN, CC_VIM_DELETE, CC_VIM_FIND,   CC_VIM_GOTO,                         CC_VIM_LEFT,  CC_VIM_DOWN, CC_VIM_UP,     CC_VIM_RIGHT,  TC_NO,       
    CC_VIM_ZOOM, CC_VIM_CUT,   CC_VIM_CHANGE, CC_VIM_VISUAL, TC_NO,         CC_VIM,       CC_VIM, TC_NO,        CC_VIM_DELI, CC_VIM_CLEAR,  CC_VIM_REPEAT, TC_NO,       
                               CC_FNUM,       CC_FNUM,       CC_VIM_RAISE,  CC_VIM,       CC_VIM, CC_VIM_RAISE, CC_FCAPS,    CC_FCAPS                                   
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
