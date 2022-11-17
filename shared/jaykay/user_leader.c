#include QMK_KEYBOARD_H
#include <version.h>
#include "config.h"
#include "leader.h"
#include "cukey.h"
#include "oneshot.h"
#include "user_layers.h"
#include "user_keycodes.h"

enum eleader_1t1
{
    LA_EASYMOTION,    // f
    LA_CENTER,        // z
    LA_DOTSPACESHIFT, // . (shift)
};

static const leader1_t leader1t1_array[] = {
    [LA_EASYMOTION]    = {KC_F},
    [LA_CENTER]        = {KC_Z},
    [LA_DOTSPACESHIFT] = {KC_DOT},
};

enum eleader_1t2
{
    LA_AND, // a, ' && '
    LA_EQ,  // e, ' == '
    LA_GAE, // g, ' >= '
    LA_LAE, // l, ' <= '
    LA_NEQ, // n, ' != '
    LA_OR,  // o, ' || '
};

// clang-format off
static const leader1_t leader1t2_array[] = {
    [LA_AND]                 = { KC_A },
    [LA_EQ]                  = { KC_E },
    [LA_GAE]                 = { KC_G },
    [LA_LAE]                 = { KC_L },
    [LA_NEQ]                 = { KC_N },
    [LA_OR]                  = { KC_O },
};
// clang-format on

enum eleader_2t2
{
    LA_UNREAL_ENGINE, // ue, 'Unreal Engine 4 '
    LA_XBOX_ONE,      // xo, 'Xbox One '
    LA_XBOX_SERIES,   // xs, 'Xbox Series '
    LA_PS4,           // ps, 'PS4 '
    LA_PS5,           // pp, 'PS5 '
    LA_NINTENDO,      // sw, 'Nintendo Switch '
    LA_MGSIV,         // mg, 'Metal Gear Solid IV '
};

// clang-format off
static const leader2_t leader2t2_array[] = {
    [LA_UNREAL_ENGINE]       = { KC_U, KC_E },
    [LA_XBOX_ONE]            = { KC_X, KC_O },
    [LA_XBOX_SERIES]         = { KC_X, KC_S },
    [LA_PS4]                 = { KC_P, KC_S },
    [LA_PS5]                 = { KC_P, KC_P },
    [LA_NINTENDO]            = { KC_S, KC_W },
    [LA_MGSIV]               = { KC_M, KC_G },
};
// clang-format on

enum eleader_1t3
{
    LA_BUILD0,
    LA_BUILD1,
    LA_KEYLAYOUT_RSTHD,
    LA_KEYLAYOUT_QWERTY,
    LA_KEYBOARD_MAC,
    LA_KEYBOARD_UBUNTU,
    LA_KEYBOARD_WIN,
};

// clang-format off
static const leader1_t leader1t3_array[] = {
    [LA_BUILD0]              = { KC_B },
    [LA_BUILD1]              = { KC_D },
    [LA_KEYBOARD_MAC]        = { KC_M },
    [LA_KEYBOARD_UBUNTU]     = { KC_U },
    [LA_KEYBOARD_WIN]        = { KC_W },
    [LA_KEYLAYOUT_RSTHD]     = { KC_R },
    [LA_KEYLAYOUT_QWERTY]    = { KC_Q },
};
// clang-format on

enum eleader_2t1
{
    LA_CHANGE_LINE,      // cl
    LA_CHANGE_WORD,      // cw
    LA_DELETE_WORD_BACK, // db
    LA_DELETE_LINE,      // dd
    LA_DELETE_UNTIL_EOL, // de
    LA_DELETE_WORD,      // dw
    LA_DELETE_UNTIL_SOL, // ds
    LA_TOP_OF_FILE,      // gg
    LA_BOTTOM_OF_FILE,   // gb
    LA_OPEN_LINE_ABOVE,  // oa
    LA_OPEN_LINE_BELOW,  // oo
    LA_COPY_LINE,        // yy
    LA_SWITCH_QUOTES,    // ss
};

// clang-format off
static const leader2_t leader2t1_array[] = {
    [LA_CHANGE_LINE]      = {KC_C, KC_L},
    [LA_CHANGE_WORD]      = {KC_C, KC_W},
    [LA_DELETE_WORD_BACK] = {KC_D, KC_B},
    [LA_DELETE_LINE]      = {KC_D, KC_D},
    [LA_DELETE_UNTIL_EOL] = {KC_D, KC_E},
    [LA_DELETE_WORD]      = {KC_D, KC_W},
    [LA_DELETE_UNTIL_SOL] = {KC_D, KC_S},
    [LA_TOP_OF_FILE]      = {KC_G, KC_G},
    [LA_BOTTOM_OF_FILE]   = {KC_G, KC_B},
    [LA_OPEN_LINE_ABOVE]  = {KC_O, KC_A},
    [LA_OPEN_LINE_BELOW]  = {KC_O, KC_O},
    [LA_COPY_LINE]        = {KC_Y, KC_Y},
    [LA_SWITCH_QUOTES]    = {KC_S, KC_S},
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

    LA_DELETE_INSIDE_ABK,   // dia (acts the same as cia)
    LA_DELETE_INSIDE_BRC,   // dib (acts the same as cib)
    LA_DELETE_INSIDE_CBR,   // dic (acts the same as cic)
    LA_DELETE_INSIDE_DQUOT, // did (acts the same as cid)
    LA_DELETE_INSIDE_PRN,   // dip (acts the same as cip)
    LA_DELETE_INSIDE_QUOT,  // diq (acts the same as ciq)
    LA_DELETE_INSIDE_TICKS, // dit (acts the same as cit)
    LA_DELETE_INSIDE_WORD,  // diw (acts the same as ciw)

    LA_PASTE_INSIDE_ABK,   // pia
    LA_PASTE_INSIDE_BRC,   // pib
    LA_PASTE_INSIDE_CBR,   // pic
    LA_PASTE_INSIDE_DQUOT, // pid
    LA_PASTE_INSIDE_PRN,   // pip
    LA_PASTE_INSIDE_QUOT,  // piq
    LA_PASTE_INSIDE_TICKS, // pit
    LA_PASTE_INSIDE_WORD,  // piw

    LA_YANK_INSIDE_ABK,   // yia
    LA_YANK_INSIDE_BRC,   // yib
    LA_YANK_INSIDE_CBR,   // yic
    LA_YANK_INSIDE_DQUOT, // yid
    LA_YANK_INSIDE_PRN,   // yip
    LA_YANK_INSIDE_QUOT,  // yiq
    LA_YANK_INSIDE_TICKS, // yit
    LA_YANK_INSIDE_WORD,  // yiw
};

// clang-format off
static const leader3_t leader3t1_array[] = {
    [LA_CHANGE_INSIDE_ABK]   = {KC_C, KC_I, KC_A},
    [LA_CHANGE_INSIDE_BRC]   = {KC_C, KC_I, KC_B},
    [LA_CHANGE_INSIDE_CBR]   = {KC_C, KC_I, KC_C},
    [LA_CHANGE_INSIDE_DQUOT] = {KC_C, KC_I, KC_D},
    [LA_CHANGE_INSIDE_PRN]   = {KC_C, KC_I, KC_P},
    [LA_CHANGE_INSIDE_QUOT]  = {KC_C, KC_I, KC_Q},
    [LA_CHANGE_INSIDE_TICKS] = {KC_C, KC_I, KC_T},
    [LA_CHANGE_INSIDE_WORD]  = {KC_C, KC_I, KC_W},
    [LA_DELETE_INSIDE_ABK]   = {KC_D, KC_I, KC_A},
    [LA_DELETE_INSIDE_BRC]   = {KC_D, KC_I, KC_B},
    [LA_DELETE_INSIDE_CBR]   = {KC_D, KC_I, KC_C},
    [LA_DELETE_INSIDE_DQUOT] = {KC_D, KC_I, KC_D},
    [LA_DELETE_INSIDE_PRN]   = {KC_D, KC_I, KC_P},
    [LA_DELETE_INSIDE_QUOT]  = {KC_D, KC_I, KC_Q},
    [LA_DELETE_INSIDE_TICKS] = {KC_D, KC_I, KC_T},
    [LA_DELETE_INSIDE_WORD]  = {KC_D, KC_I, KC_W},
    [LA_PASTE_INSIDE_ABK]    = {KC_P, KC_I, KC_A},
    [LA_PASTE_INSIDE_BRC]    = {KC_P, KC_I, KC_B},
    [LA_PASTE_INSIDE_CBR]    = {KC_P, KC_I, KC_C},
    [LA_PASTE_INSIDE_DQUOT]  = {KC_P, KC_I, KC_D},
    [LA_PASTE_INSIDE_PRN]    = {KC_P, KC_I, KC_P},
    [LA_PASTE_INSIDE_QUOT]   = {KC_P, KC_I, KC_Q},
    [LA_PASTE_INSIDE_TICKS]  = {KC_P, KC_I, KC_T},
    [LA_PASTE_INSIDE_WORD]   = {KC_P, KC_I, KC_W},
    [LA_YANK_INSIDE_ABK]     = {KC_Y, KC_I, KC_A},
    [LA_YANK_INSIDE_BRC]     = {KC_Y, KC_I, KC_B},
    [LA_YANK_INSIDE_CBR]     = {KC_Y, KC_I, KC_C},
    [LA_YANK_INSIDE_DQUOT]   = {KC_Y, KC_I, KC_D},
    [LA_YANK_INSIDE_PRN]     = {KC_Y, KC_I, KC_P},
    [LA_YANK_INSIDE_QUOT]    = {KC_Y, KC_I, KC_Q},
    [LA_YANK_INSIDE_TICKS]   = {KC_Y, KC_I, KC_T},
    [LA_YANK_INSIDE_WORD]    = {KC_Y, KC_I, KC_W},
};
// clang-format on

enum eleader_4t1
{
    LA_SCREENSHOT, // snip
};

static leader4_t const leader4t1_array[] = {
    [LA_SCREENSHOT] = {KC_S, KC_N, KC_I, KC_P},
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
    .leader2_array = leader2t2_array,
    .leader2_count = ARRAY_SIZE(leader2t2_array),
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
    const char* str = NULL;
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
            switch (action)
            {
                case LA_AND: str = " && "; break;
                case LA_EQ: str = " == "; break;
                case LA_GAE: str = " >= "; break;
                case LA_LAE: str = " <= "; break;
                case LA_NEQ: str = " != "; break;
                case LA_OR: str = " || "; break;
            }
        }
        else if (mode == 2)
        {
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
                case LA_KEYLAYOUT_RSTHD: keyboard_set_layout(LAYER_RSTHD); break;
                case LA_KEYLAYOUT_QWERTY: keyboard_set_layout(LAYER_QWERTY); break;
            }
        }
        else if (mode == 4) {}
    }
    else if (count == 2)
    {
        if (mode == 0)
        {
            switch (action)
            {
                case LA_TOP_OF_FILE:
                    if (keyboard_get_os() == OS_WINDOWS)
                    {
                        send_taps1(C(KC_HOME));
                    }
                    else
                    {
                        send_taps1(G(KC_HOME));
                    }
                    break;
                case LA_BOTTOM_OF_FILE:
                    if (keyboard_get_os() == OS_WINDOWS)
                    {
                        send_taps1(C(KC_END));
                    }
                    else
                    {
                        send_taps1(G(KC_END));
                    }
                    break;
                case LA_CHANGE_WORD:
                case LA_DELETE_WORD:
                    if (keyboard_get_os() == OS_MAC)
                    {
                        send_taps2(A(S(KC_RIGHT)), KC_DEL);
                    }
                    else
                    {
                        send_taps2(C(S(KC_RIGHT)), KC_DEL);
                    }
                    break;
                    break;
                case LA_DELETE_WORD_BACK:
                    if (keyboard_get_os() == OS_MAC)
                    {
                        send_taps2(A(S(KC_LEFT)), KC_DEL);
                    }
                    else
                    {
                        send_taps2(C(S(KC_LEFT)), KC_DEL);
                    }
                    break;
                case LA_CHANGE_LINE: send_taps3(KC_END, S(KC_HOME), KC_DEL); break;
                case LA_DELETE_LINE: send_taps1(C(S(KC_D))); break;
                case LA_DELETE_UNTIL_SOL: send_taps2(S(KC_HOME), KC_DEL); break;
                case LA_DELETE_UNTIL_EOL: send_taps2(S(KC_END), KC_DEL); break;

                case LA_OPEN_LINE_ABOVE: send_taps3(KC_HOME, KC_ENTER, KC_UP); break;
                case LA_OPEN_LINE_BELOW: send_taps2(KC_END, KC_ENTER); break;

                case LA_COPY_LINE: // yy
                    send_taps2(KC_END, S(KC_HOME));
                    if (keyboard_get_os() == OS_MAC)
                    {
                        send_taps1(G(KC_C));
                        break;
                    }
                    else
                    {
                        send_taps1(C(KC_C));
                        break;
                    }
                    break;

                case LA_SWITCH_QUOTES: send_taps2(C(KC_K), S(KC_SCLN)); break;
            }
        }
        else if (mode == 1)
        {
            switch (action)
            {
                case LA_UNREAL_ENGINE: str = "Unreal Engine 4 "; break;
                case LA_XBOX_ONE: str = "Xbox One "; break;
                case LA_XBOX_SERIES: str = "Xbox Series "; break;
                case LA_PS4: str = "PS4 "; break;
                case LA_PS5: str = "PS5 "; break;
                case LA_NINTENDO: str = "Nintendo Switch "; break;
                case LA_MGSIV: str = "Metal Gear Solid IV "; break;
            }
        }
    }
    else if (count == 3)
    {
        uint8_t  type    = 'c';
        uint16_t bracket = KC_NO;
        switch (action)
        {
            case LA_PASTE_INSIDE_WORD: type = 'p'; break; 
            case LA_DELETE_INSIDE_WORD: type = 'c'; break;
            case LA_CHANGE_INSIDE_WORD: type = 'c'; break;
            case LA_YANK_INSIDE_WORD: type = 'y'; break;
        }

        switch (action)
        {
            case LA_YANK_INSIDE_WORD: 
            case LA_PASTE_INSIDE_WORD:
            case LA_CHANGE_INSIDE_WORD:
            case LA_DELETE_INSIDE_WORD:
                if (keyboard_get_os() == OS_MAC)
                {
                    send_taps2(A(KC_LEFT), A(S(KC_RIGHT)));
                }
                else
                {
                    send_taps2(C(KC_LEFT), C(S(KC_RIGHT)));
                }
                break;

            
            case LA_DELETE_INSIDE_PRN:
            case LA_CHANGE_INSIDE_PRN: bracket = KC_LPRN; break;
            case LA_DELETE_INSIDE_CBR:
            case LA_CHANGE_INSIDE_CBR: bracket = KC_LCBR; break;
            case LA_DELETE_INSIDE_BRC:
            case LA_CHANGE_INSIDE_BRC: bracket = KC_LBRC; break;
            case LA_DELETE_INSIDE_ABK:
            case LA_CHANGE_INSIDE_ABK: bracket = KC_LABK; break;
            case LA_DELETE_INSIDE_QUOT:
            case LA_CHANGE_INSIDE_QUOT: bracket = KC_QUOT; break;
            case LA_DELETE_INSIDE_DQUOT:
            case LA_CHANGE_INSIDE_DQUOT: bracket = KC_DQUO; break;
            case LA_DELETE_INSIDE_TICKS:
            case LA_CHANGE_INSIDE_TICKS: bracket = KC_GRV; break;

            case LA_PASTE_INSIDE_PRN:
                type    = 'p';
                bracket = KC_LPRN;
                break;
            case LA_PASTE_INSIDE_CBR:
                type    = 'p';
                bracket = KC_LCBR;
                break;
            case LA_PASTE_INSIDE_BRC:
                type    = 'p';
                bracket = KC_LBRC;
                break;
            case LA_PASTE_INSIDE_ABK:
                type    = 'p';
                bracket = KC_LABK;
                break;
            case LA_PASTE_INSIDE_QUOT:
                type    = 'p';
                bracket = KC_QUOT;
                break;
            case LA_PASTE_INSIDE_DQUOT:
                type    = 'p';
                bracket = KC_DQUO;
                break;
            case LA_PASTE_INSIDE_TICKS:
                type    = 'p';
                bracket = KC_GRV;
                break;

            case LA_YANK_INSIDE_PRN:
                type    = 'y';
                bracket = KC_LPRN;
                break;
            case LA_YANK_INSIDE_CBR:
                type    = 'y';
                bracket = KC_LCBR;
                break;
            case LA_YANK_INSIDE_BRC:
                type    = 'y';
                bracket = KC_LBRC;
                break;
            case LA_YANK_INSIDE_ABK:
                type    = 'y';
                bracket = KC_LABK;
                break;
            case LA_YANK_INSIDE_QUOT:
                type    = 'y';
                bracket = KC_QUOT;
                break;
            case LA_YANK_INSIDE_DQUOT:
                type    = 'y';
                bracket = KC_DQUO;
                break;
            case LA_YANK_INSIDE_TICKS:
                type    = 'y';
                bracket = KC_GRV;
                break;                
        }

        if (bracket != KC_NO)
        {
            // vscode: Quick and Simple Text Selection
            if (keyboard_get_os() == OS_MAC)
            {
                send_taps2(G(KC_K), bracket);
            }
            else
            {
                send_taps2(C(KC_K), bracket);
            }
            wait_ms(200);
        }

        switch (type)
        {
            case 'c': send_taps1(KC_DEL); break;
            case 'p':
                if (keyboard_get_os() == OS_MAC)
                {
                    send_taps1(LGUI(KC_V));
                }
                else
                {
                    send_taps1(LCTL(KC_V));
                }
                break;
            case 'y':
                if (keyboard_get_os() == OS_MAC)
                {
                    send_taps1(LGUI(KC_C));
                }
                else
                {
                    send_taps1(LCTL(KC_C));
                }
                break;
        }
    }
    else if (count == 4)
    {
        switch (action)
        {
            case LA_SCREENSHOT: send_taps1(G(S(KC_4))); break;
        }
    }

    if (str != NULL)
    {
        send_string_with_delay(str, MACRO_TIMER);
    }
}
