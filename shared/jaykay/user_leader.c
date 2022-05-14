#include QMK_KEYBOARD_H
#include <version.h>
#include "config.h"
#include "leader.h"
#include "cukey.h"
#include "layers.h"
#include "user_keycodes.h"

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
    LA_COPY,  // j
    LA_CUT,   // h
    LA_PASTE, // k
    // LA_INDENT,   // .
    // LA_UNINDENT, // ,
};

static const leader1_t leader1_array[] = {
    [LA_COPY]  = {TC_J},
    [LA_CUT]   = {TC_H},
    [LA_PASTE] = {TC_K},
    // [LA_INDENT]   = {KC_DOT},
    // [LA_UNINDENT] = {KC_COMMA},
};

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
    LA_DELETE_LINE,      // dd
    LA_DELETE_UNTIL_EOL, // de
    LA_DELETE_WORD,      // dw
    LA_DELETE_UNTIL_SOL, // ds
    LA_CPP_ELSE,         // ee
    LA_CPP_ENUM,         // em
    LA_CPP_EXTERN,       // en
    LA_EQ,               // eq
    LA_EASYMOTION,       // ff
    LA_CPP_FRIEND,       // fi
    LA_CPP_FOR,          // fo
    LA_CPP_GOTO,         // go
    LA_GT,               // gt
    LA_CPP_INLINE,       // ie
    LA_CPP_IF,           // if
    LA_INFO,             // in
    LA_LT,               // lt
    LA_GMAIL,            // mg
    LA_HOTMAIL,          // mh
    LA_OPEN_LINE_ABOVE,  // oa
    LA_OPEN_LINE_BELOW,  // oo
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
    LA_WINDOW_NEXT,      // wn
    LA_WINDOW_PREV,      // wp
};

static const leader2_t leader2_array[] = {
    [LA_CPP_AUTO]         = {TC_A, TC_O},
    [LA_CPP_BREAK]        = {TC_B, TC_K},
    [LA_CPP_CASE]         = {TC_C, TC_E},
    [LA_CHANGE_LINE]      = {TC_C, TC_L},
    [LA_CPP_CONTINUE]     = {TC_C, TC_O},
    [LA_CPP_CLASS]        = {TC_C, TC_S},
    [LA_CPP_CONST]        = {TC_C, TC_T},
    [LA_CHANGE_WORD]      = {TC_C, TC_W},
    [LA_DELETE_WORD_BACK] = {TC_D, TC_B},
    [LA_DELETE_LINE]      = {TC_D, TC_D},
    [LA_DELETE_UNTIL_EOL] = {TC_D, TC_E},
    [LA_DELETE_WORD]      = {TC_D, TC_W},
    [LA_DELETE_UNTIL_SOL] = {TC_D, TC_S},
    [LA_CPP_ELSE]         = {TC_E, TC_E},
    [LA_CPP_ENUM]         = {TC_E, TC_M},
    [LA_CPP_EXTERN]       = {TC_E, TC_N},
    [LA_EQ]               = {TC_E, TC_Q},
    [LA_EASYMOTION]       = {TC_F, TC_F},
    [LA_CPP_FRIEND]       = {TC_F, TC_I},
    [LA_CPP_FOR]          = {TC_F, TC_O},
    [LA_CPP_GOTO]         = {TC_G, TC_O},
    [LA_GT]               = {TC_G, TC_T},
    [LA_CPP_INLINE]       = {TC_I, TC_E},
    [LA_CPP_IF]           = {TC_I, TC_F},
    [LA_INFO]             = {TC_I, TC_N},
    [LA_LT]               = {TC_L, TC_T},
    [LA_GMAIL]            = {TC_M, TC_G},
    [LA_HOTMAIL]          = {TC_M, TC_H},
    [LA_OPEN_LINE_ABOVE]  = {TC_O, TC_A},
    [LA_OPEN_LINE_BELOW]  = {TC_O, TC_O},
    [LA_CPP_OPERATOR]     = {TC_O, TC_R},
    [LA_CPP_PUBLIC]       = {TC_P, TC_C},
    [LA_CPP_PROTECTED]    = {TC_P, TC_D},
    [LA_CPP_PRIVATE]      = {TC_P, TC_E},
    [LA_PASSWORD]         = {TC_P, TC_W},
    [LA_CPP_RETURN]       = {TC_R, TC_N},
    [LA_CPP_REGISTER]     = {TC_R, TC_R},
    [LA_CPP_STATIC]       = {TC_S, TC_C},
    [LA_CPP_SIZEOF]       = {TC_S, TC_F},
    [LA_CPP_SWITCH]       = {TC_S, TC_H},
    [LA_CPP_STRUCT]       = {TC_S, TC_T},
    [LA_CPP_TEMPLATE]     = {TC_T, TC_E},
    [LA_CPP_THIS]         = {TC_T, TC_S},
    [LA_CPP_TYPEDEF]      = {TC_T, TC_Y},
    [LA_CPP_UNION]        = {TC_U, TC_N},
    [LA_CPP_VOID]         = {TC_V, TC_D},
    [LA_CPP_VOLATILE]     = {TC_V, TC_E},
    [LA_CPP_VIRTUAL]      = {TC_V, TC_L},
    [LA_CPP_WHILE]        = {TC_W, TC_E},
    [LA_WINDOW_NEXT]      = {TC_W, TC_N},
    [LA_WINDOW_PREV]      = {TC_W, TC_P},
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

static const leader3_t leader3_array[] = {
    [LA_CHANGE_INSIDE_ABK]   = {TC_C, TC_I, TC_A},
    [LA_CHANGE_INSIDE_BRC]   = {TC_C, TC_I, TC_B},
    [LA_CHANGE_INSIDE_CBR]   = {TC_C, TC_I, TC_C},
    [LA_CHANGE_INSIDE_DQUOT] = {TC_C, TC_I, TC_D},
    [LA_CHANGE_INSIDE_PRN]   = {TC_C, TC_I, TC_P},
    [LA_CHANGE_INSIDE_QUOT]  = {TC_C, TC_I, TC_Q},
    [LA_CHANGE_INSIDE_TICKS] = {TC_C, TC_I, TC_T},
    [LA_CHANGE_INSIDE_WORD]  = {TC_C, TC_I, TC_W},
    [LA_GTE]                 = {TC_G, TC_T, TC_E},
    [LA_KEYBOARD_MAC]        = {TC_K, TC_B, TC_M},
    [LA_KEYBOARD_UBUNTU]     = {TC_K, TC_B, TC_U},
    [LA_KEYBOARD_WIN]        = {TC_K, TC_B, TC_W},
    [LA_LTE]                 = {TC_L, TC_T, TC_E},
    [LA_NEQ]                 = {TC_N, TC_E, TC_Q},
};

enum eleader_four
{
    LA_SCREENSHOT, // snip
};

static leader4_t const leader4_array[] = {
    [LA_SCREENSHOT] = {TC_S, TC_N, TC_I, TC_P},
};

#define send_taps1(tap1) tap_code16(tap1)
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

void execute_leader_action(uint8_t action, uint8_t mode, uint8_t count, uint8_t* keycodes)
{
    if (count == 1)
    {
        uint16_t keycode = KC_NO;
        switch (action)
        {
            case LA_COPY: keycode = process_cukey(CC_COPY); break;
            case LA_CUT: keycode = process_cukey(CC_CUT); break;
            case LA_PASTE:
                keycode = process_cukey(CC_PASTE);
                break;
                // case LA_INDENT: keycode = (KC_TAB); break;
                // case LA_UNINDENT: keycode = S(KC_TAB); break;
        }
        send_taps1(keycode);
    }
    else if (count == 2)
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
            case LA_DELETE_WORD:
                // Visual Studio Code has an extension that does it better (cut/copy word, GUI+X/GUI+C)
                send_taps2(A(S(KC_RIGHT)), KC_DEL);
                break;
            case LA_DELETE_WORD_BACK: send_taps2(A(S(KC_LEFT)), KC_DEL); break;
            case LA_CHANGE_LINE: send_taps3(KC_END, S(KC_HOME), KC_DEL); break;
            case LA_DELETE_LINE: send_taps1(C(S(KC_D))); break;
            case LA_DELETE_UNTIL_SOL: send_taps2(S(KC_HOME), KC_DEL); break;
            case LA_DELETE_UNTIL_EOL: send_taps2(S(KC_END), KC_DEL); break;
            case LA_EASYMOTION: send_taps1(A(KC_S)); break;

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
            case LA_OPEN_LINE_ABOVE: send_taps3(KC_HOME, KC_ENTER, KC_UP); break;
            case LA_OPEN_LINE_BELOW: send_taps2(KC_END, KC_ENTER); break;
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
            case LA_WINDOW_NEXT: send_taps1(G(KC_GRV)); break;
            case LA_WINDOW_PREV: send_taps1(G(S(KC_GRV))); break;
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
            send_taps1(KC_DEL);
        }
    }
    else if (count == 4)
    {
        switch (action)
        {
            case LA_SCREENSHOT: send_taps1(G(S(KC_4))); break;
        }
    }
}
