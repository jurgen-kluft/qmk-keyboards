#include QMK_KEYBOARD_H
#include "config.h"
#include "user_layers.h"
#include "user_keycodes.h"

// Base Layers = QWERTY, RSTHD
// Virtual Layers = SHIFT(QWERTY), SHIFT(RSTHD)
// Mode Layers = NONE or VIM
// Temporary Layers = SYMBOLS, NAVIGATION, FKEYS and NUMBERS

// This is to keep track of previously pressed keys that are not yet released
static uint8_t user_kb_state[40] = {KC_NO};

// clang-format off
static const uint8_t user_kb_layers[][40] = {
    [LAYER_QWERTY] = {
        TC_Q, TC_W, TC_E,    TC_R,    TC_T,                                                  TC_Y,    TC_U,     TC_I,          TC_O,        TC_P,    
        TC_A, TC_S, TC_D,    TC_F,    TC_G,                                                  TC_H,    TC_J,     TC_K,          TC_L,        TC_SCLN, 
        TC_Z, TC_X, TC_C,    TC_V,    TC_B,    CC_PDT,                            CC_NDT,    TC_N,    TC_M,     TC_COMMA,      TC_DOT,      TC_AT,
                    CC_FNUM, CC_FNUM, CC_FNAV, TC_SPACE,                          TC_BSPACE, CC_FSYM, CC_FCAPS, CC_FCAPS
    },
    [LAYER_RSTHD] = {
        TC_J,    TC_C, TC_Y,    TC_F,    TC_K,                                               TC_Z,     TC_L,     TC_BSPACE,     TC_U,        TC_Q,    
        TC_R,    TC_S, TC_T,    TC_H,    TC_D,                                               TC_M,     TC_N,     TC_A,          TC_I,        TC_O, 
        TC_SCLN, TC_V, TC_G,    TC_P,    TC_B,    CC_PDT,                            CC_NDT, TC_X,     TC_W,     TC_COMMA,      TC_DOT,      TC_AT,
                       CC_FNUM, CC_FNUM, CC_FNAV, TC_SPACE,                          TC_E,   CC_FSYM,  CC_FCAPS, CC_FCAPS
    },
    [LAYER_NUMBERS] = {
         TC_PLUS, TC_MINUS, TC_ASTR, TC_SLASH, CC_NO,                                                 TC_6,    TC_0,     TC_9,          TC_8,        TC_7,  
         TC_7,    TC_8,     TC_9,    TC_0,     TC_6,                                                  TC_5,    TC_1,     TC_2,          TC_3,        TC_4,  
         CC_CMD,  CC_ALT,   CC_CTRL, CC_SHFT,  CC_NO,   CC_NO,                             CC_NO,     CC_NO,   TC_EQUAL, TC_COMMA,      TC_DOT,      CC_NO,
                            CC_FNUM, CC_FNUM,  CC_FNAV, TC_SPACE,                          TC_BSPACE, CC_FSYM, CC_FCAPS, CC_FCAPS
    },
    [LAYER_SYMBOLS] = {
         TC_PERC, TC_AMPR,  TC_PIPE, TC_UNDS,   TC_TILD,                                               TC_GRV,   TC_QUOT,  TC_DQUO, TC_HASH, TC_DLR,   
         TC_EXLM, TC_MINUS, TC_PLUS, TC_EQUAL,  TC_LBRC,                                               TC_LABK,  TC_LPRN,  TC_LCBR, TC_RABK, TC_COLN,  
         TC_CIRC, TC_SLASH, TC_ASTR, TC_BSLASH, TC_RBRC, CC_NDT,                            CC_PDT,    CC_NO,    TC_RPRN,  TC_RCBR, TC_QUES, TC_AT,   
                            CC_FNUM, CC_FNUM,   CC_FNAV, TC_SPACE,                          TC_BSPACE, CC_FSYM,  CC_FCAPS, CC_FCAPS
    },
    [LAYER_NAVIGATION] = {
         CC_REDO, CC_CLOSE, TC_ESCAPE, TC_ENTER,  TC_TAB,                                                   TC_INSERT, TC_PGUP,   TC_HOME, CC_NO,    CC_NO,  
         CC_CMD,  CC_ALT,   CC_CTRL,   CC_SHFT,   TC_DELETE,                                                TC_LEFT,   TC_DOWN,   TC_UP,   TC_RIGHT, CC_NO,  
         CC_UNDO, CC_CUT,   CC_COPY,   CC_PASTE,  TC_SPACE,   CC_NDT,                            CC_PDT,    TC_SPACE,  TC_PGDOWN, TC_END,  CC_NO,    CC_NO,  
                            CC_FNUM,   CC_FNUM,   CC_FNAV,    TC_SPACE,                          TC_BSPACE, CC_FSYM,   CC_FCAPS,  CC_FCAPS
    },
    [LAYER_RAISE] = {
        CC_SECRET_5, CC_SECRET_6, CC_SECRET_7, CC_SECRET_8, CC_NO,                                                  TC_F12,  TC_F2,    TC_F3,  TC_F4, TC_F1, 
        CC_CMD,      CC_ALT,      CC_CTRL,     CC_SHFT,     CC_NO,                                                  TC_F5,   TC_F11,   TC_F10, TC_F9, CC_NO,  
        CC_SECRET_1, CC_SECRET_2, CC_SECRET_3, CC_SECRET_4, CC_NO,    CC_PDT,                            CC_NDT,    CC_NO,   TC_F6,    TC_F7,  TC_F8, CC_NO,  
                                  CC_FNUM,     CC_FNUM,     CC_FNAV,  TC_SPACE,                          TC_BSPACE, CC_FSYM, CC_FCAPS, CC_FCAPS
    },
    [LAYER_VIM] = {
        CC_VIM_CHAR,   CC_VIM_WORD,  CC_VIM_END,    CC_VIM_REDO,   CC_VIM_FIND,                                  CC_VIM_YANK,     CC_VIM_UNDO, CC_VIM_INSIDE, CC_VIM_LINE,   CC_VIM_PAGE,   
        CC_VIM_INSERT, CC_VIM_BEGIN, CC_VIM_DELETE, CC_VIM_SEARCH, CC_VIM_GOTO,                                  CC_VIM_LEFT,     CC_VIM_DOWN, CC_VIM_UP,     CC_VIM_RIGHT,  CC_VIM_APP,    
        CC_VIM_DOCU,   CC_VIM_CUT,   CC_VIM_CHANGE, CC_VIM_VISUAL, CC_VIM_INDENT,  CC_NO,                 CC_NO, CC_VIM_UNINDENT, CC_VIM_DELI, CC_VIM_CLEAR,  CC_VIM_REPEAT, CC_VIM_DESKTOP,
                                     CC_NO,         CC_NO,         CC_VIM_RAISE,   CC_NO,                 CC_NO, CC_VIM_RAISE,    CC_NO,       CC_NO
    },
    [LAYER_VIM_RAISE] = {
        CC_NO, CC_VIM_CHAR, CC_VIM_EXIT,        CC_VIM_ENTER,  CC_NO,                                      TC_6,          TC_0,  TC_9,  TC_8,  TC_7,
        CC_NO, CC_NO,       CC_VIM_DELETE_LINE, CC_NO,         CC_NO,                                      TC_5,          TC_1,  TC_2,  TC_3,  TC_4,
        CC_NO, CC_NO,       CC_NO,              CC_VIM_PASTE,  CC_NO,        CC_NO,                 CC_NO, CC_NO,         CC_NO, CC_NO, CC_NO, CC_NO,
                            CC_NO,              CC_NO,         CC_VIM_RAISE, CC_NO,                 CC_NO, CC_VIM_RAISE,  CC_NO, CC_NO
    },
};
// clang-format on

// The possible change of layers:
//
//       base    <-> nav
//       base    <-> symbols
//       base    <-> numbers
//       nav     <-> raise
//       symbols <-> raise
//       numbers <-> symbols
//       base    <-> vim
//       vim     <-> vim raise
//

static int8_t base_layer_mods = 0; // CC_SHIFT
static int8_t base_layer      = LAYER_QWERTY;
static int8_t current_layer   = LAYER_QWERTY;
void user_layer_on(int8_t layer)
{
    switch (layer)
    {
        case LAYER_RSTHD:
        case LAYER_QWERTY: current_layer = base_layer; break;
        case LAYER_SYMBOLS:
        case LAYER_NAVIGATION:
        case LAYER_NUMBERS:
        case LAYER_RAISE:
        case LAYER_VIM:
        case LAYER_VIM_RAISE:
        default: current_layer = layer; break;
    }
}

int8_t user_layer(void) { return current_layer; }

void user_smartshift_on() { base_layer_mods = 1; }
void user_smartshift_off() { base_layer_mods = 0; }

uint16_t user_layer_get_code(uint16_t keycode, bool pressed)
{
    uint8_t const ti = keycode - KL_00;
    keycode          = user_kb_layers[current_layer][ti];
    if (pressed)
    {
        user_kb_state[ti] = keycode;
    }
    else
    {
        keycode           = user_kb_state[ti];
        user_kb_state[ti] = KC_NO;
    }
    return keycode;
}

void user_apply_keycode(uint16_t keycode, bool pressed)
{
    if (keycode >= TC_RANGE_START && keycode <= TC_RANGE_END)
    {
        uint16_t kc = user_get_code16(keycode);
        if (kc != KC_NO)
        {
            if (pressed)
            {
                if (base_layer_mods)
                {
                    if (kc >= KC_A && kc <= KC_Z)
                    {
                        kc = LSFT(kc);
                    }
                    else
                    {
                        if (kc == KC_SCLN)
                        {
                            kc = KC_UNDS;
                        }
                    }
                    register_code16(kc);
                }
                else
                {
                    register_code16(kc);
                }
            }
            else
            {
                if (base_layer_mods)
                {
                    if (kc >= KC_A && kc <= KC_Z)
                    {
                        kc = LSFT(kc);
                    }
                    else
                    {
                        if (kc == KC_SCLN)
                        {
                            kc = KC_UNDS;
                        }
                    }
                    unregister_code16(kc);
                }
                else
                {
                    unregister_code16(kc);
                }
            }
        }
    }
}
