#include QMK_KEYBOARD_H
#include "user_layers.h"
#include "user_keycodes.h"

#define xxx KC_NO

    // [_QWERTY] = LAYOUT_myr(
    //   KC_ESC  , KC_1 ,  KC_2   ,  KC_3  ,   KC_4 ,   KC_5 ,         KC_LSFT,     KC_RSFT,          KC_6 ,  KC_7 ,  KC_8 ,   KC_9 ,  KC_0 , KC_ESC,
    //   KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,         KC_LCTL,     KC_RCTL,          KC_Y ,  KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSPC,
    //   CTL_ESC , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,         KC_LALT,     KC_RALT,          KC_H ,  KC_J ,  KC_K ,   KC_L ,KC_SCLN,CTL_QUOT,
    //   KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_LBRC,KC_CAPS,     FKEYS  , KC_RBRC, KC_N ,  KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
    //                              ADJUST , KC_LGUI, ALT_ENT, KC_SPC , NAV   ,     SYM    , KC_SPC ,KC_RALT, KC_RGUI, KC_APP,

    //   KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP,    KC_MUTE,                            KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP,    KC_MUTE
    // ),


#define LAYOUTXX( \
       L01,      L02,    L03,      L04,      L05 ,    L06  ,                             R06,    R05,    R04,    R03 ,    R02 ,    R01, \
       L11,      L12,    L13,      L14,      L15 ,    L16  ,                             R16,    R15,    R14,    R13 ,    R12 ,    R11, \
       L21,      L22,    L23,      L24,      L25 ,    L26  ,                             R26,    R25,    R24,    R23 ,    R22 ,    R21, \
       L31,      L32,    L33,      L34,      L35 ,    L36  ,   L37 , L38 ,  R38, R37,    R36,    R35,    R34,    R33 ,    R32 ,    R31, \
                                   L41,      L42 ,    L43  ,   L44 , L45 ,  R45, R44,    R43,    R42,    R41                            \
) \
LAYOUT_myr( \
       L01,      L02,    L03,      L04,      L05 ,    L06  ,         xxx,   xxx,          R06,    R05,    R04,    R03 ,    R02 ,    R01, \
       L11,      L12,    L13,      L14,      L15 ,    L16  ,         xxx,   xxx,          R16,    R15,    R14,    R13 ,    R12 ,    R11, \
       L21,      L22,    L23,      L24,      L25 ,    L26  ,         xxx,   xxx,          R26,    R25,    R24,    R23 ,    R22 ,    R21, \
       L31,      L32,    L33,      L34,      L35 ,    L36  ,   L37 , L38,   R38,  R37,    R36,    R35,    R34,    R33 ,    R32 ,    R31, \
                                   L41,      L42 ,    L43  ,   L44 , L45,   R45,  R44,    R43,    R42,    R41,                           \
                                   xxx,      xxx,     xxx,      xxx, xxx,   xxx,  xxx,    xxx,    xxx,    xxx                            \
)

// clang-format off

#define OSL_LN  OSL(LAYER_NUMBERS)
#define OSM_LS  OSM(MOD_LSFT)
#define OSM_XX  OSM(MOD_LGUI|MOD_LALT|MOD_LCTL|MOD_LSFT)


// 
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_QWERTY] = LAYOUTXX(
    KC_ESC,  KC_1, KC_2, KC_3,    KC_4,    KC_5,                         /*|*/                     KC_6,    KC_7,   KC_8,     KC_9,   KC_0,    KC_ESC,
    KC_TAB,  KC_Q, KC_W, KC_E,    KC_R,    KC_T,                         /*|*/                     KC_Y,    KC_U,   KC_I,     KC_O,   KC_P,    KC_BSPC,
    KC_LGUI, KC_A, KC_S, KC_D,    KC_F,    KC_G,                         /*|*/                     KC_H,    KC_J,   KC_K,     KC_L,   KC_SCLN, OSM_LS, 
    KC_LCTL, KC_Z, KC_X, KC_C,    KC_V,    KC_B,    CC_PDT,     CC_PDT,  /*|*/   CC_NDT,  CC_NDT,  KC_N,    KC_M,   KC_COMMA, KC_DOT, KC_SLSH, KC_RCTL,
                         OSL_LN, OSL_LN, CC_FNAV, KC_SPACE, HYPR(KC_Z),  /*|*/   OSM_XX, KC_BSPC,  CC_FSYM, OSM_LS, OSM_LS
    ),
    [LAYER_RSTHD] = LAYOUTXX(
    KC_ESC,  KC_1,    KC_2, KC_3,    KC_4,    KC_5,                        /*|*/                   KC_6,    KC_7,     KC_8,      KC_9,     KC_0,   KC_ESC,
    KC_TAB,  KC_J,    KC_C, KC_Y,    KC_F,    KC_K,                        /*|*/                   KC_Z,    KC_L,     KC_BSPC,   KC_U,     KC_Q,   KC_BSPC,
    KC_LGUI, KC_R,    KC_S, KC_T,    KC_H,    KC_D,                        /*|*/                   KC_M,    KC_N,     KC_A,      KC_I,     KC_O,   OSM_LS, 
    KC_LCTL, OSM_LS,  KC_V, KC_G,    KC_P,    KC_B,    CC_PDT,   CC_PDT,   /*|*/  CC_NDT,  CC_NDT, KC_X,    KC_W,     KC_COMMA,  KC_DOT,   OSL_LN, KC_RCTL,
                            OSL_LN, OSL_LN, CC_FNAV, KC_SPACE, HYPR(KC_Z), /*|*/  OSM_XX,  KC_E,   CC_FSYM, OSM_LS, OSM_LS
    ),
    [LAYER_GRAPHITE] = LAYOUTXX(
    KC_ESC,  KC_1,    KC_2, KC_3,    KC_4,    KC_5,                         /*|*/                   KC_6,    KC_7,     KC_8,      KC_9,     KC_0,   KC_ESC,
    KC_TAB,  KC_B,    KC_L, KC_D,    KC_W,    KC_Z,                         /*|*/                   KC_BSPC, KC_F,     KC_O,      KC_U,     KC_Q,   KC_BSPC,
    KC_CAPS, KC_N,    KC_R, KC_T,    KC_S,    KC_G,                         /*|*/                   KC_Y,    KC_H,     KC_A,      KC_J,     KC_I,   OSM_LS, 
    KC_LCTL, KC_Q,    KC_X, KC_M,    KC_C,    KC_V,    CC_PDT,   CC_PDT,    /*|*/   CC_NDT, CC_NDT, KC_K,    KC_P,     KC_COMMA,  KC_DOT,   OSL_LN, KC_RCTL,
                            OSL_LN, OSL_LN, CC_FNAV, KC_SPACE, HYPR(KC_Z),  /*|*/   KC_BSPC,KC_E,   CC_FSYM, OSM_LS, OSM_LS
    ),
    [LAYER_ENGRAM2] = LAYOUTXX(
    KC_ESC,  KC_1,  KC_2, KC_3,   KC_4,   KC_5,                             /*|*/                   KC_6,    KC_7,     KC_8,      KC_9,     KC_0,   KC_ESC,
    KC_TAB,  KC_B,  KC_Y, KC_O,   KC_U,   KC_QUOT,                          /*|*/                   KC_DQUO, KC_L,     KC_D,      KC_W,     KC_V,   KC_BSPC,
    KC_CAPS, KC_C,  KC_I, KC_E,   KC_A,   KC_COMMA,                         /*|*/                   KC_DOT,  KC_H,     KC_T,      KC_S,     KC_N,   OSM_LS, 
    KC_LCTL, KC_G,  KC_X, KC_J,   KC_K,   KC_Z,    CC_PDT,   CC_PDT,        /*|*/   CC_NDT, CC_NDT, KC_Q,    KC_R,     KC_M,      KC_F,     KC_P,   KC_RCTL,
                          OSL_LN, OSL_LN, CC_FNAV, KC_SPACE, HYPR(KC_Z),    /*|*/   KC_BSPC,  KC_E, CC_FSYM, OSM_LS,   OSM_LS
    ),

// V M L C P           B ^1 U O  Q
// S T R D Y           F  N E A  I
// X K J G W           Z  H , . ^2
//       Nav ⎵      @ Sym

    [LAYER_STURDY] = LAYOUTXX(
    KC_ESC,  KC_1,  KC_2, KC_3,   KC_4,   KC_5,                             /*|*/                   KC_6,    KC_7,     KC_8,      KC_9,   KC_0,     KC_ESC,
    KC_TAB,  KC_V,  KC_M, KC_L,   KC_C,   KC_P,                             /*|*/                   KC_B,    QK_AREP,  KC_U,      KC_O,   KC_Q,     KC_BSPC,
    KC_CAPS, KC_S,  KC_T, KC_R,   KC_D,   KC_Y,                             /*|*/                   KC_F,    KC_N,     KC_E,      KC_A,   KC_I,     OSM_LS, 
    KC_LCTL, KC_X,  KC_K, KC_J,   KC_G,   KC_W,    CC_PDT,   CC_PDT,        /*|*/   CC_NDT, CC_NDT, KC_Z,    KC_H,     KC_COMMA,  KC_DOT, CC_MAG_2, KC_RCTL,
                          OSL_LN, OSL_LN, CC_FNAV, KC_SPACE, CC_MAG_3,      /*|*/   KC_BSPC,QK_REP, CC_FSYM, OSM_LS,   OSM_LS
    ),
    [LAYER_NUMBERS] = LAYOUTXX(
    KC_ESC,   KC_1,    KC_2,     KC_3,    KC_4,     KC_5,                          /*|*/                         KC_6,    KC_7,     KC_8,     KC_9,    KC_0,    KC_ESC,
    KC_TAB,   KC_7,    KC_8,     KC_9,    KC_0,     KC_6,                          /*|*/                         KC_6,    KC_0,     KC_9,     KC_8,    KC_7,    KC_BSPC,
    KC_LGUI,  CC_CMD,  CC_ALT,   CC_CTRL, CC_SHFT,  KC_5,                          /*|*/                         KC_5,    KC_1,     KC_2,     KC_3,    KC_4,    OSM_LS, 
    KC_LCTL,  KC_4,    KC_3,     KC_2,    KC_1,     KC_ASTR, KC_NO,    KC_NO,      /*|*/   KC_NO,    KC_NO,      KC_B,    KC_UNDS,  KC_COMMA, KC_DOT,  OSL_LN,  KC_RCTL,
                                 OSL_LN,  OSL_LN,   CC_FNAV, KC_SPACE, HYPR(KC_Z), /*|*/   OSM_XX, KC_BSPC,   CC_FSYM, OSM_LS, OSM_LS                 
    ),
    [LAYER_SYMBOLS] = LAYOUTXX(
    KC_ESC,  KC_1,    KC_2,     KC_3,    KC_4,      KC_5,                        /*|*/                   KC_6,    KC_7,     KC_8,    KC_9,     KC_0,     KC_ESC,
    KC_TAB,  KC_PERC, KC_AMPR,  KC_PIPE, KC_UNDS,   KC_TILD,                     /*|*/                   KC_GRV,  KC_QUOT,  KC_DQUO, KC_HASH,  KC_DLR,   KC_BSPC,
    KC_LGUI, KC_EXLM, KC_MINUS, KC_PLUS, KC_EQUAL,  KC_LBRC,                     /*|*/                   KC_LABK, KC_LPRN,  KC_LCBR, KC_SCLN,  KC_COLN,  OSM_LS, 
    KC_LCTL, KC_CIRC, KC_SLSH,  KC_ASTR, KC_BSLS,   KC_RBRC, CC_NDOC,  CC_NDOC,  /*|*/ CC_PDOC, CC_PDOC, KC_RABK, KC_RPRN,  KC_RCBR, KC_QUES,  KC_AT,    KC_RCTL,
                                KC_LBRC, KC_LPRN,   CC_FNAV, KC_LCBR,  KC_LBRC,  /*|*/  OSM_XX, KC_BSPC, CC_FSYM, OSM_LS,   OSM_LS
    ),
    [LAYER_NAVIGATION] = LAYOUTXX(
    KC_ESC,  KC_1,    KC_2,     KC_3,      KC_4,     KC_5,                             /*|*/                     KC_6,      KC_7,      KC_8,    KC_9,     KC_0,  KC_ESC,
    KC_TAB,  CC_REDO, CC_CLOSE, KC_ESCAPE, KC_ENTER, KC_TAB,                           /*|*/                     KC_INSERT, CC_PGUP,   KC_HOME, KC_NO,    KC_NO, KC_BSPC,
    KC_LGUI, CC_CMD,  CC_ALT,   CC_CTRL,   CC_SHFT,  KC_DELETE,                        /*|*/                     KC_LEFT,   KC_DOWN,   KC_UP,   KC_RIGHT, KC_NO, OSM_LS, 
    KC_LCTL, CC_UNDO, CC_CUT,   CC_COPY,   CC_PASTE, KC_BSPC,    CC_NAPP,  CC_NAPP,    /*|*/  CC_PAPP, CC_PAPP,  KC_NO,     CC_PGDOWN, KC_END,  KC_NO,    KC_NO, KC_RCTL,
                                OSL_LN,    OSL_LN,   CC_FNAV,    KC_SPACE, HYPR(KC_Z), /*|*/  OSM_XX,  KC_BSPC,  CC_FSYM,   OSM_LS,    OSM_LS                   
    ),
    [LAYER_RAISE] = LAYOUTXX(
    KC_ESC,  CC_QWERTY,   CC_RSTHD,    CC_GRAPHITE, CC_ENGRAM2,  CC_STURDY,                   /*|*/                   KC_6,     KC_7,   KC_8,    KC_9,  KC_0,  KC_ESC,
    KC_TAB,  CC_SECRET_5, CC_SECRET_6, CC_SECRET_7, CC_SECRET_8, KC_NO,                       /*|*/                   KC_F12,   KC_F2,  KC_F3,   KC_F4, KC_F1, KC_BSPC,
    KC_LGUI, CC_CMD,      CC_ALT,      CC_CTRL,     CC_SHFT,     KC_NO,                       /*|*/                   KC_F5,    KC_F11, KC_F10,  KC_F9, KC_NO, OSM_LS, 
    KC_LCTL, CC_SECRET_1, CC_SECRET_2, CC_SECRET_3, CC_SECRET_4, KC_NO,   CC_PDT,   CC_PDT,   /*|*/  CC_NDT, CC_NDT,  KC_NO,    KC_F6,  KC_F7,   KC_F8, KC_NO, KC_RCTL,
                                       OSL_LN,     OSL_LN,     CC_FNAV, KC_SPACE, HYPR(KC_Z), /*|*/  OSM_XX, KC_BSPC, CC_FSYM,  OSM_LS, OSM_LS                
    ),
    [LAYER_MOUSE] = LAYOUTXX(
    KC_ESC,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,                                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_ESC,
    KC_TAB,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                             KC_WH_U, KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_BSPC,
    KC_LGUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                             KC_WH_D, KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN6,  OSM_LS, 
    KC_LCTL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_BTN7, KC_BTN4, KC_BTN5, KC_BTN8, KC_NO,    KC_RCTL,
                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO
    )    
};
// clang-format on

#ifdef OLED_ENABLE
bool oled_task_user(void) { return true; }
#endif
