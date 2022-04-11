#include QMK_KEYBOARD_H
#include <version.h>
#include "leader.h"
#include "cukey.h"

#if !defined(NO_SECRETS)
#include "secrets.x"
#else
#define SECRET_5 "test"
#endif

// Thoughts:
// Use a timer to deal with branching chains, e.g:
// - eg, egt
// For these you need to hold the 'g' key and press the 't' key to get to 'gte'


enum eleader_one
{
    LA_DUMMY_ONE,
};

static leader1_t const leader1_array[] = {};

enum eleader_two
{
    LA_CPP_AUTO,         // ao
    LA_CPP_BREAK,        // bk
    LA_CPP_CASE,         // ce
    LA_CHANGE_LINE,      // cl
    LA_CPP_CONTINUE,     // co
    LA_CPP_CLASS,        // cs
    LA_CPP_CONST,        // ct
    LA_CHANGE_WORD,      // cw
    LA_DELETE_WORD_BACK, // db
    LA_DELETE_UNTIL_EOL, // de
    LA_DELETE_LINE,      // dl
    LA_DELETE_WORD,      // dw
    LA_DELETE_UNTIL_SOL, // ds
    LA_CPP_ELSE,         // ee
    LA_CPP_ENUM,         // em
    LA_CPP_EXTERN,       // en
    LA_EQ,               // eq
    LA_EASYMOTION,       // ff
    LA_CPP_FRIEND,       // fi
    LA_CPP_FOR,          // fo
    LA_GMAIL,            // gm
    LA_CPP_GOTO,         // go
    LA_GT,               // gt
    LA_HOTMAIL,          // hm
    LA_CPP_INLINE,       // ie
    LA_CPP_IF,           // if
    LA_INFO,             // in
    LA_LT,               // lt
    LA_CPP_OPERATOR,     // or
    LA_CPP_PUBLIC,       // pc
    LA_CPP_PROTECTED,    // pd
    LA_CPP_PRIVATE,      // pe
    LA_PASSWORD,         // pw
    LA_CPP_RETURN,       // rn
    LA_CPP_REGISTER,     // rr
    LA_CPP_STATIC,       // sc
    LA_CPP_SIZEOF,       // sf
    LA_CPP_SWITCH,       // sh
    LA_CPP_STRUCT,       // st
    LA_CPP_TEMPLATE,     // te
    LA_CPP_THIS,         // ts
    LA_CPP_TYPEDEF,      // ty
    LA_CPP_UNION,        // un
    LA_CPP_VOID,         // vd
    LA_CPP_VOLATILE,     // ve
    LA_CPP_VIRTUAL,      // vl
    LA_CPP_WHILE,        // we
};

static leader2_t const leader2_array[] = {
    [LA_CPP_AUTO] = {KC_A, KC_O},
      [LA_CPP_BREAK] = {KC_B, KC_K},
      [LA_CPP_CASE] = {KC_C, KC_E},
      [LA_CHANGE_LINE] = {KC_C, KC_L},
      [LA_CPP_CONTINUE] = {KC_C, KC_O},
    [LA_CPP_CLASS] = {KC_C, KC_S},
      [LA_CPP_CONST] = {KC_C, KC_T},
      [LA_CHANGE_WORD] = {KC_C, KC_W},
      [LA_DELETE_WORD_BACK] = {KC_D, KC_B},
      [LA_DELETE_UNTIL_EOL] = {KC_D, KC_E},
    [LA_DELETE_LINE] = {KC_D, KC_L},
      [LA_DELETE_WORD] = {KC_D, KC_W},
      [LA_DELETE_UNTIL_SOL] = {KC_D, KC_S},
      [LA_CPP_ELSE] = {KC_E, KC_E},
      [LA_CPP_ENUM] = {KC_E, KC_M},
      [LA_CPP_EXTERN] = {KC_E, KC_N},
    [LA_EQ] = {KC_E, KC_Q},
      [LA_EASYMOTION] = {KC_F, KC_F},
      [LA_CPP_FRIEND] = {KC_F, KC_I},
      [LA_CPP_FOR] = {KC_F, KC_O},
      [LA_GMAIL] = {KC_G, KC_M},
    [LA_CPP_GOTO] = {KC_G, KC_O},
      [LA_GT] = {KC_G, KC_T},
      [LA_HOTMAIL] = {KC_H, KC_M},
      [LA_CPP_INLINE] = {KC_I, KC_E},
      [LA_CPP_IF] = {KC_I, KC_F},
    [LA_INFO] = {KC_I, KC_N},
      [LA_LT] = {KC_L, KC_T},
      [LA_CPP_OPERATOR] = {KC_O, KC_R},
      [LA_CPP_PUBLIC] = {KC_P, KC_C},
      [LA_CPP_PROTECTED] = {KC_P, KC_D},
    [LA_CPP_PRIVATE] = {KC_P, KC_E},
      [LA_PASSWORD] = {KC_P, KC_W},
      [LA_CPP_RETURN] = {KC_R, KC_N},
      [LA_CPP_REGISTER] = {KC_R, KC_R},
      [LA_CPP_STATIC] = {KC_S, KC_C},
    [LA_CPP_SIZEOF] = {KC_S, KC_F},
      [LA_CPP_SWITCH] = {KC_S, KC_H},
      [LA_CPP_STRUCT] = {KC_S, KC_T},
      [LA_CPP_TEMPLATE] = {KC_T, KC_E},
      [LA_CPP_THIS] = {KC_T, KC_S},
    [LA_CPP_TYPEDEF] = {KC_T, KC_Y},
      [LA_CPP_UNION] = {KC_U, KC_N},
      [LA_CPP_VOID] = {KC_V, KC_D},
      [LA_CPP_VOLATILE] = {KC_V, KC_E},
      [LA_CPP_VIRTUAL] = {KC_V, KC_L},
    [LA_CPP_WHILE] = {KC_W, KC_E},
};

enum eleader_three
{
    LA_CHANGE_INSIDE_ABK = 0,
    LA_CHANGE_INSIDE_BRC,
    LA_CHANGE_INSIDE_CBR,
    LA_CHANGE_INSIDE_DQUOT,
    LA_CHANGE_INSIDE_PRN,
    LA_CHANGE_INSIDE_QUOT,
    LA_CHANGE_INSIDE_TICKS,
    LA_CHANGE_INSIDE_WORD,
    LA_GTE,
    LA_LTE,
    LA_NEQ,
    LA_KEYBOARD_MAC,
    LA_KEYBOARD_UBUNTU,
    LA_KEYBOARD_WIN,
};

static leader3_t const leader3_array[] = {
    [LA_CHANGE_INSIDE_ABK]   = {KC_C, KC_I, KC_A},
    [LA_CHANGE_INSIDE_BRC]   = {KC_C, KC_I, KC_B},
    [LA_CHANGE_INSIDE_CBR]   = {KC_C, KC_I, KC_C},
    [LA_CHANGE_INSIDE_DQUOT] = {KC_C, KC_I, KC_D},
    [LA_CHANGE_INSIDE_PRN]   = {KC_C, KC_I, KC_P},
    [LA_CHANGE_INSIDE_QUOT]  = {KC_C, KC_I, KC_Q},
    [LA_CHANGE_INSIDE_TICKS] = {KC_C, KC_I, KC_T},
    [LA_CHANGE_INSIDE_WORD]  = {KC_C, KC_I, KC_W},
    [LA_GTE]                 = {KC_G, KC_T, KC_E},
    [LA_KEYBOARD_MAC]        = {KC_K, KC_B, KC_M},
    [LA_KEYBOARD_UBUNTU]     = {KC_K, KC_B, KC_U},
    [LA_KEYBOARD_WIN]        = {KC_K, KC_B, KC_W},
    [LA_LTE]                 = {KC_L, KC_T, KC_E},
    [LA_NEQ]                 = {KC_N, KC_E, KC_Q},
};

enum eleader_four
{
    LA_SCREENSHOT, // snip
};

static leader4_t const leader4_array[] = {
    [LA_SCREENSHOT] = {KC_S, KC_N, KC_I, KC_P},
};

#define send_taps2(tap1, tap2) \
    tap_code16(tap1);          \
    tap_code16(tap2)
#define send_taps3(tap1, tap2, tap3) \
    tap_code16(tap1);                \
    tap_code16(tap2);                \
    tap_code16(tap3)

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

static leader_config_t leader_config = {
    .leader1_array = leader1_array,
    .leader1_count = ARRAY_SIZE(leader1_array),
    .leader2_array = leader2_array,
    .leader2_count = ARRAY_SIZE(leader2_array),
    .leader3_array = leader3_array,
    .leader3_count = ARRAY_SIZE(leader3_array),
    .leader4_array = leader4_array,
    .leader4_count = ARRAY_SIZE(leader4_array),
};

bool process_leader_user(uint16_t keycode, keyrecord_t* record) { return process_record_leader(keycode, record, &leader_config); }

void execute_leader_action(uint8_t action, uint8_t mode, uint8_t count, uint16_t* keycodes)
{
    if (count == 2)
    {
        const char* str = NULL;
        switch (action)
        {
            case LA_INFO:
                if (mode == 0)
                {
                    if (keyboard_get_os() == OS_MAC)
                        str = ("kb=" QMK_KEYBOARD ", km=" QMK_KEYMAP ", build= " __DATE__ "/" __TIME__ " (Mac)");
                    else if (keyboard_get_os() == OS_WINDOWS)
                        str = ("kb=" QMK_KEYBOARD ", km=" QMK_KEYMAP ", build= " __DATE__ "/" __TIME__ " (Windows)");
                    else if (keyboard_get_os() == OS_UBUNTU)
                        str = ("kb=" QMK_KEYBOARD ", km=" QMK_KEYMAP ", build= " __DATE__ "/" __TIME__ " (Ubuntu)");
                }
                else if (mode == 1)
                {
                    str = ("QMK=" QMK_VERSION ", build= " QMK_BUILDDATE);
                }
                break;

            case LA_PASSWORD: str = SECRET_5; break;
            case LA_GMAIL: str = ("jurgen.kluft@gmail.com"); break;
            case LA_HOTMAIL: str = ("jurgen_kluft@hotmail.com"); break;
            case LA_GT: str = (" > "); break;
            case LA_LT: str = (" < "); break;
            case LA_EQ: str = (" == "); break;
            case LA_CHANGE_WORD:
            case LA_DELETE_WORD: send_taps2(A(S(KC_RIGHT)), KC_DEL); break;
            case LA_DELETE_WORD_BACK: send_taps2(A(S(KC_LEFT)), KC_DEL); break;
            case LA_CHANGE_LINE: send_taps3(KC_END, S(KC_HOME), KC_DEL); break;
            case LA_DELETE_LINE: send_taps2(C(KC_D), KC_L); break;
            case LA_DELETE_UNTIL_SOL: send_taps2(S(KC_HOME), KC_DEL); break;
            case LA_DELETE_UNTIL_EOL: send_taps2(S(KC_END), KC_DEL); break;
            case LA_EASYMOTION: tap_code16(A(KC_S)); break;

            case LA_CPP_AUTO: str = "auto "; break;
            case LA_CPP_BREAK: str = "break; "; break;
            case LA_CPP_CASE: str = "case "; break;
            case LA_CPP_CLASS: str = "class "; break;
            case LA_CPP_CONST: str = "const "; break;
            case LA_CPP_CONTINUE: str = "continue; "; break;
            case LA_CPP_ELSE: str = "else "; break;
            case LA_CPP_ENUM: str = "enum "; break;
            case LA_CPP_EXTERN: str = "extern "; break;
            case LA_CPP_FOR: str = "for (s32 i=0; i<"; break;
            case LA_CPP_FRIEND: str = "friend "; break;
            case LA_CPP_GOTO: str = "goto "; break;
            case LA_CPP_IF: str = "if () {\n"; break;
            case LA_CPP_INLINE: str = "inline "; break;
            case LA_CPP_OPERATOR: str = "operator "; break;
            case LA_CPP_PRIVATE: str = "private: "; break;
            case LA_CPP_PROTECTED: str = "protected: "; break;
            case LA_CPP_PUBLIC: str = "public: "; break;
            case LA_CPP_REGISTER: str = "register "; break;
            case LA_CPP_RETURN: str = "return "; break;
            case LA_CPP_SIZEOF: str = "sizeof("; break;
            case LA_CPP_STATIC: str = "static "; break;
            case LA_CPP_STRUCT: str = "struct "; break;
            case LA_CPP_SWITCH: str = "switch () {\n case "; break;
            case LA_CPP_TEMPLATE: str = "template "; break;
            case LA_CPP_THIS: str = "this "; break;
            case LA_CPP_TYPEDEF: str = "typedef "; break;
            case LA_CPP_UNION: str = "union "; break;
            case LA_CPP_VIRTUAL: str = "virtual "; break;
            case LA_CPP_VOID: str = "void"; break;
            case LA_CPP_VOLATILE: str = "volatile"; break;
            case LA_CPP_WHILE: str = "while (x) {\n"; break;
        }
        if (str != NULL)
        {
            send_string_with_delay(str, MACRO_TIMER);
        }
    }
    else if (count == 3)
    {
        uint16_t bracket = KC_NO;
        switch (action)
        {
            case LA_GTE: send_string(" >= "); break;
            case LA_LTE: send_string(" <= "); break;
            case LA_NEQ: send_string(" != "); break;
            case LA_CHANGE_INSIDE_WORD: send_taps3(A(KC_LEFT), A(S(KC_RIGHT)), KC_DEL); break;
            case LA_CHANGE_INSIDE_PRN: bracket = KC_LPRN; break;
            case LA_CHANGE_INSIDE_CBR: bracket = KC_LCBR; break;
            case LA_CHANGE_INSIDE_BRC: bracket = KC_LBRC; break;
            case LA_CHANGE_INSIDE_ABK: bracket = KC_LABK; break;
            case LA_CHANGE_INSIDE_QUOT: bracket = KC_QUOT; break;
            case LA_CHANGE_INSIDE_DQUOT: bracket = KC_DQUO; break;
            case LA_CHANGE_INSIDE_TICKS: bracket = KC_GRV; break;
            case LA_KEYBOARD_MAC: keyboard_set_os(OS_MAC); break;
            case LA_KEYBOARD_WIN: keyboard_set_os(OS_WINDOWS); break;
            case LA_KEYBOARD_UBUNTU: keyboard_set_os(OS_UBUNTU); break;
        }
        if (bracket != KC_NO)
        {
            send_taps2(G(KC_K), bracket);
            wait_ms(200);
            tap_code16(KC_DEL);
        }
    }
    else if (count == 4)
    {
        switch (action)
        {
            case LA_SCREENSHOT: tap_code16(G(S(KC_4))); break;
        }
    }
}
