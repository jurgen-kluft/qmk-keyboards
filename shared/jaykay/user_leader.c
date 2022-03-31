#include QMK_KEYBOARD_H
#include <version.h>
#include "leader.h"
#include "cukey.h"

#if (__has_include("secrets.x") && !defined(NO_SECRETS))
#include "secrets.x"
#else
#define SECRET_5 "test"
#endif

enum eleader_range
{
    // abreviations
    LA_DIGIT_TO_WORD = 0,
};

static leader_range_t leader_range_array[] = {
    [LA_DIGIT_TO_WORD] = {.start = KC_1, .end = KC_0},
};

enum eleader_one
{
    LA_EASYMOTION = 0,
};

static leader1_t const leader1_array[] = {
    [LA_EASYMOTION] = {KC_F},
};

enum eleader_two
{
    LA_CHANGE_LINE,      // cl
    LA_CHANGE_WORD,      // cw
    LA_DELETE_UNTIL_BOL, // db
    LA_DELETE_UNTIL_EOL, // de
    LA_DELETE_LINE,      // dl
    LA_DELETE_WORD,      // dw
    LA_EQ,               // eq
    LA_GMAIL,            // gm
    LA_GT,               // gt
    LA_HOTMAIL,          // hm
    LA_INFO,             // in
    LA_CLASS,            // kc
    LA_RETURN,           // kr
    LA_STRUCT,           // ks
    LA_VOID,             // kv
    LA_LT,               // lt
    LA_PASSWORD,         // pw
    LA_SCREENSHOT,       // ss
};

static leader2_t const leader2_array[] = {
    [LA_CHANGE_LINE]      = {KC_C, KC_L},
    [LA_CHANGE_WORD]      = {KC_C, KC_W},
    [LA_DELETE_UNTIL_BOL] = {KC_D, KC_B},
    [LA_DELETE_UNTIL_EOL] = {KC_D, KC_E},
    [LA_DELETE_LINE]      = {KC_D, KC_L},
    [LA_DELETE_WORD]      = {KC_D, KC_W},
    [LA_EQ]               = {KC_E, KC_Q},
    [LA_GMAIL]            = {KC_G, KC_M},
    [LA_GT]               = {KC_G, KC_T},
    [LA_HOTMAIL]          = {KC_H, KC_M},
    [LA_INFO]             = {KC_I, KC_N},
    [LA_CLASS]            = {KC_K, KC_C},
    [LA_RETURN]           = {KC_K, KC_R},
    [LA_STRUCT]           = {KC_K, KC_S},
    [LA_VOID]             = {KC_K, KC_V},
    [LA_LT]               = {KC_L, KC_T},
    [LA_PASSWORD]         = {KC_P, KC_W},
    [LA_SCREENSHOT]       = {KC_S, KC_S},
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

#define send_taps2(tap1, tap2) \
    tap_code16(tap1);          \
    tap_code16(tap2)
#define send_taps3(tap1, tap2, tap3) \
    tap_code16(tap1);                \
    tap_code16(tap2);                \
    tap_code16(tap3)

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

static leader_config_t leader_config = {
    .leader_range_array = leader_range_array,
    .leader_range_count = ARRAY_SIZE(leader_range_array),
    .leader1_array      = leader1_array,
    .leader1_count      = ARRAY_SIZE(leader1_array),
    .leader2_array      = leader2_array,
    .leader2_count      = ARRAY_SIZE(leader2_array),
    .leader3_array      = leader3_array,
    .leader3_count      = ARRAY_SIZE(leader3_array),
};

bool process_leader_user(uint16_t keycode, keyrecord_t* record) { return process_record_leader(keycode, record, &leader_config); }

void execute_leader_action(uint8_t action, uint8_t mode, uint8_t count, uint16_t* keycodes)
{
    if (count == 1)
    {
        switch (action)
        {
            case LA_EASYMOTION: tap_code16(A(KC_S)); break;
        }
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
            case LA_SCREENSHOT: tap_code16(G(S(KC_4))); break;
            case LA_PASSWORD: str = SECRET_5; break;
            case LA_GMAIL: str = ("jurgen.kluft@gmail.com"); break;
            case LA_HOTMAIL: str = ("jurgen_kluft@hotmail.com"); break;
            case LA_GT: str = (" > "); break;
            case LA_LT: str = (" < "); break;
            case LA_EQ: str = (" == "); break;
            case LA_STRUCT: str = ("struct "); break;
            case LA_CLASS: str = ("class "); break;
            case LA_RETURN: str = ("return "); break;
            case LA_VOID: str = ("void "); break;
            case LA_CHANGE_WORD:
            case LA_DELETE_WORD: send_taps2(A(S(KC_RIGHT)), KC_DEL); break;
            case LA_CHANGE_LINE: send_taps3(KC_END, S(KC_HOME), KC_DEL); break;
            case LA_DELETE_LINE: send_taps2(C(KC_D), KC_L); break;
            case LA_DELETE_UNTIL_EOL: send_taps2(S(KC_END), KC_DEL); break;
            case LA_DELETE_UNTIL_BOL: send_taps2(S(KC_HOME), KC_DEL); break;
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
}
