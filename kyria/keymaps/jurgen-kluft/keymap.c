#include QMK_KEYBOARD_H
#include "oled.h"
#include "layers.h"
#include "oneshot.h"
#include "cushi.h"
#include "cukey.h"
#include "feature.h"
#include "cheng.h"
#include "secrets.x"

#define KC_TRANS KC_TRANSPARENT
#define ____     KC_TRANSPARENT
#define xxxx     KC_NO
#define LT_MOS   TG(_MOUS)
#define LT_STENO TG(_STENO)
#define STENO_TIMING


// Symbols (C++) in order of frequency     space _ * , . ) ( ; - = / > " { & } : + # ` ] [ < % ! ' | ? @ $ ^ ~

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    xxxx, KC_Q, KC_W, KC_E,   KC_R,    KC_T,                                                 KC_Y,    KC_U,     KC_I,          KC_O,        KC_P,    xxxx,
    xxxx, KC_A, KC_S, KC_D,   KC_F,    KC_G,                                                 KC_H,    KC_J,     KC_K,          KC_L,        KC_SCLN, xxxx,
    xxxx, KC_Z, KC_X, KC_C,   KC_V,    KC_B,    KC_OS_PDT, xxxx,      xxxx, KC_OS_NDT, KC_N,    KC_M,     KC_COMMA_QUES, KC_DOT_EXCL, KC_UNDS, xxxx,
                      LT_MOS, KC_FNUM, KC_FNAV, KC_SPACE,  xxxx,      xxxx, KC_BSPACE, KC_FSYM, KC_FCAPS, LT_STENO
  ),
  [_RSTHD] = LAYOUT(
    xxxx, KC_J,    KC_C, KC_Y,   KC_F,    KC_K,                                        KC_Z,    KC_L,     KC_BSPACE,     KC_U,        KC_Q,    xxxx,
    xxxx, KC_R,    KC_S, KC_T,   KC_H,    KC_D,                                        KC_M,    KC_N,     KC_A,          KC_I,        KC_O,    xxxx,
    xxxx, KC_UNDS, KC_V, KC_G,   KC_P,    KC_B,    KC_OS_PDT, xxxx,   xxxx, KC_OS_NDT, KC_X,    KC_W,     KC_COMMA_QUES, KC_DOT_EXCL, KC_SCLN, xxxx,
                         LT_MOS, KC_FNUM, KC_FNAV, KC_SPACE,  xxxx,   xxxx, KC_E,      KC_FSYM, KC_FCAPS, LT_MOS
  ),
  [_STENO] = LAYOUT(
    xxxx, SC_Q, SC_W, SC_E, SC_R, SC_T,                               SC_Y, SC_U, SC_I,   SC_O,   SC_P,   xxxx,
    xxxx, SC_A, SC_S, SC_D, SC_F, SC_G,                               SC_H, SC_J, SC_K,   SC_L,   SC_SCN, xxxx,
    xxxx, SC_Z, SC_X, SC_C, SC_V, SC_B, ____,   xxxx,   xxxx, ____,   SC_N, SC_M, SC_CMA, SC_DOT, SC_SLS, xxxx,
                      ____, ____, ____, SC_SPC, xxxx,   xxxx, SC_BPC, ____, ____, ____
  ),
  [_QWERTY_CAPS] = LAYOUT(
    xxxx, LSFT(KC_Q), LSFT(KC_W), LSFT(KC_E), LSFT(KC_R), LSFT(KC_T),                           LSFT(KC_Y), LSFT(KC_U), LSFT(KC_I),    LSFT(KC_O),  LSFT(KC_P), xxxx,
    xxxx, LSFT(KC_A), LSFT(KC_S), LSFT(KC_D), LSFT(KC_F), LSFT(KC_G),                           LSFT(KC_H), LSFT(KC_J), LSFT(KC_K),    LSFT(KC_L),  KC_UNDS,    xxxx,
    xxxx, LSFT(KC_Z), LSFT(KC_X), LSFT(KC_C), LSFT(KC_V), LSFT(KC_B), ____, xxxx,   xxxx, ____, LSFT(KC_N), LSFT(KC_M), KC_COMMA_QUES, KC_DOT_EXCL, KC_AT,      xxxx,
                                  ____,       ____,       ____,       ____, xxxx,   xxxx, ____, ____,       ____,       ____
  ),
  [_RSTHD_CAPS] = LAYOUT(
    xxxx, LSFT(KC_J), LSFT(KC_C), LSFT(KC_Y), LSFT(KC_F), LSFT(KC_K),                                 LSFT(KC_Z), LSFT(KC_L), KC_BSPACE,     LSFT(KC_U),  LSFT(KC_Q), xxxx,
    xxxx, LSFT(KC_R), LSFT(KC_S), LSFT(KC_T), LSFT(KC_H), LSFT(KC_D),                                 LSFT(KC_M), LSFT(KC_N), LSFT(KC_A),    LSFT(KC_I),  LSFT(KC_O), xxxx,
    xxxx, KC_UNDS,    LSFT(KC_V), LSFT(KC_G), LSFT(KC_P), LSFT(KC_B), ____, xxxx,   xxxx, ____,       LSFT(KC_X), LSFT(KC_W), KC_COMMA_QUES, KC_DOT_EXCL, KC_AT,      xxxx,
                                  ____,       ____,       ____,       ____, xxxx,   xxxx, LSFT(KC_E), ____,       ____,       ____
  ),
  [_NUM] = LAYOUT(
    xxxx, xxxx, xxxx, KC_MS_BTN2,xxxx, xxxx,                                xxxx, KC_5, KC_6,     KC_7, KC_8, xxxx,
    xxxx, xxxx, xxxx, KC_9,      KC_0, xxxx,                                xxxx, KC_1, KC_2,     KC_3, KC_4, xxxx,
    xxxx, xxxx, xxxx, xxxx,      xxxx, xxxx, ____, xxxx,   xxxx, ____,      xxxx, xxxx, ____,     ____, xxxx, xxxx,
                      KC_SPACE,  ____, ____, ____, xxxx,   xxxx, KC_BSPACE, ____, ____, KC_SPACE
  ),
  [_MOUS] = LAYOUT(
    xxxx, KC_MPLY,    MU_TOG,      MU_MOD,  KC_OLED, RGB_SAD,                                    KC_MS_WH_UP,   KC_MS_BTN1,    KC_MS_UP,   KC_MS_BTN2,     RGB_SAI, xxxx,
    xxxx, OS_CMD,     OS_ALT,      OS_CTRL, OS_SHFT, RGB_HUD,                                    KC_MS_WH_DOWN, KC_MS_LEFT,    KC_MS_DOWN, KC_MS_RIGHT,    RGB_HUI, xxxx,
    xxxx, KC_OS_MODE, KC_OS_PMODE, ____,    ____,    RGB_VAD, ____,     xxxx,   xxxx, ____,      ____,          KC_MS_WH_LEFT, KC_MS_BTN3, KC_MS_WH_RIGHT, RGB_VAI, xxxx,
                                   ____,    ____,    ____,    KC_RSTHD, xxxx,   xxxx, KC_QWERTY, ____,          ____,          ____
  ),
  [_SYM] = LAYOUT(
    xxxx, KC_PERC, KC_AMPR,  KC_PIPE, KC_UNDS,   KC_TILD,                           KC_GRV,  KC_QUOT, KC_DQUO, KC_HASH,  KC_DLR,  xxxx, 
    xxxx, KC_EXLM, KC_MINUS, KC_PLUS, KC_EQUAL,  KC_LBRC,                           KC_LABK, KC_LPRN, KC_LCBR, KC_RABK,  KC_COLN, xxxx, 
    xxxx, KC_CIRC, KC_SLASH, KC_ASTR, KC_BSLASH, KC_RBRC, ____, xxxx,   xxxx, ____, SH_TG,   KC_RPRN, KC_RCBR, KC_QUES,  KC_AT,   xxxx, 
                             ____,    ____,      ____,    ____, xxxx,   xxxx, ____, ____,    ____,    ____                              
  ),
  [_NAV] = LAYOUT(
    xxxx, KC_OS_REDO, KC_OS_CLOSE, KC_ESCAPE,  KC_ENTER,    KC_TAB,                                   KC_INSERT, KC_PGUP,   KC_HOME, ____,     ____, xxxx, 
    xxxx, OS_CMD,     OS_ALT,      OS_CTRL,    OS_SHFT,     KC_DELETE,                                KC_LEFT,   KC_DOWN,   KC_UP,   KC_RIGHT, ____, xxxx, 
    xxxx, KC_OS_UNDO, KC_OS_CUT,   KC_OS_COPY, KC_OS_PASTE, SH_TG,     ____, xxxx,   xxxx, ____,      KC_TRANS,  KC_PGDOWN, KC_END,  ____,     ____, xxxx, 
                                   ____,       ____,        ____,      ____, xxxx,   xxxx, KC_BSPACE, ____,      ____,      ____                           
  ),
  [_RAISE] = LAYOUT(
    xxxx, xxxx,        xxxx,          xxxx,           xxxx,           xxxx,                                KC_F12,    KC_F2,  KC_F3,  KC_F4, KC_F1, xxxx,
    xxxx, OS_CMD,      OS_ALT,        OS_CTRL,        OS_SHFT,        xxxx,                                KC_F5,     KC_F11, KC_F10, KC_F9, xxxx,  xxxx,
    xxxx, KC_SECRET_1, KC_SECRET_2,   KC_SECRET_3,    KC_SECRET_4,    KC_OS_PDT, ____, xxxx,   xxxx, ____, KC_OS_NDT, KC_F6,  KC_F7,  KC_F8, xxxx,  xxxx,
                                      ____,           ____,           ____,      ____, xxxx,   xxxx, ____, ____,      ____,   ____
  )
};
// clang-format on

#ifdef ENABLE_ONESHOT

bool is_oneshot_modifier_cancel_key(uint16_t keycode)
{

    switch (keycode)
    {
        case KC_FNAV:
        case KC_FNUM:
        case KC_FCAPS: return true;
        default: return false;
    }
}

bool is_oneshot_modifier_ignored_key(uint16_t keycode)
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
        case OS_SHFT: return ONESHOT_LSFT;
        case OS_CTRL: return ONESHOT_LCTL;
        case OS_ALT: return ONESHOT_LALT;
        case OS_CMD: return ONESHOT_LGUI;
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
        case KC_OS_MODE ... KC_OS_CLOSE:
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
        case KC_SECRET_1:
            if (record->event.pressed)
            {
                SEND_STRING(SECRET_1);
            }
            return true;
        case KC_SECRET_2:
            if (record->event.pressed)
            {
                SEND_STRING(SECRET_2);
            }
            return true;
        case KC_SECRET_3:
            if (record->event.pressed)
            {
                SEND_STRING(SECRET_3);
            }
            return true;
        case KC_SECRET_4:
            if (record->event.pressed)
            {
                SEND_STRING(SECRET_4);
            }
            return true;
        case KC_DCOLN:
            if (record->event.pressed)
            {
                tap_code16(KC_COLN);
            }
            else
            {
                tap_code16(KC_COLN);
            }
            break;
        case KC_OLED:
            if (record->event.pressed)
            {
                toggle_display_oled();
#ifdef RGBLIGHT_ENABLE
                rgblight_enable();
#endif
            }
            return true;
    }

    int8_t keycode_consumed = 0;

    if (!process_feature_key(keycode, record))
    {
        return false;
    }

#ifdef ENABLE_ONESHOT
    keycode_consumed += update_oneshot_modifiers(keycode, record, keycode_consumed);
#endif

    if (!process_cushi_keys(keycode, record))
    {
        return false;
    }

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

    return true;
};

// Layer-specific encoder knob functions
#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise)
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
      "KC_FNAV": "green",
  },
  "vizcellwidth": 5,
  "vizemits": [
  ],
  "vizline": "//#",
  "vizemits": [
      { "line": "LAYOUT => _QWERTY", "layer": "_QWERTY" },
      { "line": "LAYOUT => _QWERTY_CAPS", "layer": "_QWERTY_CAPS" },
      { "line": "LAYOUT => _SSYM", "layer": "_SSYM" },
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
      "LSFT(KC_A)": "  A  " ,
      "LSFT(KC_B)": "  B  " ,
      "LSFT(KC_C)": "  C  " ,
      "LSFT(KC_D)": "  D  " ,
      "LSFT(KC_E)": "  E  " ,
      "LSFT(KC_F)": "  F  " ,
      "LSFT(KC_G)": "  G  " ,
      "LSFT(KC_H)": "  H  " ,
      "LSFT(KC_I)": "  I  " ,
      "LSFT(KC_J)": "  J  " ,
      "LSFT(KC_K)": "  K  " ,
      "LSFT(KC_L)": "  L  " ,
      "LSFT(KC_M)": "  M  " ,
      "LSFT(KC_N)": "  N  " ,
      "LSFT(KC_O)": "  O  " ,
      "LSFT(KC_P)": "  P  " ,
      "LSFT(KC_Q)": "  Q  " ,
      "LSFT(KC_R)": "  R  " ,
      "LSFT(KC_S)": "  S  " ,
      "LSFT(KC_T)": "  T  " ,
      "LSFT(KC_U)": "  U  " ,
      "LSFT(KC_V)": "  V  " ,
      "LSFT(KC_W)": "  W  " ,
      "LSFT(KC_X)": "  X  " ,
      "LSFT(KC_Y)": "  Y  " ,
      "LSFT(KC_Z)": "  Z  " ,
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
