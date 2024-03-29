#pragma once

#define xxxx KC_NO

enum euser_keycodes
{
    KL_00,
    KL_01,
    KL_02,
    KL_03,
    KL_04,
    KL_05,
    KL_06,
    KL_07,
    KL_08,
    KL_09,
    KL_10,
    KL_11,
    KL_12,
    KL_13,
    KL_14,
    KL_15,
    KL_16,
    KL_17,
    KL_18,
    KL_19,
    KL_20,
    KL_21,
    KL_22,
    KL_23,
    KL_24,
    KL_25,
    KL_26,
    KL_27,
    KL_28,
    KL_29,
    KL_30,
    KL_31,
    KL_32,
    KL_33,
    KL_34,
    KL_35,
    KL_36,
    KL_37,
    KL_38,
    KL_39,
    KL_40,
    KL_41,
    KL_42,
    KL_43,
    KL_44,
    KL_45,
    KL_46,
    KL_47,
    KL_48,
    KL_49,
    KL_50,
    KL_51,
    KL_52,
    KL_53,
    KL_54,
    KL_55,
    KL_56,
    KL_57,
    KL_58,
    KL_59,
    KL_60,
    KL_61,
    KL_62,
    KL_63,
    KL_64,
    KL_65,
    KL_66,
    KL_67,
    KL_68,
    KL_69,
    KL_70,
    KL_71,
    KL_72,
    KL_73,
    KL_74,
    KL_75,
    KL_76,
    KL_77,
    KL_78,
    KL_79,
};

// clang-format off
enum ebasekeycodes {
    TC_NO = 0,
    TC_0,TC_1,TC_2,TC_3,TC_4,TC_5,TC_6,TC_7,TC_8,TC_9,
    TC_A,TC_B,TC_C,TC_D,TC_E,TC_F,TC_G,TC_H,TC_I,TC_J,TC_K,TC_L,TC_M,
    TC_N,TC_O,TC_P,TC_Q,TC_R,TC_S,TC_T,TC_U,TC_V,TC_W,TC_X,TC_Y,TC_Z,
    TC_F1,TC_F2,TC_F3,TC_F4,TC_F5,TC_F6,TC_F7,TC_F8,TC_F9,TC_F10,TC_F11,TC_F12,
    TC_UP,TC_DOWN,TC_LEFT,TC_RIGHT,
    TC_AT,
    TC_PERC,
    TC_DLR,
    TC_TILD,
    TC_CIRC,
    TC_HASH,
    TC_UNDS,
    TC_DOT,TC_COMMA,
    TC_COLN,TC_SCLN,
    TC_DQUO,TC_QUOT,TC_GRV,
    TC_EXLM,TC_QUES,
    TC_HOME,TC_END,
    TC_LABK,TC_RABK,
    TC_LBRC,TC_RBRC,
    TC_LCBR,TC_RCBR,
    TC_LPRN,TC_RPRN,
    TC_PIPE,TC_AMPR,
    TC_EQUAL,TC_PLUS,TC_MINUS,TC_ASTR,
    TC_SLASH,TC_BSLASH,
    TC_SPACE,
    TC_BSPACE,
    TC_ENTER,
    TC_TAB,
    TC_DELETE,
    TC_ESCAPE,
    TC_INSERT,
    TC_PGUP,TC_PGDOWN,
    TC_LSHIFT,TC_RSHIFT,TC_LCTRL,TC_RCTRL,TC_LALT,TC_RALT,
    TC_RANGE_START = TC_0,
    TC_RANGE_END = TC_RALT,
    TC_RANGE_COUNT = TC_RANGE_END+1,
    TC_SAFE_RANGE_START,
};
// clang-format on

enum ecustomkeycodes
{
    CC_RANGE_START = TC_SAFE_RANGE_START,
    CC_FNUM        = CC_RANGE_START,
    CC_FCAPS,
    CC_FNAV,
    CC_FSYM,
    CC_FCNT,

    // oneshot
    CC_CTRL,
    CC_SHFT,
    CC_ALT,
    CC_CMD,
    // cukey-start
    CC_UNDO,
    CC_REDO,
    CC_CUT,
    CC_COPY,
    CC_PASTE,
    CC_NDT,
    CC_PDT,
    CC_NAPP,
    CC_PAPP,
    CC_NDOC,
    CC_PDOC,
    CC_CLOSE,
    // cukey-end

    CC_PGUP,
    CC_PGDOWN,

    // secrets
    CC_SECRET_1,
    CC_SECRET_2,
    CC_SECRET_3,
    CC_SECRET_4,
    CC_SECRET_5,
    CC_SECRET_6,
    CC_SECRET_7,
    CC_SECRET_8,
    // space+shift
    CC_SPIFT,
    // layout
    CC_QWERTY,
    CC_RSTHD,

    CC_GAMEL,
    CC_GAMER,

    // Vim keycodes
    CC_VIM_DOCU,
    CC_VIM_PAGE,
    CC_VIM_LINE,
    CC_VIM_WORD,
    CC_VIM_CHAR,
    CC_VIM_DELI,
    CC_VIM_INSIDE,
    CC_VIM_SEARCH,
    CC_VIM_FIND,
    CC_VIM_ZOOM,
    CC_VIM_BEGIN,
    CC_VIM_END,
    CC_VIM_VISUAL,
    CC_VIM_ESCAPE,
    CC_VIM_CLEAR,
    CC_VIM_RAISE,
    CC_VIM_ADD,
    CC_VIM_INSERT,
    CC_VIM_CHANGE,
    CC_VIM_DELETE,
    CC_VIM_GOTO,
    CC_VIM_CUT,
    CC_VIM_YANK,
    CC_VIM_REDO,
    CC_VIM_REPEAT,
    CC_VIM_UNDO,
    CC_VIM_UNTIL,
    CC_VIM_DOWN,
    CC_VIM_LEFT,
    CC_VIM_RIGHT,
    CC_VIM_UP,
    CC_VIM_INDENT,
    CC_VIM_UNINDENT,

    CC_RANGE_END       = CC_VIM_UNINDENT,
    CC_RANGE_VIM_START = CC_VIM_DOCU,
    CC_RANGE_VIM_END   = CC_VIM_UNINDENT,
};

uint16_t user_get_code16(uint16_t keycode);
