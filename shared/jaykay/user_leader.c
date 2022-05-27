#include QMK_KEYBOARD_H
#include <version.h>
#include "config.h"
#include "leader.h"
#include "feature.h"
#include "cukey.h"
#include "oneshot.h"
#include "user_layers.h"
#include "user_keycodes.h"

/*

a = and
b = back
c = cross
d = down
e = east
f = -> easymotion
g = go
h = horizontal
i = inside
j = jump
k = know
l = left
m = move
n = north
o = origin
p = position
q = question
r = right
s = south
t = the
u = up
v = vertical
w = west
x = axis
y = you
z = -> center


*/

enum eleader_1t1
{
    LA_EASYMOTION,    // f
    LA_CENTER,        // z
    LA_DOTSPACESHIFT, // . (shift)
};

static const leader1_t leader1t1_array[] = {
    [LA_EASYMOTION]    = {TC_F},
    [LA_CENTER]        = {TC_Z},
    [LA_DOTSPACESHIFT] = {TC_DOT},
};

enum eleader_1t2
{
    LA_AND,             // a, ' && '
    LA_EQ,              // e, ' == ' 
    LA_GAE,             // g, ' >= '
    LA_LAE,             // l, ' <= '
    LA_NEQ,             // n, ' != '
    LA_OR,              // o, ' || '
    LA_UNREAL_ENGINE,   // u
};

// clang-format off
static const leader1_t leader1t2_array[] = {
    [LA_AND]                 = { TC_A },
    [LA_EQ]                  = { TC_E },
    [LA_GAE]                 = { TC_G },
    [LA_LAE]                 = { TC_L },
    [LA_NEQ]                 = { TC_N },
    [LA_OR]                  = { TC_O },
    [LA_UNREAL_ENGINE]       = { TC_U },
};
// clang-format on

enum eleader_1t3
{
    LA_BUILD0,
    LA_BUILD1,
    LA_KEYBOARD_MAC,
    LA_KEYBOARD_UBUNTU,
    LA_KEYBOARD_WIN,
};

// clang-format off
static const leader1_t leader1t3_array[] = {
    [LA_BUILD0]              = { TC_B },
    [LA_BUILD1]              = { TC_D },
    [LA_KEYBOARD_MAC]        = { TC_M },
    [LA_KEYBOARD_UBUNTU]     = { TC_U },
    [LA_KEYBOARD_WIN]        = { TC_W },
};
// clang-format on

enum eleader_2t1
{
    LA_CAMEL_CASE,       // cc
    LA_CHANGE_LINE,      // cl
    LA_CHANGE_WORD,      // cw
    LA_DELETE_WORD_BACK, // db
    LA_DELETE_LINE,      // dd
    LA_DELETE_UNTIL_EOL, // de
    LA_DELETE_WORD,      // dw
    LA_DELETE_UNTIL_SOL, // ds
    LA_TOP_OF_FILE,      // gg
    LA_BOTTOM_OF_FILE,   // gb
    LA_NUM,              // nn
    LA_OPEN_LINE_ABOVE,  // oa
    LA_OPEN_LINE_BELOW,  // oo
};

// clang-format off
static const leader2_t leader2t1_array[] = {
    [LA_CAMEL_CASE]       = {TC_C, TC_C},
    [LA_CHANGE_LINE]      = {TC_C, TC_L},
    [LA_CHANGE_WORD]      = {TC_C, TC_W},
    [LA_DELETE_WORD_BACK] = {TC_D, TC_B},
    [LA_DELETE_LINE]      = {TC_D, TC_D},
    [LA_DELETE_UNTIL_EOL] = {TC_D, TC_E},
    [LA_DELETE_WORD]      = {TC_D, TC_W},
    [LA_DELETE_UNTIL_SOL] = {TC_D, TC_S},
    [LA_TOP_OF_FILE]      = {TC_G, TC_G},
    [LA_BOTTOM_OF_FILE]   = {TC_G, TC_B},
    [LA_NUM]              = {TC_N, TC_N},
    [LA_OPEN_LINE_ABOVE]  = {TC_O, TC_A},
    [LA_OPEN_LINE_BELOW]  = {TC_O, TC_O},
};
// clang-format on

enum eleader_3t1
{
    LA_CHANGE_INSIDE_ABK = 0, // cia
    LA_CHANGE_INSIDE_BRC,     // cib
    LA_CHANGE_INSIDE_CBR,     // cic
    LA_CHANGE_INSIDE_DQUOT,   // cid
    LA_CHANGE_INSIDE_PRN,     // cip
    LA_CHANGE_INSIDE_QUOT,    // ciq
    LA_CHANGE_INSIDE_TICKS,   // cit
    LA_CHANGE_INSIDE_WORD,    // ciw
};

// clang-format off
static const leader3_t leader3t1_array[] = {
    [LA_CHANGE_INSIDE_ABK]   = {TC_C, TC_I, TC_A},
    [LA_CHANGE_INSIDE_BRC]   = {TC_C, TC_I, TC_B},
    [LA_CHANGE_INSIDE_CBR]   = {TC_C, TC_I, TC_C},
    [LA_CHANGE_INSIDE_DQUOT] = {TC_C, TC_I, TC_D},
    [LA_CHANGE_INSIDE_PRN]   = {TC_C, TC_I, TC_P},
    [LA_CHANGE_INSIDE_QUOT]  = {TC_C, TC_I, TC_Q},
    [LA_CHANGE_INSIDE_TICKS] = {TC_C, TC_I, TC_T},
    [LA_CHANGE_INSIDE_WORD]  = {TC_C, TC_I, TC_W},
};
// clang-format on

enum eleader_4t1
{
    LA_SCREENSHOT, // snip
};

static leader4_t const leader4t1_array[] = {
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

static leader_config_t leader_config_t1 = {
    .leader1_array = leader1t1_array,
    .leader1_count = ARRAY_SIZE(leader1t1_array),
    .leader2_array = leader2t1_array,
    .leader2_count = ARRAY_SIZE(leader2t1_array),
    .leader3_array = leader3t1_array,
    .leader3_count = ARRAY_SIZE(leader3t1_array),
    .leader4_array = leader4t1_array,
    .leader4_count = ARRAY_SIZE(leader4t1_array),
};

static leader_config_t leader_config_t2 = {
    .leader1_array = leader1t2_array,
    .leader1_count = ARRAY_SIZE(leader1t2_array),
    .leader2_array = NULL,
    .leader2_count = 0,
    .leader3_array = NULL,
    .leader3_count = 0,
    .leader4_array = NULL,
    .leader4_count = 0,  
};

static leader_config_t leader_config_t3 = {
    .leader1_array = leader1t3_array,
    .leader1_count = ARRAY_SIZE(leader1t3_array),
    .leader2_array = NULL,
    .leader2_count = 0,
    .leader3_array = NULL,
    .leader3_count = 0,
    .leader4_array = NULL,
    .leader4_count = 0,  
};

bool process_leader_user(uint16_t keycode, keyrecord_t* record) { return process_record_leader(keycode, record, &leader_config_t1, &leader_config_t2, &leader_config_t3); }

void execute_leader_action(uint8_t action, uint8_t mode, uint8_t count, uint8_t* keycodes)
{
    if (count == 1)
    {
        if (mode == 0)
        {
            switch (action)
            {
                case LA_DOTSPACESHIFT: send_taps1(KC_DOT); break;
                case LA_CENTER: send_taps1(A(KC_M)); break;
                case LA_EASYMOTION: send_taps1(A(KC_S)); break;
            }
            switch (action)
            {
                case LA_DOTSPACESHIFT:
                    send_taps1(KC_SPACE);
                    tap_oneshot_modifier(ONESHOT_LSFT);
                    break;
            }
        }
        else if (mode == 1)
        {
            const char* str = NULL;
            switch (action)
            {
                case LA_AND: str = " && "; break;
                case LA_EQ: str = " == "; break;
                case LA_GAE: str = " >= "; break;
                case LA_LAE: str = " <= "; break;
                case LA_NEQ: str = " != "; break;
                case LA_OR: str = " || "; break;
                case LA_UNREAL_ENGINE: str = "Unreal Engine "; break;
            }
            if (str != NULL)
            {
                send_string_with_delay(str, MACRO_TIMER);
            }
        }
        else if (mode == 2) {
            const char* str = NULL;
            switch (action)
            {
                case LA_BUILD0: str = "QMK=" QMK_VERSION ", build= " QMK_BUILDDATE; break;
                case LA_BUILD1:
                    if (keyboard_get_os() == OS_MAC)
                        str = ("kb=" QMK_KEYBOARD ", km=" QMK_KEYMAP ", build= " __DATE__ "/" __TIME__ " (Mac)");
                    else if (keyboard_get_os() == OS_WINDOWS)
                        str = ("kb=" QMK_KEYBOARD ", km=" QMK_KEYMAP ", build= " __DATE__ "/" __TIME__ " (Windows)");
                    else if (keyboard_get_os() == OS_UBUNTU)
                        str = ("kb=" QMK_KEYBOARD ", km=" QMK_KEYMAP ", build= " __DATE__ "/" __TIME__ " (Ubuntu)");
                    break;
                case LA_KEYBOARD_MAC: keyboard_set_os(OS_MAC); break;
                case LA_KEYBOARD_WIN: keyboard_set_os(OS_WINDOWS); break;
                case LA_KEYBOARD_UBUNTU: keyboard_set_os(OS_UBUNTU); break;
            }
            if (str != NULL)
            {
                send_string_with_delay(str, MACRO_TIMER);
            }
        }
    }
    else if (count == 2)
    {
        if (mode == 0 || mode == 1)
        {
            switch (action)
            {
                case LA_NUM: enable_smart_numbers(); break;
                case LA_TOP_OF_FILE: send_taps1(G(KC_UP)); break;
                case LA_BOTTOM_OF_FILE: send_taps1(G(KC_DOWN)); break;
                case LA_CAMEL_CASE: user_camelcase_toggle(); break;
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

                case LA_OPEN_LINE_ABOVE: send_taps3(KC_HOME, KC_ENTER, KC_UP); break;
                case LA_OPEN_LINE_BELOW: send_taps2(KC_END, KC_ENTER); break;
            }
        }
    }
    else if (count == 3)
    {
        uint16_t bracket = KC_NO;
        switch (action)
        {
            case LA_CHANGE_INSIDE_WORD: send_taps3(A(KC_LEFT), A(S(KC_RIGHT)), KC_DEL); break;
            case LA_CHANGE_INSIDE_PRN: bracket = KC_LPRN; break;
            case LA_CHANGE_INSIDE_CBR: bracket = KC_LCBR; break;
            case LA_CHANGE_INSIDE_BRC: bracket = KC_LBRC; break;
            case LA_CHANGE_INSIDE_ABK: bracket = KC_LABK; break;
            case LA_CHANGE_INSIDE_QUOT: bracket = KC_QUOT; break;
            case LA_CHANGE_INSIDE_DQUOT: bracket = KC_DQUO; break;
            case LA_CHANGE_INSIDE_TICKS: bracket = KC_GRV; break;
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
