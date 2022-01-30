#include QMK_KEYBOARD_H
#include "version.h"
#include "smart.h"
#include "oneshot.h"
#include "layers.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)
#define MOON_LED_LEVEL LED_LEVEL
#define KC_NDT LCTL(LGUI(KC_RIGHT))
#define KC_PDT LCTL(LGUI(KC_LEFT))
#undef LAYOUT
#define LAYOUT LAYOUT_moonlander

#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)
#define LA_FNC MO(_FNC)

enum custom_keycodes
{
    RGB_SLD = ML_SAFE_RANGE,
    KC_PASSWORD,
    KC_QWERTY,
    KC_RSTHD,
    KC_OLED,
    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    KC_SMART_CAPSLOCK,
    KC_SMART_NUMBER,
    UC_SHRG,  // ¯\_(ツ)_/¯
    UC_DISA,  // ಠ_ಠ
    UC_LVIT,  // ♥‿♥
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
   KC_TRNS,       KC_TRNS, KC_TRNS,   KC_TRNS,         KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS, KC_PASSWORD,           KC_TRNS,   KC_TRNS,  KC_TRNS, TG(_MOUS), TG(_GAMEL),        
   KC_TRNS,       KC_Q,    KC_W,      KC_E,            KC_R,     KC_T,      KC_NDT,    KC_PDT,  KC_Y,              KC_U,      KC_I,     KC_O,    KC_P,      KC_TRNS,           
   KC_TRNS,       KC_A,    KC_S,      KC_D,            KC_F,     KC_G,      KC_PDT,    KC_NDT,  KC_H,              KC_J,      KC_K,     KC_L,    KC_SCOLON, KC_TRNS, 
   KC_TRNS,       KC_Z,    KC_X,      KC_C,            KC_V,     KC_B,                          KC_N,              KC_M,      KC_COMMA, KC_DOT,  KC_SLASH,  KC_TRNS,           
   KC_TRNS,       KC_TRNS, TG(_MOUS), KC_TRNS, MO(_NAV), KC_TRNS,                               KC_BSPACE,         MO(_SYM),  MO(_FNC), KC_TRNS, KC_TRNS,   KC_RSTHD,           
                                                       KC_SPACE, KC_BSPACE, KC_TRNS,   KC_TRNS, KC_TRNS,           KC_BSPACE                                                   
  ),
  [_RSTHD] = LAYOUT(
   KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS, KC_PASSWORD,           KC_TRNS,  KC_TRNS,   KC_TRNS,   TG(_MOUS), TG(_GAMEL),        
   KC_TRNS,       KC_J,    KC_C,    KC_Y,            KC_F,     KC_K,      KC_NDT,    KC_PDT,  KC_Z,              KC_L,     KC_BSPACE, KC_U,      KC_Q,      KC_TRNS,           
   KC_TRNS,       KC_R,    KC_S,    KC_T,            KC_H,     KC_D,      KC_PDT,    KC_NDT,  KC_M,              KC_N,     KC_A,      KC_I,      KC_O,      KC_TRNS, 
   KC_TRNS,       KC_UNDS, KC_V,    KC_G,            KC_P,     KC_B,                          KC_X,              KC_W,     KC_COMMA,  KC_DOT,    KC_SCLN,   KC_TRNS,           
   KC_TRNS,       KC_TRNS, KC_TRNS, KC_SMART_NUMBER, MO(_NAV), KC_TRNS,                       KC_BSPACE,         MO(_SYM), MO(_FNC),  KC_TRNS,   KC_TRNS,   KC_QWERTY,           
                                                     KC_SPACE, KC_BSPACE, KC_TRNS,   KC_TRNS, KC_TRNS,           KC_E                                                         
  ),
  [_QWERTY_CAPS] = LAYOUT(
   KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS, 
   KC_TRNS, LSFT(KC_Q), LSFT(KC_W), LSFT(KC_E), LSFT(KC_R), LSFT(KC_T), KC_TRNS,   KC_TRNS, LSFT(KC_Y), LSFT(KC_U), LSFT(KC_I),     LSFT(KC_O),   LSFT(KC_P), KC_TRNS, 
   KC_TRNS, LSFT(KC_A), LSFT(KC_S), LSFT(KC_D), LSFT(KC_F), LSFT(KC_G), KC_TRNS,   KC_TRNS, LSFT(KC_H), LSFT(KC_J), LSFT(KC_K),     LSFT(KC_L),   KC_UNDS,    KC_TRNS, 
   KC_TRNS, LSFT(KC_Z), LSFT(KC_X), LSFT(KC_C), LSFT(KC_V), LSFT(KC_B),                     LSFT(KC_N), LSFT(KC_M), LSFT(KC_COMMA), LSFT(KC_DOT), KC_AT,      KC_TRNS, 
   KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                        KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS, 
                                                KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS, KC_TRNS,    KC_TRNS                                                        
  ),
  [_RSTHD_CAPS] = LAYOUT(
   KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,         KC_TRNS,    KC_TRNS, 
   KC_TRNS, LSFT(KC_J), LSFT(KC_C), LSFT(KC_Y), LSFT(KC_F), LSFT(KC_K), KC_TRNS,   KC_TRNS, LSFT(KC_Z), LSFT(KC_L), KC_BSPACE,  LSFT(KC_U),      LSFT(KC_P), KC_TRNS, 
   KC_TRNS, LSFT(KC_R), LSFT(KC_S), LSFT(KC_T), LSFT(KC_H), LSFT(KC_D), KC_TRNS,   KC_TRNS, LSFT(KC_M), LSFT(KC_N), LSFT(KC_A), LSFT(KC_I),      LSFT(KC_O), KC_TRNS, 
   KC_TRNS, KC_UNDS,    LSFT(KC_V), LSFT(KC_G), LSFT(KC_P), LSFT(KC_B),                     LSFT(KC_X), LSFT(KC_W), KC_COMMA,   KC_DOT,          KC_AT,      KC_TRNS, 
   KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,         KC_TRNS,    KC_TRNS, 
                                                KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS, KC_TRNS,    LSFT(KC_E)                                                    
  ),
  [_SMART_NUM] = LAYOUT(
   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,     KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
   KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRACKET, KC_RBRACKET, KC_SLASH, KC_TRNS,   KC_TRNS, KC_MINUS, KC_LPRN, KC_RPRN, KC_TRNS, KC_TRNS, KC_TRNS, 
   KC_TRNS, KC_5,    KC_6,    KC_7,        KC_8,        KC_ASTR,  KC_TRNS,   KC_TRNS, KC_PLUS,  KC_1,    KC_2,    KC_3,    KC_4,    KC_TRNS, 
   KC_TRNS, KC_TRNS, KC_TRNS, KC_EQUAL,    KC_9,        KC_TRNS,                      KC_TRNS,  KC_0,    KC_EQUAL, KC_TRNS, KC_TRNS, KC_TRNS, 
   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,     KC_TRNS,                      KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                                           KC_TRNS,     KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS                                      
  ),
  [_SYM] = LAYOUT(
   KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,     KC_TRNS,     KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_NO,   KC_NO,   
   KC_NO,   KC_TRNS, KC_SLASH,  KC_LBRACKET, KC_RBRACKET, KC_CIRC,  KC_TRNS,   KC_TRNS, KC_DQUO,  KC_LABK, KC_RABK, KC_UNDS,  KC_TILD, KC_NO,   
   KC_TRNS, KC_HASH, KC_EQUAL,  KC_LCBR,     KC_RCBR,     KC_ASTR,  KC_TRNS,   KC_TRNS, KC_PLUS,  KC_LPRN, KC_RPRN, KC_MINUS, KC_COLN, KC_NO,   
   KC_TRNS, KC_DLR,  KC_BSLASH, KC_PIPE,     KC_AMPR,     KC_GRAVE,                     KC_QUOTE, KC_PERC, KC_EXLM, KC_QUES,  KC_AT,   KC_TRNS, 
   KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,     KC_SMART_NUMBER,    KC_TRNS,                      KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, 
                                             KC_TRNS,     KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS                                       
  ),
  [_NUM] = LAYOUT(
   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, 
   KC_TRNS, KC_TRNS, KC_TRNS, KC_ASTR,  KC_PLUS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_MINUS, KC_SLASH, KC_TRNS, KC_TRNS, KC_TRNS, 
   KC_TRNS, KC_5,    KC_6,    KC_7,     KC_8,    KC_EQUAL, KC_TRNS,   KC_TRNS, KC_TRNS, KC_1,     KC_2,     KC_3,    KC_4,    KC_TRNS, 
   KC_TRNS, KC_TRNS, KC_TRNS, KC_EQUAL, KC_9,    KC_TRNS,                      KC_TRNS, KC_0,     KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, 
   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                      KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, 
                                        KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS                                        
  ),
  [_NAV] = LAYOUT(
   KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,  KC_NO,   KC_NO,   
   KC_NO,   KC_TRNS,    LCTL(KC_W), KC_ESCAPE,  KC_ENTER,    KC_TAB,    KC_TRNS,   KC_TRNS, KC_INSERT, KC_PGUP,   KC_HOME, KC_TRNS,  KC_TRNS, KC_NO,   
   KC_TRNS, OS_CMD,     OS_ALT,     OS_CTRL,    OS_SHFT,     KC_DELETE, KC_TRNS,   KC_TRNS, KC_LEFT,   KC_DOWN,   KC_UP,   KC_RIGHT, KC_TRNS, KC_TRNS, 
   KC_TRNS, KC_PC_UNDO, KC_PC_CUT,  KC_PC_COPY, KC_PC_PASTE, KC_BSPACE,                     KC_DELETE, KC_PGDOWN, KC_END,  KC_TRNS,  KC_TRNS, KC_TRNS, 
   KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,                       KC_TRNS,   KC_SMART_CAPSLOCK,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, 
                                                KC_TRNS,     KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,   KC_TRNS                                         
  ),
  [_FNC] = LAYOUT(
   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
   KC_TRNS, KC_F12,  KC_F11,  KC_F10,  KC_F9,   KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
   KC_TRNS, KC_F8,   KC_F7,   KC_F6,   KC_F5,   KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_TRNS, 
   KC_TRNS, KC_F4,   KC_F3,   KC_F2,   KC_F1,   KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                                       KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS                                      
  ),
  [_MOUS] = LAYOUT(
   AU_TOG,  RGB_TOG,   TOGGLE_LAYER_COLOR, RGB_VAD,          RGB_VAI,            RGB_SAD,       RGB_SAI,             RESET,   WEBUSB_PAIR, KC_TRNS,       KC_TRNS,    KC_TRNS,        KC_TRNS,             KC_NO,   
   KC_TRNS, KC_TRNS,   KC_TRNS,            KC_BRIGHTNESS_UP, KC_BRIGHTNESS_DOWN, KC_MS_WH_UP,   KC_AUDIO_VOL_UP,     KC_TRNS, KC_EQUAL,    KC_MS_BTN1,    KC_MS_UP,   KC_MS_BTN2,     KC_MEDIA_PREV_TRACK, KC_TRNS, 
   KC_TRNS, KC_LGUI,   KC_LALT,            KC_LCTRL,         KC_LSHIFT,          KC_MS_WH_DOWN, KC_AUDIO_VOL_DOWN,   KC_TRNS, KC_MINUS,    KC_MS_LEFT,    KC_MS_DOWN, KC_MS_RIGHT,    KC_MEDIA_NEXT_TRACK, MU_TOG,  
   KC_TRNS, KC_TRNS,   KC_TRNS,            KC_TRNS,          KC_TRNS,            KC_TRNS,                                     KC_TRNS,     KC_MS_WH_LEFT, KC_MS_BTN3, KC_MS_WH_RIGHT, KC_TRNS,             MU_MOD,  
   KC_TRNS, KC_TRNS,   KC_TRNS,            KC_TRNS,          KC_TRNS,            KC_TRNS,                                     KC_TRNS,     KC_TRNS,       KC_TRNS,    KC_TRNS,        KC_TRNS,             KC_TRNS, 
                                                             KC_TRNS,            KC_TRNS,       KC_TRNS,             KC_TRNS, KC_TRNS,     KC_TRNS                                                                  
  ),
  [_GAMEL] = LAYOUT(
   KC_TRNS,   KC_1,  KC_2,       KC_3,     KC_4,     KC_5,      KC_TRNS,   KC_0,    KC_6,    KC_7,    KC_8,      KC_9,    KC_NO,     KC_TRNS, 
   KC_TAB,    KC_Q,  KC_W,       KC_E,     KC_R,     KC_T,      KC_NO,     KC_TRNS, KC_Y,    KC_U,    KC_I,      KC_O,    KC_P,      KC_TRNS, 
   KC_ESCAPE, KC_A,  KC_S,       KC_D,     KC_F,     KC_G,      KC_NO,     KC_NO,   KC_H,    KC_J,    KC_K,      KC_L,    KC_SCOLON, KC_TRNS, 
   KC_LSHIFT, KC_Z,  KC_X,       KC_C,     KC_V,     KC_B,                          KC_N,    KC_M,    KC_COMMA,  KC_DOT,  KC_SLASH,  KC_TRNS, 
   KC_NO,     KC_NO, MO(_GAMER), KC_LCTRL, KC_LALT,  KC_ENTER,                      KC_TRNS, KC_LALT, KC_LSHIFT, KC_TRNS, KC_TRNS,   KC_TRNS, 
                                           KC_SPACE, KC_BSPACE, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS                                          
  ),
  [_GAMER] = LAYOUT(
   KC_TRNS,   KC_0,      KC_9,    KC_8,     KC_7,     KC_6,      KC_TRNS,   KC_0,    KC_6,    KC_7,    KC_8,     KC_9,    KC_NO,     KC_TRNS,   
   KC_TRNS,   KC_P,      KC_O,    KC_I,     KC_U,     KC_Y,      KC_NO,     KC_TRNS, KC_Y,    KC_U,    KC_I,     KC_O,    KC_P,      KC_TRNS,   
   KC_ESCAPE, KC_SCOLON, KC_L,    KC_K,     KC_J,     KC_H,      KC_NO,     KC_NO,   KC_H,    KC_J,    KC_K,     KC_L,    KC_SCOLON, KC_TRNS,   
   KC_LSHIFT, KC_SLASH,  KC_DOT,  KC_COMMA, KC_M,     KC_N,                          KC_N,    KC_M,    KC_COMMA, KC_DOT,  KC_SLASH,  KC_RSHIFT, 
   KC_TRNS,   KC_NO,     KC_TRNS, KC_LCTRL, KC_LALT,  KC_ENTER,                      KC_TRNS, KC_LALT, KC_LCTRL, KC_TRNS, KC_NO,     KC_NO,     
                                            KC_SPACE, KC_BSPACE, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS                                           
  )
};
// clang-format on

extern bool         g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) { rgb_matrix_enable(); }

// clang-format off
const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = { {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195} },
    [1] = { {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187} },
    [2] = { {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198} },
    [3] = { {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198} },
    [4] = { {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198} },
    [5] = { {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218} },
    [6] = { {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228} },
    [7] = { {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152} },
    [8] = { {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228} },
    [9] = { {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {0,183,238}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195} },
    [10] = { {0,183,238}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {141,255,233}, {141,255,233}, {0,183,238}, {141,255,233}, {0,0,0}, {141,255,233}, {0,183,238}, {0,183,238}, {141,255,233}, {154,255,255}, {141,255,233}, {141,255,233}, {0,183,238}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {0,0,0}, {0,0,0}, {141,255,233}, {141,255,233}, {0,0,0}, {141,255,233}, {141,255,233}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {0,0,0}, {88,185,172}, {0,0,0}, {0,0,0}, {0,0,255} },
    [11] = { {0,183,238}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {154,255,255}, {154,255,255}, {0,0,0}, {154,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {0,0,0}, {88,185,172}, {0,0,0}, {0,0,0}, {0,0,0} },
    [12] = { {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188} },
};
// clang-format on

void set_layer_color(int layer)
{
    for (int i = 0; i < DRIVER_LED_TOTAL; i++)
    {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (!hsv.h && !hsv.s && !hsv.v)
        {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
        else
        {
            RGB   rgb = hsv_to_rgb(hsv);
            float f   = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        }
    }
}

void rgb_matrix_indicators_user(void)
{
    if (g_suspend_state || keyboard_config.disable_layer_led)
    {
        return;
    }
    int layer = biton32(layer_state);
    switch (layer)
    {
        case _QWERTY ... _GAMER: set_layer_color(layer); break;
        default:
            if (rgb_matrix_get_flags() == LED_FLAG_NONE)
                rgb_matrix_set_color_all(0, 0, 0);
            break;
    }
}

#ifdef ENABLE_ONESHOT

bool is_oneshot_modifier_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case LA_FNC:
        case LA_NAV:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_modifier_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_NAV:
        case LA_FNC:
        case KC_LSFT:
        case KC_SMART_NUMBER:
            return true;
    }
    return false;
}

oneshot_mod get_modifier_for_trigger_key(uint16_t keycode) {
    switch (keycode) {
        case OS_SHFT:
            return ONESHOT_LSFT;
        case OS_CTRL:
            return ONESHOT_LCTL;
        case OS_ALT:
            return ONESHOT_LALT;
        case OS_CMD:
            return ONESHOT_LGUI;
    }
    return ONESHOT_NONE;
}

#endif

bool smart_feature_cancel_key(uint16_t keycode, keyrecord_t* recor) {
    switch (keycode) {
        case LA_SYM:
        case LA_NAV:
            return true;
    }
    return false;
}


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case KC_PASSWORD:
            if (record->event.pressed) {
                SEND_STRING("SP00NS_and_");
            }
            break;
        case KC_SMART_NUMBER:
            if (record->event.pressed) {
                smart_feature_toggle(SMART_NUMBERS, _NUM);
            }
            break;
        case KC_SMART_CAPSLOCK:
            if (record->event.pressed) {
                uint8_t layer = _QWERTY_CAPS;
                if ((default_layer_state & (1 << _RSTHD)) != 0) layer = _RSTHD_CAPS;
                smart_feature_toggle(SMART_CAPSLOCK, layer);
            }
            break;
    }

    // Some features below need to know if the keycode was consumed. For example: If NAV was used
    // to cancel a MOD then HTC should return to its initial state.
    // Also if NAV was used as a cancel key for a smart feature then it should not cancel anything
    // in 'update_oneshot_modifiers'.

    int8_t keycode_consumed = 0;

    if ((smart_feature_cancel_key(keycode, record)) || (keycode < QK_MODS_MAX && !IS_MOD(keycode))) {
        if (smart_feature_state(SMART_CAPSLOCK)) {
            keycode_consumed = 1;
            smart_capslock_process(keycode, record);
        }
        if (smart_feature_state(SMART_NUMBERS)) {
            keycode_consumed = 1;
            smart_numbers_process(keycode, record);
        }
    }

#ifdef ENABLE_ONESHOT
    keycode_consumed += update_oneshot_modifiers(keycode, record, keycode_consumed);
#endif

    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            break;
        case KC_RSTHD:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_RSTHD);
            }
            break;
#ifdef UNICODE_ENABLE
        case UC_SHRG:  // ¯\_(ツ)_/¯
            if (record->event.pressed) {
                send_unicode_string("¯\\_(ツ)_/¯");
            }
            break;
        case UC_DISA:  // ಠ_ಠ
            if (record->event.pressed) {
                send_unicode_string("ಠ_ಠ");
            }
            break;
        case UC_LVIT:  // ♥‿♥
            if (record->event.pressed) {
                send_unicode_string("♥‿♥");
            }
            break;
#endif
    }

    return true;
}

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
        "KC_SCOLON": "  ;  ",
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
