#include QMK_KEYBOARD_H
#include "config.h"
#include "user_keycodes.h"
#include "user_layers.h"
#include "oneshot.h"
#include "feature.h"

enum
{
    FEATURE_CAPS        = 0x01,
    FEATURE_NUM         = 0x02,
    FEATURE_SYM         = 0x04,
    FEATURE_SYM_ONESHOT = 0x08,
    FEATURE_NAV         = 0x10,
    FEATURE_NAV_ONESHOT = 0x20,
    FEATURE_USED        = 0x40,
};

enum
{
    SMART_CAPS_OFF    = 0x00,
    SMART_CAPS_USED   = 0x02,
    SMART_CAPS_SHIFT  = 0x04,
    SMART_CAPS_HOLD   = 0x08,
    SMART_CAPS_NORMAL = 0x10,
    SMART_CAPS_CAMEL  = 0x40,
    SMART_CAPS_SNAKE  = 0x80,
};

/*
Possible combinations with NAV and SYM:
- Tap NAV  +  Tap SYM    = unused (part of `leader` logic)
- Tap SYM  +  Tap NAV    = RAISE Layer lock
- Hold NAV +  Tap SYM    = SmartNum  (You can now release NAV and it will stay in SmartNum mode)
- Hold SYM +  Tap NAV    = SmartCaps (You can now release SYM and it will stay in SmartCaps mode)
- Hold NAV +  Hold SYM   = RAISE Layer

Hold NAV -> Tap SYM will put the keyboard in SMARTNUM mode.
  - When you release NAV withouth having typed anything it will stay in SMARTNUM mode.
  - When you hold NAV and you type some numbers and then release NAV it will exit SMARTNUM mode.

Hold SYM -> Tap NAV will put the keyboard in SMARTCAPS mode, tapping NAV again will cycle to the next SMARTCAPS mode.
*/

#define SMART_CAPS_MAX_SEPARATORS 4

static uint8_t     s_smartcaps_state                               = 0;
static uint16_t    s_smartcaps_arr_seps[SMART_CAPS_MAX_SEPARATORS] = {KC_NO};
static int8_t      s_smartcaps_num_seps                            = 0;
static inline bool smartcaps_active_all(uint8_t features) { return (s_smartcaps_state & features) == features; }
static inline bool smartcaps_active_any(uint8_t features) { return (s_smartcaps_state & features) != 0; }

static uint8_t     s_feature_state = 0;
static inline bool features_active_all(uint8_t features) { return (s_feature_state & features) == features; }
static inline bool features_active_any(uint8_t features) { return (s_feature_state & features) != 0; }

void enable_smart_numbers(void)
{
    s_feature_state |= FEATURE_NUM;
    s_feature_state &= ~FEATURE_USED;
    user_layer_on(LAYER_NUMBERS);
}

bool process_feature_key(uint16_t kc, keyrecord_t* record)
{
    if (record->event.pressed)
    {
        if (features_active_all(FEATURE_SYM_ONESHOT | FEATURE_NAV_ONESHOT))
        {
            if (kc == KC_BSPACE || kc == KC_SPACE || kc == CC_FNUM || kc == CC_FNAV || kc == CC_FCAPS || kc == CC_FSYM)
            {
                s_feature_state &= ~(FEATURE_SYM_ONESHOT | FEATURE_NAV_ONESHOT | FEATURE_USED);
                user_layer_on(LAYER_QWERTY);
            }
        }

        // logic for when a key is pressed
        switch (kc)
        {
            // pressed
            case CC_SHFT:
            case CC_CTRL:
            case CC_ALT:
            case CC_CMD: break;

            case CC_UNDO ... CC_CLOSE: s_feature_state |= FEATURE_USED; break;

            case KC_COMM:
            case KC_DOT:
            case KC_A ... KC_Z:
            case S(KC_A)... S(KC_Z):
                s_feature_state |= FEATURE_USED;
                s_smartcaps_state |= SMART_CAPS_USED;
                break;

            case KC_MINS:
            case KC_EQL:
            case KC_LBRC:
            case KC_RBRC:
            case KC_BSLS:
            case KC_NUHS:
            case KC_SCLN:
            case KC_QUOT:
            case KC_GRV:
            case KC_SLSH:
            case KC_TILD:
            case KC_EXLM:
            case KC_AT:
            case KC_HASH:
            case KC_DLR:
            case KC_PERC:
            case KC_CIRC:
            case KC_AMPR:
            case KC_ASTR:
            case KC_LPRN:
            case KC_RPRN:
            case KC_UNDS:
            case KC_PLUS:
            case KC_LCBR:
            case KC_RCBR:
            case KC_PIPE:
            case KC_COLN:
            case KC_DQUO:
            case KC_LABK:
            case KC_RABK:
            case KC_QUES:

                s_feature_state |= FEATURE_USED;
                if (smartcaps_active_any(SMART_CAPS_NORMAL))
                {
                    if (!smartcaps_active_any(SMART_CAPS_USED))
                    {
                        if (s_smartcaps_num_seps < SMART_CAPS_MAX_SEPARATORS)
                        {
                            s_smartcaps_arr_seps[s_smartcaps_num_seps] = kc;
                            s_smartcaps_num_seps++;
                        }
                        return false;
                    }
                }
                break;

            case KC_1 ... KC_0:
            case KC_F1 ... KC_F12: s_feature_state |= FEATURE_USED; break;

            case CC_FNAV: // pressed
                s_feature_state &= ~(FEATURE_CAPS | FEATURE_NUM | FEATURE_USED);
                s_smartcaps_state    = 0;
                s_smartcaps_num_seps = 0;

                s_feature_state |= FEATURE_NAV;
                if (features_active_all(FEATURE_NAV | FEATURE_SYM))
                {
                    user_layer_on(LAYER_RAISE);
                }
                else
                {
                    user_layer_on(LAYER_NAVIGATION);
                }
                break;
            case CC_FSYM: // pressed
                if (features_active_all(FEATURE_SYM_ONESHOT))
                {
                    s_feature_state &= ~(FEATURE_USED | FEATURE_SYM | FEATURE_SYM_ONESHOT);
                    if (features_active_all(FEATURE_NUM))
                    {
                        user_layer_on(LAYER_NUMBERS);
                    }
                    else
                    {
                        user_layer_on(LAYER_QWERTY);
                    }
                }
                else
                {
                    s_feature_state |= FEATURE_SYM;
                    s_feature_state &= ~FEATURE_USED;
                    if (features_active_all(FEATURE_SYM | FEATURE_NAV))
                    {
                        user_layer_on(LAYER_RAISE);
                    }
                    else
                    {
                        user_layer_on(LAYER_SYMBOLS);
                    }
                }
                break;
            case CC_FNUM:
                if (features_active_all(FEATURE_CAPS))
                {
                    s_feature_state &= ~FEATURE_CAPS;
                    s_smartcaps_state    = 0;
                    s_smartcaps_num_seps = 0;
                }

                if (features_active_all(FEATURE_NUM))
                {
                    s_feature_state &= ~FEATURE_NUM;
                    user_layer_on(LAYER_QWERTY);
                }
                else
                {
                    s_feature_state &= ~FEATURE_USED;
                    enable_smart_numbers();
                }
                break;
            case CC_FCAPS:
                if (smartcaps_active_any(SMART_CAPS_CAMEL | SMART_CAPS_NORMAL | SMART_CAPS_SNAKE) == false)
                {
                    user_layer_on(LAYER_QWERTY_CAPS);
                    s_smartcaps_state       = SMART_CAPS_NORMAL;
                    s_smartcaps_num_seps    = 1;
                    s_smartcaps_arr_seps[0] = KC_SCLN;
                }
                s_smartcaps_state &= ~SMART_CAPS_USED;
                s_smartcaps_state |= SMART_CAPS_HOLD;
                s_feature_state |= FEATURE_CAPS;
                break;
        }
    }
    else
    {
        switch (kc)
        {
            case CC_SHFT:
            case CC_CTRL:
            case CC_ALT:
            case CC_CMD: break;

            case CC_UNDO ... CC_CLOSE: break;

            case KC_MINS:
            case KC_EQL:
            case KC_LBRC:
            case KC_RBRC:
            case KC_BSLS:
            case KC_NUHS:
            case KC_SCLN:
            case KC_QUOT:
            case KC_GRV:
            case KC_SLSH:
            case KC_TILD:
            case KC_EXLM:
            case KC_AT:
            case KC_HASH:
            case KC_DLR:
            case KC_PERC:
            case KC_CIRC:
            case KC_AMPR:
            case KC_ASTR:
            case KC_LPRN:
            case KC_RPRN:
            case KC_UNDS:
            case KC_PLUS:
            case KC_LCBR:
            case KC_RCBR:
            case KC_PIPE:
            case KC_COLN:
            case KC_DQUO:
            case KC_LABK:
            case KC_RABK:
            case KC_QUES:

                if (smartcaps_active_any(SMART_CAPS_NORMAL))
                {
                    if (!smartcaps_active_any(SMART_CAPS_USED))
                    {
                        return false;
                    }
                }

            case KC_COMM:
            case KC_DOT:
            case KC_F1 ... KC_F12:
            case KC_A ... KC_Z:
            case S(KC_A)... S(KC_Z):
                s_feature_state |= FEATURE_USED;

            case KC_BSPACE:
            case KC_SPACE:
                if (features_active_all(FEATURE_SYM_ONESHOT) && !features_active_all(FEATURE_NAV_ONESHOT))
                {
                    s_feature_state &= ~FEATURE_SYM_ONESHOT;
                    user_layer_on(LAYER_QWERTY);
                    if (features_active_all(FEATURE_NUM))
                    {
                        user_layer_on(LAYER_NUMBERS);
                    }
                }
                break;

            case CC_FNAV: // released
                if (features_active_all(FEATURE_NAV | FEATURE_SYM))
                {
                    user_layer_on(LAYER_SYMBOLS);
                    if (features_active_all(FEATURE_USED))
                    {
                        s_feature_state |= FEATURE_USED;
                        s_feature_state &= ~FEATURE_NAV;
                    }
                    else
                    {
                        s_feature_state &= ~FEATURE_NAV;
                        s_feature_state |= FEATURE_CAPS;
                        s_smartcaps_state = SMART_CAPS_NORMAL;
                        s_smartcaps_state |= SMART_CAPS_HOLD;
                        s_smartcaps_num_seps = 0;
                    }
                }
                else if (features_active_all(FEATURE_NAV))
                {
                    s_feature_state &= ~(FEATURE_NAV);
                    if (features_active_all(FEATURE_SYM_ONESHOT))
                    {
                        s_feature_state &= ~(FEATURE_NUM | FEATURE_CAPS);
                        s_feature_state |= FEATURE_NAV_ONESHOT;
                        user_layer_on(LAYER_RAISE);
                    }
                    else
                    {
                        if (features_active_all(FEATURE_NUM))
                        {
                            if (features_active_all(FEATURE_USED))
                            {
                                s_feature_state &= ~(FEATURE_NUM | FEATURE_CAPS);
                                user_layer_on(LAYER_QWERTY);
                            }
                        }
                        else
                        {
                            s_feature_state &= ~(FEATURE_NUM | FEATURE_CAPS);
                            user_layer_on(LAYER_QWERTY);
                        }
                    }
                }

                break;

            case CC_FSYM: // released
                if (features_active_all(FEATURE_NAV | FEATURE_SYM))
                {
                    s_feature_state &= ~(FEATURE_SYM | FEATURE_SYM_ONESHOT);
                    // Hold NAV + Tap SYM ?
                    if (!features_active_all(FEATURE_USED))
                    {
                        enable_smart_numbers();
                    }
                    else
                    {
                        s_feature_state &= ~(FEATURE_USED);
                        user_layer_on(LAYER_NAVIGATION);
                    }
                }
                else if (features_active_all(FEATURE_SYM))
                {
                    s_feature_state &= ~(FEATURE_SYM | FEATURE_SYM_ONESHOT);
                    if (features_active_all(FEATURE_CAPS))
                    {
                        if (s_smartcaps_num_seps == 0)
                        {
                            s_smartcaps_num_seps    = 1;
                            s_smartcaps_arr_seps[0] = KC_UNDS;
                        }
                        s_smartcaps_state &= ~SMART_CAPS_HOLD;
                        user_layer_on(LAYER_QWERTY_CAPS);
                    }
                    else
                    {
                        if (features_active_all(FEATURE_USED))
                        {
                            s_feature_state &= ~FEATURE_USED;
                            user_layer_on(LAYER_QWERTY);
                            if (features_active_all(FEATURE_NUM))
                            {
                                user_layer_on(LAYER_NUMBERS);
                            }
                        }
                        else
                        {
                            s_feature_state |= FEATURE_SYM_ONESHOT;
                        }
                    }
                }
                break;

            case CC_FNUM: // released
                if (features_active_all(FEATURE_NUM))
                {
                    if (features_active_all(FEATURE_USED))
                    {
                        s_feature_state &= ~FEATURE_NUM;
                        user_layer_on(LAYER_QWERTY);
                    }
                }
                break;

            case CC_FCAPS: // released
                s_smartcaps_state &= ~SMART_CAPS_HOLD;
                if (smartcaps_active_any(SMART_CAPS_USED))
                {
                    user_layer_on(LAYER_QWERTY);
                    s_feature_state &= ~FEATURE_CAPS;
                    s_smartcaps_state    = 0;
                    s_smartcaps_num_seps = 0;
                }
                break;
        }
    }

    // if (features_active_all(FEATURE_NAV))
    //     send_string_with_delay("NAV ", 1);
    // if (features_active_all(FEATURE_NAV_ONESHOT))
    //     send_string_with_delay("NAV1 ", 1);
    // if (features_active_all(FEATURE_SYM))
    //     send_string_with_delay("SYM ", 1);
    // if (features_active_all(FEATURE_SYM_ONESHOT))
    //     send_string_with_delay("SYM1 ", 1);
    // if (features_active_all(FEATURE_NUM))
    //     send_string_with_delay("NUM ", 1);
    // if (features_active_all(FEATURE_CAPS))
    //     send_string_with_delay("CAPS ", 1);


    // switch (user_layer_current())
    // {
    //     case LAYER_QWERTY: send_string_with_delay("0 ", 1); break;
    //     case LAYER_RSTHD: send_string_with_delay("1 ", 1);break;
    //     case LAYER_QWERTY_CAPS: send_string_with_delay("2 ", 1);break;
    //     case LAYER_RSTHD_CAPS: send_string_with_delay("3 ", 1);break;
    //     case LAYER_NUMBERS: send_string_with_delay("4 ", 1);break;
    //     case LAYER_SYMBOLS: send_string_with_delay("5 ", 1);break;
    //     case LAYER_NAVIGATION: send_string_with_delay("6 ", 1);break;
    //     case LAYER_RAISE: send_string_with_delay("7 ", 1);break;
    // }

    if (features_active_all(FEATURE_NUM))
    {
        if (kc == KC_SPACE)
        {
            if (!record->event.pressed)
            {
                s_feature_state &= ~(FEATURE_NUM | FEATURE_CAPS);
                if (!features_active_all(FEATURE_SYM))
                {
                    user_layer_on(LAYER_QWERTY);
                }
            }
        }
    }
    else if (features_active_all(FEATURE_CAPS))
    {
        if (record->event.pressed)
        {
            // Normal Caps, all letters are emitted in 'upper' case.
            // The ';' symbol is emitted as the '_' symbol.
            // When pressing 'comma' we emit a 'space'
            // When pressing 'dot' we cycle to the next mode
            // When 'space' is pressed smart capslock is disabled.
            if (kc >= KC_A && kc <= KC_Z)
            {
                if (smartcaps_active_all(SMART_CAPS_SHIFT))
                {
                    press_oneshot_modifier(ONESHOT_LSFT);
                    s_smartcaps_state &= ~SMART_CAPS_SHIFT;
                }
            }
            else if (kc == KC_SPACE)
            {
                // will be handled on release
            }
            else if (kc == KC_DOT)
            {
                // will be handled on release
                return false;
            }
            else if (kc == KC_UNDS)
            {
                if (smartcaps_active_all(SMART_CAPS_CAMEL))
                {
                    s_smartcaps_state |= SMART_CAPS_SHIFT;
                }
                return false;
            }
            else if (kc == KC_COMMA)
            {
                if (smartcaps_active_all(SMART_CAPS_NORMAL))
                {
                    user_layer_on(LAYER_QWERTY_CAPS);
                    kc = KC_SPACE;
                    register_keycode_press(kc);
                }
                else if (smartcaps_active_any(SMART_CAPS_CAMEL | SMART_CAPS_SNAKE))
                {
                    user_layer_on(LAYER_QWERTY);
                    s_smartcaps_state ^= SMART_CAPS_SHIFT;
                }
                return false;
            }
        }
        else // record->event.pressed == false
        {
            if (kc == KC_SPACE)
            {
                if (!smartcaps_active_all(SMART_CAPS_HOLD))
                {
                    s_feature_state &= ~FEATURE_CAPS;
                    s_smartcaps_state    = 0;
                    s_smartcaps_num_seps = 0;
                }
            }
            else if (kc == KC_DOT)
            {
                s_feature_state &= ~FEATURE_USED;
                s_smartcaps_num_seps = 0;
                if (smartcaps_active_any(SMART_CAPS_SNAKE))
                {
                    s_smartcaps_state &= ~(SMART_CAPS_CAMEL | SMART_CAPS_SHIFT | SMART_CAPS_NORMAL | SMART_CAPS_SNAKE);
                    s_smartcaps_state |= SMART_CAPS_NORMAL;
                    s_smartcaps_num_seps    = 1;
                    s_smartcaps_arr_seps[0] = KC_SCLN;
                }
                else if (smartcaps_active_any(SMART_CAPS_CAMEL))
                {
                    s_smartcaps_state &= ~(SMART_CAPS_CAMEL | SMART_CAPS_SHIFT | SMART_CAPS_NORMAL | SMART_CAPS_SNAKE);
                    s_smartcaps_state |= SMART_CAPS_SNAKE;
                    s_smartcaps_num_seps    = 1;
                    s_smartcaps_arr_seps[0] = KC_SCLN;
                }
                else
                {
                    s_smartcaps_state &= ~(SMART_CAPS_CAMEL | SMART_CAPS_SHIFT | SMART_CAPS_NORMAL | SMART_CAPS_SNAKE);
                    s_smartcaps_state |= SMART_CAPS_CAMEL;
                    s_smartcaps_state |= SMART_CAPS_SHIFT;
                    s_smartcaps_num_seps    = 1;
                    s_smartcaps_arr_seps[0] = KC_SPACE;
                }
                return false;
            }
            else if (kc == KC_UNDS)
            {
                for (int8_t i = 0; i < s_smartcaps_num_seps; ++i)
                {
                    uint16_t kc = s_smartcaps_arr_seps[i];
                    register_keycode_tap(kc);
                }
                return false;
            }
            else if (kc == KC_COMMA)
            {
                return false;
            }
        }
    }

    return true;
}