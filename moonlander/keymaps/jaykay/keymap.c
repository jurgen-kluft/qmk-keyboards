#include QMK_KEYBOARD_H
#include "cukey.h"
#include "user_keycodes.h"
#include "user_layers.h"

#undef LAYOUT
#define LAYOUT LAYOUT_moonlander

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
      KL_00, KL_01, KL_02, KL_03, KL_04, KL_05, KL_06,   KL_07, KL_08, KL_09, KL_10, KL_11, KL_12, KL_13, 
      KL_14, KL_15, KL_16, KL_17, KL_18, KL_19, KL_20,   KL_21, KL_22, KL_23, KL_24, KL_25, KL_26, KL_27, 
      KL_28, KL_29, KL_30, KL_31, KL_32, KL_33, KL_34,   KL_35, KL_36, KL_37, KL_38, KL_39, KL_40, KL_41, 
      KL_42, KL_43, KL_44, KL_45, KL_46, KL_47,                 KL_48, KL_49, KL_50, KL_51, KL_52, KL_53, 
      KL_54, KL_55, KL_56, KL_57, KL_58, KL_59,                 KL_60, KL_61, KL_62, KL_63, KL_64, KL_65, 
                                  KL_66, KL_67, KL_68,   KL_69, KL_70, KL_71                              
  )
};

const uint8_t user_kb_layers[][72] = {
  [LAYER_QWERTY] = {
       CC_NO, CC_NO, CC_NO, CC_NO,   CC_NO,    CC_NO, CC_NO,       CC_NO,     CC_NO, CC_NO,     CC_NO,    CC_NO,  CC_NO,     CC_GAMEL, 
       CC_NO, TC_Q,  TC_W,  TC_E,    TC_R,     TC_T,  CC_NDT,      CC_PDT,    TC_Y,  TC_U,      TC_I,     TC_O,   TC_P,      CC_NO,    
       CC_NO, TC_A,  TC_S,  TC_D,    TC_F,     TC_G,  CC_PDT,      CC_NDT,    TC_H,  TC_J,      TC_K,     TC_L,   TC_SCLN,   CC_NO,    
       CC_NO, TC_Z,  TC_X,  TC_C,    TC_V,     TC_B,                          TC_N,  TC_M,      TC_COMMA, TC_DOT, TC_SLASH,  CC_NO,    
       CC_NO, CC_NO, CC_NO, CC_FNUM, CC_FNAV,  CC_PDT,                        CC_NDT,CC_FSYM,   CC_FCAPS, CC_NO,  CC_NO,     CC_RSTHD, 
                                     TC_SPACE, CC_NO, CC_NO,       CC_NO,     CC_NO, TC_BSPACE                                         
  },
  [LAYER_RSTHD] = {
       CC_NO, CC_NO,   CC_NO, CC_NO,   CC_NO,    CC_NO,     CC_NO,       CC_NO,     CC_NO,     CC_NO,   CC_NO,     CC_NO,  CC_NO,   CC_GAMEL,  
       CC_NO, TC_J,    TC_C,  TC_Y,    TC_F,     TC_K,      CC_NDT,      CC_PDT,    TC_Z,      TC_L,    TC_BSPACE, TC_U,   TC_Q,    CC_NO,     
       CC_NO, TC_R,    TC_S,  TC_T,    TC_H,     TC_D,      CC_PDT,      CC_NDT,    TC_M,      TC_N,    TC_A,      TC_I,   TC_O,    CC_NO,     
       CC_NO, TC_UNDS, TC_V,  TC_G,    TC_P,     TC_B,                              TC_X,      TC_W,    TC_COMMA,  TC_DOT, TC_SCLN, CC_NO,     
       CC_NO, CC_NO,   CC_NO, CC_FNUM, CC_FNAV,  CC_PDT,                            CC_NDT,    CC_FSYM, CC_FCAPS,  CC_NO,  CC_NO,   CC_QWERTY, 
                                       TC_SPACE, TC_BSPACE, CC_NO,       CC_NO,     CC_NO,     TC_E                                            
  },
  [LAYER_NUMBERS] = {
       CC_NO, CC_NO, CC_NO, CC_NO,    CC_NO,    CC_NO,    CC_NO,   CC_NO, CC_NO, CC_NO, CC_NO, CC_NO, CC_NO, CC_NO, 
       CC_NO, CC_NO, CC_NO, TC_MINUS, TC_PLUS,  CC_NO,    CC_NO,   CC_NO, CC_NO, TC_5,  TC_6,  TC_7,  TC_8,  CC_NO, 
       CC_NO, CC_NO, CC_NO, TC_9,     TC_0,     TC_EQUAL, CC_NO,   CC_NO, CC_NO, TC_1,  TC_2,  TC_3,  TC_4,  CC_NO, 
       CC_NO, CC_NO, CC_NO, TC_ASTR,  TC_SLASH, CC_NO,                    CC_NO, TC_0,  CC_NO, CC_NO, CC_NO, CC_NO, 
       CC_NO, CC_NO, CC_NO, CC_FNUM,  CC_NO,    CC_NO,                    CC_NO, CC_NO, CC_NO, CC_NO, CC_NO, CC_NO, 
                                      TC_SPACE, CC_NO,    CC_NO,   CC_NO, CC_NO, TC_BSPACE                              
  },
  [LAYER_SYMBOLS] = {
       CC_NO, CC_NO,   CC_NO,    CC_NO,   CC_NO,     CC_NO,    CC_NO,              CC_NO, CC_NO,    CC_NO,   CC_NO,   CC_NO,    CC_NO,   CC_NO, 
       CC_NO, TC_PERC, TC_AMPR,  TC_PIPE, TC_UNDS,   TC_TILD,  CC_NO,              CC_NO, TC_GRV,   TC_QUOT,  TC_DQUO, TC_HASH, TC_DLR,  CC_NO, 
       CC_NO, TC_EXLM, TC_MINUS, TC_PLUS, TC_EQUAL,  TC_LBRC,  CC_NO,              CC_NO, TC_LABK,  TC_LPRN,  TC_LCBR, TC_RABK, TC_COLN, CC_NO, 
       CC_NO, TC_CIRC, TC_SLASH, TC_ASTR, TC_BSLASH, TC_RBRC,                             CC_NO,    TC_RPRN,  TC_RCBR, TC_QUES, TC_AT,   CC_NO, 
       CC_NO, CC_NO,   CC_NO,    CC_FNUM, CC_FNAV,   CC_PDT,                              CC_NDT,   CC_FSYM,  CC_FCAPS, CC_NO,  CC_NO,   CC_QWERTY, 
                                          TC_SPACE,  CC_NO,    CC_NO,              CC_NO, CC_NO,    TC_BSPACE
  },
  [LAYER_NAVIGATION] = {
       CC_NO, CC_NO,      CC_NO,       CC_NO,      CC_NO,       CC_NO,     CC_NO,   CC_NO, CC_NO,     CC_NO,     CC_NO,   CC_NO,    CC_NO, CC_NO, 
       CC_NO, CC_NO,      CC_CLOSE,    TC_ESCAPE,  TC_ENTER,    TC_TAB,    CC_NO,   CC_NO, TC_INSERT, TC_PGUP,   TC_HOME, CC_NO,    CC_NO, CC_NO, 
       CC_NO, CC_CMD,     CC_ALT,      CC_CTRL,    CC_SHFT,     TC_DELETE, CC_NO,   CC_NO, TC_LEFT,   TC_DOWN,   TC_UP,   TC_RIGHT, CC_NO, CC_NO, 
       CC_NO, CC_UNDO,    CC_CUT,      CC_COPY,    CC_PASTE,    TC_BSPACE,                 TC_DELETE, TC_PGDOWN, TC_END,  CC_NO,    CC_NO, CC_NO, 
       CC_NO, CC_NO,      CC_NO,       CC_NO,      CC_FNAV,     CC_NO,                     CC_NO,     CC_FSYM,   CC_NO,   CC_NO,    CC_NO, CC_NO, 
                                                   CC_NO,       CC_NO,     CC_NO,   CC_NO, CC_NO,     TC_BSPACE                                       
  },
  [LAYER_RAISE] = {
       CC_NO, CC_NO,  CC_NO,  CC_NO,  CC_NO, CC_NO, CC_NO,   CC_NO, CC_NO, CC_NO,   CC_NO,   CC_NO,  CC_NO,  CC_NO, 
       CC_NO, TC_F12, TC_F11, TC_F10, TC_F9, CC_NO, CC_NO,   CC_NO, CC_NO, CC_NO,   CC_NO,   CC_NO,  CC_NO,  CC_NO, 
       CC_NO, TC_F8,  TC_F7,  TC_F6,  TC_F5, CC_NO, CC_NO,   CC_NO, CC_NO, CC_SHFT, CC_CTRL, CC_ALT, CC_CMD, CC_NO, 
       CC_NO, TC_F4,  TC_F3,  TC_F2,  TC_F1, CC_NO,                 CC_NO, CC_NO,   CC_NO,   CC_NO,  CC_NO,  CC_NO, 
       CC_NO, CC_NO,  CC_NO,  CC_NO,  CC_NO, CC_NO,                 CC_NO, CC_NO,   CC_NO,   CC_NO,  CC_NO,  CC_NO, 
                                      CC_NO, CC_NO, CC_NO,   CC_NO, CC_NO, CC_NO                                    
  },
  [LAYER_VIM] = {
       CC_NO, CC_NO,         CC_NO,        CC_NO,         CC_NO,          CC_NO,         CC_NO,                  CC_NO, CC_NO,           CC_NO,       CC_NO,         CC_NO,         CC_NO,           CC_NO, 
       CC_NO, CC_VIM_CHAR,   CC_VIM_WORD,  CC_VIM_END,    CC_VIM_REDO,    CC_VIM_FIND,   CC_NO,                  CC_NO, CC_VIM_YANK,     CC_VIM_UNDO, CC_VIM_INSIDE, CC_VIM_LINE,   CC_VIM_PAGE,     CC_NO, 
       CC_NO, CC_VIM_INSERT, CC_VIM_BEGIN, CC_VIM_DELETE, CC_VIM_SEARCH,  CC_VIM_GOTO,   CC_NO,                  CC_NO, CC_VIM_LEFT,     CC_VIM_DOWN, CC_VIM_UP,     CC_VIM_RIGHT,  CC_VIM_APP,      CC_NO, 
       CC_NO, CC_VIM_DOCU,   CC_VIM_CUT,   CC_VIM_CHANGE, CC_VIM_VISUAL,  CC_VIM_INDENT,                                CC_VIM_UNINDENT, CC_VIM_DELI, CC_VIM_CLEAR,  CC_VIM_REPEAT, CC_VIM_DESKTOP,  CC_NO, 
       CC_NO, CC_NO,         CC_NO,        CC_NO,         CC_NO,          CC_NO,                                        CC_NO,           CC_NO,       CC_NO,         CC_NO,         CC_NO,           CC_NO,
                                                          CC_VIM_RAISE,   CC_NO,         CC_NO,                  CC_NO, CC_NO,           CC_VIM_RAISE,
  },
  [LAYER_VIM_RAISE] = {
       CC_NO, CC_NO,         CC_NO,        CC_NO,         CC_NO,          CC_NO,         CC_NO,                  CC_NO, CC_NO,           CC_NO,       CC_NO,         CC_NO,         CC_NO,           CC_NO, 
       CC_NO, CC_VIM_CHAR,   CC_VIM_WORD,  CC_VIM_END,    CC_VIM_REDO,    CC_VIM_FIND,   CC_NO,                  CC_NO, CC_VIM_YANK,     CC_VIM_UNDO, CC_VIM_INSIDE, CC_VIM_LINE,   CC_VIM_PAGE,     CC_NO, 
       CC_NO, CC_VIM_INSERT, CC_VIM_BEGIN, CC_VIM_DELETE, CC_VIM_SEARCH,  CC_VIM_GOTO,   CC_NO,                  CC_NO, CC_VIM_LEFT,     CC_VIM_DOWN, CC_VIM_UP,     CC_VIM_RIGHT,  CC_VIM_APP,      CC_NO, 
       CC_NO, CC_VIM_DOCU,   CC_VIM_CUT,   CC_VIM_CHANGE, CC_VIM_VISUAL,  CC_VIM_INDENT,                                CC_VIM_UNINDENT, CC_VIM_DELI, CC_VIM_CLEAR,  CC_VIM_REPEAT, CC_VIM_DESKTOP,  CC_NO, 
       CC_NO, CC_NO,         CC_NO,        CC_NO,         CC_NO,          CC_NO,                                        CC_NO,           CC_NO,       CC_NO,         CC_NO,         CC_NO,           CC_NO,
                                                          CC_VIM_RAISE,   CC_NO,         CC_NO,                  CC_NO, CC_NO,           CC_VIM_RAISE,
  },
  [LAYER_GAMEL] = {
       CC_NO,     TC_1,  TC_2,       TC_3,     TC_4,     TC_5,      CC_NO,   TC_0,  TC_6,  TC_7,    TC_8,      TC_9,   CC_NO,     CC_NO, 
       TC_TAB,    TC_Q,  TC_W,       TC_E,     TC_R,     TC_T,      CC_NO,   CC_NO, TC_Y,  TC_U,    TC_I,      TC_O,   TC_P,      CC_NO, 
       TC_ESCAPE, TC_A,  TC_S,       TC_D,     TC_F,     TC_G,      CC_NO,   CC_NO, TC_H,  TC_J,    TC_K,      TC_L,   TC_SCLN,   CC_NO, 
       TC_LSHIFT, TC_Z,  TC_X,       TC_C,     TC_V,     TC_B,                      TC_N,  TC_M,    TC_COMMA,  TC_DOT, TC_SLASH,  CC_NO, 
       CC_NO,     CC_NO, CC_GAMER,   TC_LCTRL, TC_LALT,  TC_ENTER,                  CC_NO, TC_LALT, TC_LSHIFT, CC_NO,  CC_NO,     CC_NO, 
                                               TC_SPACE, TC_BSPACE, CC_NO,   CC_NO, CC_NO, CC_NO                                         
  },
  [LAYER_GAMER] = {
       CC_NO,     TC_0,      TC_9,   TC_8,     TC_7,     TC_6,      CC_NO,   TC_0,  TC_6,  TC_7,    TC_8,     TC_9,   CC_NO,     CC_NO,     
       CC_NO,     TC_P,      TC_O,   TC_I,     TC_U,     TC_Y,      CC_NO,   CC_NO, TC_Y,  TC_U,    TC_I,     TC_O,   TC_P,      CC_NO,     
       TC_ESCAPE, TC_SCLN,   TC_L,   TC_K,     TC_J,     TC_H,      CC_NO,   CC_NO, TC_H,  TC_J,    TC_K,     TC_L,   TC_SCLN,   CC_NO,     
       TC_LSHIFT, TC_SLASH,  TC_DOT, TC_COMMA, TC_M,     TC_N,                      TC_N,  TC_M,    TC_COMMA, TC_DOT, TC_SLASH,  TC_RSHIFT, 
       CC_NO,     CC_NO,     CC_NO,  TC_LCTRL, TC_LALT,  TC_ENTER,                  CC_NO, TC_LALT, TC_LCTRL, CC_NO,  CC_NO,     CC_NO,     
                                               TC_SPACE, TC_BSPACE, CC_NO,   CC_NO, CC_NO, CC_NO                                            
  }
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
        "TC_TRANS": "     ",
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
        "TC_A": "  A  " ,
        "TC_B": "  B  " ,
        "TC_C": "  C  " ,
        "TC_D": "  D  " ,
        "TC_E": "  E  " ,
        "TC_F": "  F  " ,
        "TC_G": "  G  " ,
        "TC_H": "  H  " ,
        "TC_I": "  I  " ,
        "TC_J": "  J  " ,
        "TC_K": "  K  " ,
        "TC_L": "  L  " ,
        "TC_M": "  M  " ,
        "TC_N": "  N  " ,
        "TC_O": "  O  " ,
        "TC_P": "  P  " ,
        "TC_Q": "  Q  " ,
        "TC_R": "  R  " ,
        "TC_S": "  S  " ,
        "TC_T": "  T  " ,
        "TC_U": "  U  " ,
        "TC_V": "  V  " ,
        "TC_W": "  W  " ,
        "TC_X": "  X  " ,
        "TC_Y": "  Y  " ,
        "TC_Z": "  Z  " ,
        "TC_COMMA": "  ,  ",
        "TC_COMM": "  ,  ",
        "TC_DOT": "  .  ",
        "TC_SCLN": "  ;  ",
        "TC_SCLN": "  :  ",
        "TC_SLASH": "  \/  ",
        "TC_SLSH": "  \/  ",
        "TC_BSLS": "  \\  ",
        "TC_EXLM": "  !  ",
        "TC_PIPE": "  |  ",
        "TC_QUOT": "  '  ",
        "TC_HASH": "  #  ",
        "TC_AMPR": "  &  ",
        "TC_PERC": "  %  ",
        "TC_AT": "  @  ",
        "TC_DLR": "  $  ",
        "TC_CIRC": "  ^  ",
        "TC_EQL": "  =  ",
        "TC_ASTR": "  *  ",
        "TC_MINS": "  -  ",
        "TC_PLUS": "  +  ",
        "TC_LCBR": "  {  ",
        "TC_RCBR": "  }  ",
        "TC_LPRN": "  (  ",
        "TC_RPRN": "  )  ",
        "TC_GRV": "  `  ",
        "TC_LBRC": "  [  ",
        "TC_RBRC": "  ]  ",
        "TC_TILD": "  ~  ",
        "TC_ESC": "  ⎋  " ,
        "TC_CUT": "  ✄  " ,
        "TC_UNDO": "  ↶  " ,
        "TC_REDO": "  ↷  " ,
        "TC_VOLU": "  🕪  " ,
        "TC_VOLD": "  🕩  " ,
        "TC_MUTE":   "  🕨  " ,
        "TC_TAB": "  ⭾  " ,
        "TC_MENU": "  𝌆  " ,
        "TC_CAPSLOCK": "  ⇪  " ,
        "TC_NUMLK": "  ⇭  " ,
        "TC_SCRLK": "  ⇳  " ,
        "TC_PRSCR": "  ⎙  " ,
        "TC_PAUSE": "  ⎉  " ,
        "TC_BREAK": "  ⎊  " ,
        "TC_ENTER": "  ⏎  " ,
        "TC_BSPACE": "  ⌫  " ,
        "TC_DELETE": "  ⌦ " ,
        "TC_INSERT": "  ⎀  " ,
        "TC_LEFT": "  ◁  " ,
        "TC_RIGHT": "  ▷  " ,
        "TC_UP": "  △  " ,
        "TC_DOWN": "  ▽  " ,
        "TC_HOME": "  ⇤  " ,
        "TC_END": "  ⇥  " ,
        "TC_PGUP": "  ⇞  " ,
        "TC_PGDOWN": "  ⇟  " ,
        "TC_LSFT": "  ⇧  " ,
        "TC_RSFT": "  ⇧  " ,
        "TC_LCTL": "  ^  " ,
        "TC_RCTL": "  ^  " ,
        "TC_LALT": "  ⎇  " ,
        "TC_RALT": "  ⎇  " ,
        "TC_HYPER": "  ✧  " ,
        "TC_LGUI": "  ⌘  " ,
        "TC_RGUI": "  ⌘  "
    }
}
qmk-keyboard-format:json:end
*/