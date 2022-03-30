#include QMK_KEYBOARD_H
#include "layers.h"
#include "oneshot.h"
#include "cushi.h"
#include "cukey.h"
#include "feature.h"
#include "cheng.h"
#include "leader_user.h"
#include "layouts.h"

#ifdef OLED_ENABLE
#include "oled.h"
#endif

#define KC_TRANS KC_TRANSPARENT
#define ____     KC_TRANSPARENT
#define xxxx     KC_NO
#define LT_MOS   TG(_MOUS)

#if (__has_include("secrets.x") && !defined(NO_SECRETS))
#include "secrets.x"
static const char* gSecrets[] = {SECRET_1, SECRET_2, SECRET_3, SECRET_4, SECRET_5, SECRET_6, SECRET_7, SECRET_8};
#else
static const char* gSecrets[] = {"SECRET_1", "SECRET_2", "SECRET_3", "SECRET_4", "SECRET_5", "SECRET_6", "SECRET_7", "SECRET_8"};
#endif

// This is a LAYOUT that maps a Kyria layout to a Hillside layout.
// I do this so that I can use the same keymap for both keyboards.
// Next step is to actually share this keymap between keyboards.
#ifdef KEYBOARD_HILLSIDE
#undef LAYOUT
#define LAYOUT KYRIA_TO_HILLSIDE_LAYOUT
#endif

// Symbols (C++) in order of frequency     space _ * , . ) ( ; - = / > " { & } : + # ` ] [ < % ! ' | ? @ $ ^ ~

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    xxxx, KC_Q, KC_W, KC_E,   KC_R,    KC_T,                                        KC_Y,    KC_U,     KC_I,          KC_O,        KC_P,    xxxx, 
    xxxx, KC_A, KC_S, KC_D,   KC_F,    KC_G,                                        KC_H,    KC_J,     KC_K,          KC_L,        KC_SCLN, xxxx, 
    xxxx, KC_Z, KC_X, KC_C,   KC_V,    KC_B,    KC_OS_PDT, xxxx,   xxxx, KC_OS_NDT, KC_N,    KC_M,     KC_COMMA_QUES, KC_DOT_EXCL, KC_UNDS, xxxx, 
                      LT_MOS, KC_FNUM, KC_FNAV, KC_SPACE,  xxxx,   xxxx, KC_BSPACE, KC_FSYM, KC_FCAPS, LT_MOS                                   
  ),
  [_RSTHD] = LAYOUT(
    xxxx, KC_J,    KC_C, KC_Y,   KC_F,    KC_K,                                        KC_Z,    KC_L,     KC_BSPACE,     KC_U,        KC_Q,    xxxx, 
    xxxx, KC_R,    KC_S, KC_T,   KC_H,    KC_D,                                        KC_M,    KC_N,     KC_A,          KC_I,        KC_O,    xxxx, 
    xxxx, KC_SCLN, KC_V, KC_G,   KC_P,    KC_B,    KC_OS_PDT, xxxx,   xxxx, KC_OS_NDT, KC_X,    KC_W,     KC_COMMA_QUES, KC_DOT_EXCL, KC_UNDS, xxxx, 
                         LT_MOS, KC_FNUM, KC_FNAV, KC_SPACE,  xxxx,   xxxx, KC_E,      KC_FSYM, KC_FCAPS, LT_MOS                                     
  ),
  [_QWERTY_CAPS] = LAYOUT(
    xxxx, S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T),                           S(KC_Y), S(KC_U), S(KC_I),       S(KC_O),     S(KC_P), xxxx, 
    xxxx, S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G),                           S(KC_H), S(KC_J), S(KC_K),       S(KC_L),     KC_UNDS, xxxx, 
    xxxx, S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), ____, xxxx,   xxxx, ____, S(KC_N), S(KC_M), KC_COMMA_QUES, KC_DOT_EXCL, KC_AT,   xxxx, 
                            ____,    ____,    ____,    ____, xxxx,   xxxx, ____, ____,    ____,    ____                                       
  ),
  [_RSTHD_CAPS] = LAYOUT(
    xxxx, S(KC_J), S(KC_C), S(KC_Y), S(KC_F), S(KC_K),                              S(KC_Z), S(KC_L), KC_BSPACE,     S(KC_U),     S(KC_Q), xxxx, 
    xxxx, S(KC_R), S(KC_S), S(KC_T), S(KC_H), S(KC_D),                              S(KC_M), S(KC_N), S(KC_A),       S(KC_I),     S(KC_O), xxxx, 
    xxxx, KC_UNDS, S(KC_V), S(KC_G), S(KC_P), S(KC_B), ____, xxxx,   xxxx, ____,    S(KC_X), S(KC_W), KC_COMMA_QUES, KC_DOT_EXCL, KC_AT,   xxxx, 
                            ____,    ____,    ____,    ____, xxxx,   xxxx, S(KC_E), ____,    ____,    ____                                       
  ),
  [_NUM] = LAYOUT(
    xxxx, xxxx, xxxx, KC_MINUS, KC_PLUS,  xxxx,                                    xxxx, KC_5, KC_6, KC_7, KC_8, xxxx, 
    xxxx, xxxx, xxxx, KC_9,     KC_0,     KC_EQUAL,                                xxxx, KC_1, KC_2, KC_3, KC_4, xxxx, 
    xxxx, xxxx, xxxx, KC_ASTR,  KC_SLASH, xxxx,     ____, xxxx,   xxxx, ____,      xxxx, xxxx, ____, ____, xxxx, xxxx, 
                      ____,     ____,     ____,     ____, xxxx,   xxxx, KC_BSPACE, ____, ____, ____                    
  ),
  [_MOUS] = LAYOUT(
    xxxx, KC_MPLY,    MU_TOG,      MU_MOD,  KC_OLED, RGB_SAD,                                      KC_MS_WH_UP,    KC_MS_BTN1,    KC_MS_UP,      KC_MS_BTN2,     RGB_SAI, xxxx, 
    xxxx, OS_CMD,     OS_ALT,      OS_CTRL, OS_SHFT, RGB_HUD,                                      KC_MS_WH_DOWN,  KC_MS_LEFT,    KC_MS_DOWN,    KC_MS_RIGHT,    RGB_HUI, xxxx, 
    xxxx, ____,         ____,         ____,    ____, RGB_VAD,     ____,  xxxx,   xxxx,       ____,          ____,  KC_MS_WH_LEFT, KC_MS_BTN3,    KC_MS_WH_RIGHT, RGB_VAI, xxxx, 
                                      ____,    ____,    ____, KC_RSTHD,  xxxx,   xxxx,  KC_QWERTY,          ____,           ____,          ____                                       
  ),
  [_SYM] = LAYOUT(
    xxxx, KC_PERC, KC_AMPR,  KC_PIPE, KC_UNDS,   KC_TILD,                           KC_GRV,  KC_QUOT, KC_DQUO, KC_HASH, KC_DLR,  xxxx, 
    xxxx, KC_EXLM, KC_MINUS, KC_PLUS, KC_EQUAL,  KC_LBRC,                           KC_LABK, KC_LPRN, KC_LCBR, KC_RABK, KC_COLN, xxxx, 
    xxxx, KC_CIRC, KC_SLASH, KC_ASTR, KC_BSLASH, KC_RBRC, ____, xxxx,   xxxx, ____, SH_TG,   KC_RPRN, KC_RCBR, KC_QUES, KC_AT,   xxxx, 
                             ____,    ____,      ____,    ____, xxxx,   xxxx, ____, ____,    ____,    ____                             
  ),
  [_NAV] = LAYOUT(
    xxxx, KC_OS_REDO, KC_OS_CLOSE, KC_ESCAPE,  KC_ENTER,    KC_TAB,                                   KC_INSERT, KC_PGUP,   KC_HOME, KC_NO,    KC_NO, xxxx, 
    xxxx, OS_CMD,     OS_ALT,      OS_CTRL,    OS_SHFT,     KC_DELETE,                                KC_LEFT,   KC_DOWN,   KC_UP,   KC_RIGHT, KC_NO, xxxx, 
    xxxx, KC_OS_UNDO, KC_OS_CUT,   KC_OS_COPY, KC_OS_PASTE, SH_TG,     ____, xxxx,   xxxx, ____,      KC_TRANS,  KC_PGDOWN, KC_END,  KC_NO,    KC_NO, xxxx, 
                                   ____,       ____,        ____,      ____, xxxx,   xxxx, KC_BSPACE, ____,      ____,      ____                           
  ),
  [_RAISE] = LAYOUT(
    xxxx, KC_SECRET_5, KC_SECRET_6, KC_SECRET_7, KC_SECRET_8, KC_4,                                KC_F12,    KC_F2,  KC_F3,  KC_F4, KC_F1, xxxx, 
    xxxx, OS_CMD,      OS_ALT,      OS_CTRL,     OS_SHFT,     xxxx,                                KC_F5,     KC_F11, KC_F10, KC_F9, xxxx,  xxxx, 
    xxxx, KC_SECRET_1, KC_SECRET_2, KC_SECRET_3, KC_SECRET_4, KC_OS_PDT, ____, xxxx,   xxxx, ____, KC_OS_NDT, KC_F6,  KC_F7,  KC_F8, xxxx,  xxxx, 
                                    ____,        ____,        ____,      ____, xxxx,   xxxx, ____, ____,      ____,   ____                        
  )
};
// clang-format on

#ifdef ENABLE_ONESHOT

bool is_oneshot_modifier_cancel_key(uint16_t keycode, bool pressed)
{
    switch (keycode)
    {
        case KC_FNAV:
        case KC_FCAPS: return pressed;
    }
    return false;
}

bool is_oneshot_modifier_ignored_key(uint16_t keycode, bool pressed)
{
    switch (keycode)
    {
        case KC_FNAV:
        case KC_FSYM: return true;
    }
    return false;
}

oneshot_mod get_modifier_for_trigger_key(uint16_t keycode)
{
    switch (keycode)
    {
        case OS_CTRL:
        case OS_SHFT:
        case OS_ALT:
        case OS_CMD: return (keycode - OS_CTRL) + ONESHOT_LCTL;
    }
    return ONESHOT_NONE;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
#ifdef OLED_DRIVER_ENABLE
    process_record_oled(keycode, record);
#endif

    if (process_record_cheng(keycode, record))
        return false;

    switch (keycode)
    {
        case KC_OS_UNDO ... KC_OS_CLOSE:
        {
            if (!process_cushi_keys(keycode, record))
                return false;

            if (record->event.pressed)
            {
                keycode = process_cukey(keycode);
                if (keycode != KC_NO)
                    tap_code16(keycode);
            }

            return false;
        }
        case KC_SECRET_1 ... KC_SECRET_8: // Secrets!  Externally defined strings, not stored in repo
            if (!record->event.pressed)
            {
                turnoff_oneshot_modifiers();
                send_string_with_delay(gSecrets[keycode - KC_SECRET_1], MACRO_TIMER);
            }
            return false;
            break;
        case KC_OLED:
            if (record->event.pressed)
            {
#ifdef OLED_ENABLE
                toggle_display_oled();
#endif
#ifdef RGBLIGHT_ENABLE
                rgblight_enable();
#endif
            }
            return true;
    }

    if (!process_feature_key(keycode, record))
    {
        return false;
    }

    if (!process_cushi_keys(keycode, record))
    {
        return false;
    }

    update_oneshot_modifiers(keycode, record);

    switch (keycode)
    {
        case KC_QWERTY:
            if (record->event.pressed)
            {
                set_single_persistent_default_layer(_QWERTY);
            }
            break;
        case KC_RSTHD:
            if (record->event.pressed)
            {
                set_single_persistent_default_layer(_RSTHD);
            }
            break;
    }

    if (process_leader_user(keycode, record))
        return false;

    return true;
}

// Layer-specific encoder knob functions
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise)
{
    uint16_t layers = (layer_state | default_layer_state);
    if (index == 0)
    { // left knob
        switch (get_highest_layer(layers))
        {
            case _MOUS: // Underglow color
#ifdef RGBLIGHT_ENABLE
                if (clockwise)
                {
                    rgblight_increase_hue();
                }
                else
                {
                    rgblight_decrease_hue();
                }
#endif
                break;
            default: // Volume Up/Down
                if (clockwise)
                {
                    tap_code(KC_VOLD);
                }
                else
                {
                    tap_code(KC_VOLU);
                }
                break;
        }
    }
    else if (index == 1)
    { // right knob
        switch (get_highest_layer(layers))
        {
            case _NAV:
                if (clockwise)
                {
                    tap_code(KC_MS_WH_DOWN);
                }
                else
                {
                    tap_code(KC_MS_WH_UP);
                }
                break;
            case _MOUS: // Underglow brightness
#ifdef RGBLIGHT_ENABLE
                if (clockwise)
                {
                    rgblight_increase_val();
                }
                else
                {
                    rgblight_decrease_val();
                }
#endif
                break;
            default:
                if (clockwise)
                {
                    tap_code(KC_BRIU);
                }
                else
                {
                    tap_code(KC_BRID);
                }
                break;
        }
    }
    return false;
}
#endif


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
