#include QMK_KEYBOARD_H
#include "config.h"
#include "user_cushi.h"
#include "user_keycodes.h"
#include "user_layers.h"
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
Possible combiniations with NAV and SYM:
- Tap NAV  +  Tap SYM    = unused
- Tap SYM  +  Tap NAV    = RAISE Layer lock
- Hold NAV +  Tap SYM    = SmartNum
- Hold SYM +  Tap NAV    = SmartCaps
- Hold NAV +  Hold SYM   = RAISE Layer

Hold NAV -> Tap SYM will put the keyboard in SMARTNUM mode.
  - When you release NAV withouth having typed anything it will stay in SMARTNUM mode.
  - When you hold NAV and you type some numbers and then release NAV it will exit SMARTNUM mode.

Hold SYM -> Tap NAV will put the keyboard in SMARTCAPS mode, tapping NAV again will cycle to the next SMARTCAPS mode.

*/

#define SMART_CAPS_MAX_SEPARATORS 4

static uint8_t     s_smartcaps_state                               = 0;
static uint8_t     s_smartcaps_arr_seps[SMART_CAPS_MAX_SEPARATORS] = {TC_NO};
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

bool process_feature_key(uint8_t ti, uint8_t tc, keyrecord_t* record)
{
    bool ret = true;
    {
        if (record->event.pressed)
        {
            if (features_active_all(FEATURE_SYM_ONESHOT | FEATURE_NAV_ONESHOT))
            {
                if (tc == TC_BSPACE || tc == TC_SPACE || tc == CC_FNUM || tc == CC_FNAV || tc == CC_FCAPS || tc == CC_FSYM)
                {
                    s_feature_state &= ~(FEATURE_SYM_ONESHOT | FEATURE_NAV_ONESHOT | FEATURE_USED);
                    user_layer_on(LAYER_QWERTY);
                }
            }

            // logic for when a key is pressed
            switch (tc)
            {
                // pressed
                case CC_SHFT:
                case CC_CTRL:
                case CC_ALT:
                case CC_CMD: break;

                case CC_NDOC ... CC_PDOC: s_feature_state |= FEATURE_USED; break;

                
                case TC_A ... TC_Z:
                    s_feature_state |= FEATURE_USED;
                    s_smartcaps_state |= SMART_CAPS_USED;
                    break;

                case TC_AT ... TC_BSLASH:
                    s_feature_state |= FEATURE_USED;
                    if (smartcaps_active_any(SMART_CAPS_NORMAL))
                    {
                        if (!smartcaps_active_any(SMART_CAPS_USED))
                        {
                            if (s_smartcaps_num_seps == 0)
                            {
                                s_smartcaps_arr_seps[0] = tc;
                                s_smartcaps_num_seps    = 1;
                            }
                            else
                            {
                                if (s_smartcaps_num_seps < SMART_CAPS_MAX_SEPARATORS)
                                {
                                    s_smartcaps_arr_seps[s_smartcaps_num_seps] = tc;
                                    s_smartcaps_num_seps++;
                                }
                            }
                            return false;
                        }
                    }
                    break;

                case TC_0 ... TC_9:
                case TC_F1 ... TC_F12: s_feature_state |= FEATURE_USED; break;

                case CC_FNAV: // pressed
                    if (smartcaps_active_all(SMART_CAPS_HOLD))
                    {
                        s_feature_state &= ~FEATURE_USED;
                        s_smartcaps_num_seps = 0;
                        if (smartcaps_active_any(SMART_CAPS_SNAKE))
                        {
                            s_smartcaps_state &= ~(SMART_CAPS_CAMEL | SMART_CAPS_SHIFT | SMART_CAPS_NORMAL | SMART_CAPS_SNAKE);
                            s_smartcaps_state |= SMART_CAPS_NORMAL;
                        }
                        else
                        {
                            if (smartcaps_active_any(SMART_CAPS_CAMEL))
                            {
                                s_smartcaps_state &= ~(SMART_CAPS_CAMEL | SMART_CAPS_SHIFT | SMART_CAPS_NORMAL | SMART_CAPS_SNAKE);
                                s_smartcaps_state |= SMART_CAPS_SNAKE;
                            }
                            else
                            {
                                s_smartcaps_state &= ~(SMART_CAPS_CAMEL | SMART_CAPS_SHIFT | SMART_CAPS_NORMAL | SMART_CAPS_SNAKE);
                                s_smartcaps_state |= SMART_CAPS_CAMEL;
                                s_smartcaps_state |= SMART_CAPS_SHIFT;
                            }
                        }
                    }
                    else
                    {
                        if (features_active_all(FEATURE_CAPS))
                        {
                            s_feature_state &= ~FEATURE_CAPS;
                            s_smartcaps_state = 0;
                            s_smartcaps_num_seps = 0;
                        }
                        if (features_active_all(FEATURE_NUM))
                        {
                            s_feature_state &= ~FEATURE_NUM;
                            user_layer_on(LAYER_QWERTY);
                        }

                        s_feature_state |= FEATURE_NAV;
                        s_feature_state &= ~FEATURE_USED;
                        if (features_active_all(FEATURE_NAV | FEATURE_SYM))
                        {
                            user_layer_on(LAYER_RAISE);
                        }
                        else
                        {
                            user_layer_on(LAYER_NAVIGATION);
                        }
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
                        s_smartcaps_state = 0;
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
                        s_smartcaps_state = SMART_CAPS_NORMAL;
                        s_smartcaps_num_seps = 0;
                    }
                    s_smartcaps_state &= ~SMART_CAPS_USED;
                    s_smartcaps_state |= SMART_CAPS_HOLD;
                    s_feature_state |= FEATURE_CAPS;
                    break;
            }
        }
        else
        {
            switch (tc)
            {
                case CC_SHFT:
                case CC_CTRL:
                case CC_ALT:
                case CC_CMD: break;

                case CC_NDOC ... CC_PDOC: break;

                case TC_AT ... TC_BSLASH:
                    if (smartcaps_active_any(SMART_CAPS_NORMAL))
                    {
                        if (!smartcaps_active_any(SMART_CAPS_USED))
                        {
                            return false;
                        }
                    }

                case TC_0 ... TC_9:
                case TC_F1 ... TC_F12:
                case TC_A ... TC_Z:
                case TC_BSPACE:
                case TC_SPACE:
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
                        if (features_active_all(FEATURE_USED))
                        {
                            user_layer_on(LAYER_SYMBOLS);
                            s_feature_state |= FEATURE_USED;
                            s_feature_state &= ~FEATURE_NAV;
                        }
                        else
                        {
                            s_feature_state &= ~FEATURE_NAV;
                            s_feature_state &= ~FEATURE_SYM;
                            if (smartcaps_active_any(SMART_CAPS_CAMEL | SMART_CAPS_NORMAL | SMART_CAPS_SNAKE) == false)
                            {
                                s_smartcaps_state = SMART_CAPS_NORMAL;
                                s_smartcaps_num_seps = 0;
                            }
                            s_smartcaps_state &= ~SMART_CAPS_USED;
                            s_smartcaps_state |= SMART_CAPS_HOLD;
                            s_feature_state |= FEATURE_CAPS;
                            user_layer_on(LAYER_QWERTY);
                        }
                    }
                    else if (features_active_all(FEATURE_NAV))
                    {
                        s_feature_state &= ~(FEATURE_NAV|FEATURE_NUM|FEATURE_CAPS);
                        if (features_active_all(FEATURE_SYM_ONESHOT))
                        {
                            s_feature_state |= FEATURE_NAV_ONESHOT;
                            user_layer_on(LAYER_RAISE);
                        }
                        else
                        {
                            user_layer_on(LAYER_QWERTY);
                        }
                    }
                    else if (features_active_all(FEATURE_NUM))
                    {
                        if (features_active_all(FEATURE_USED))
                        {
                            s_feature_state &= ~(FEATURE_NUM|FEATURE_CAPS);
                            user_layer_on(LAYER_QWERTY);
                        }
                    }
                    break;

                case CC_FSYM: // released
                    if (features_active_all(FEATURE_NAV | FEATURE_SYM))
                    {
                        // Hold NAV + Tap SYM ?
                        if (!features_active_all(FEATURE_USED))
                        {
                            s_feature_state &= ~FEATURE_NAV;
                            s_feature_state &= ~FEATURE_USED;
                            enable_smart_numbers();
                        }
                        else
                        {
                            user_layer_on(LAYER_NAVIGATION);
                            s_feature_state &= ~(FEATURE_SYM | FEATURE_USED | FEATURE_SYM_ONESHOT);
                        }
                    }
                    else if (features_active_all(FEATURE_SYM))
                    {
                        s_feature_state &= ~(FEATURE_SYM | FEATURE_SYM_ONESHOT);
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
                    else
                    {
                        s_smartcaps_state &= ~SMART_CAPS_HOLD;
                        if (smartcaps_active_any(SMART_CAPS_USED))
                        {
                            s_feature_state &= ~FEATURE_CAPS;
                            s_smartcaps_state = 0;
                            s_smartcaps_num_seps = 0;
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
                        s_feature_state &= ~FEATURE_CAPS;
                        s_smartcaps_state = 0;
                        s_smartcaps_num_seps = 0;
                    }
                    break;
            }
        }
    }

    if (features_active_all(FEATURE_NUM))
    {
        if (tc == TC_SPACE)
        {
            if (record->event.pressed)
            {
                s_feature_state &= ~(FEATURE_NUM|FEATURE_CAPS);
                user_layer_on(LAYER_QWERTY);
            }
        }
    }
    else if (features_active_all((FEATURE_CAPS)))
    {
        if (tc >= TC_RANGE_START && tc <= TC_RANGE_END)
        {
            if (record->event.pressed)
            {
                // Normal Caps, all letters are emitted in 'upper' case.
                // The ';' symbol is emitted as the '_' symbol.
                // When pressing 'comma' we emit a 'space'
                // When pressing 'dot' we cycle to the next mode
                // When 'space' is pressed smart capslock is disabled.

                // Camel Case, when pressing ';' we register space and mark the next key to be registered with 'shift'.
                // When pressing 'comma' we mark the next key to be registered with 'shift'.
                // When pressing 'dot' we cycle to the next mode
                // When 'space' is pressed smart capslock is disabled.

                // Snake Case, when pressing ';' we register a '_' and continue
                // When pressing 'dot' we cycle to the next mode
                // When 'space' is pressed smart capslock is disabled.

                if (smartcaps_active_all(SMART_CAPS_NORMAL))
                {
                    if (tc >= TC_A && tc <= TC_Z)
                    {
                        register_keycode_press_with_shift(ti, tc);
                    }
                    else if (tc == TC_SPACE)
                    {
                        if (s_smartcaps_num_seps == 0)
                        {
                            register_keycode_press(ti, tc);

                            if (!smartcaps_active_all(SMART_CAPS_HOLD))
                            {
                                s_feature_state &= ~FEATURE_CAPS;
                                s_smartcaps_state = 0;
                                s_smartcaps_num_seps = 0;
                            }                            
                        }
                    }
                    else
                    {
                        if (tc == TC_SCLN)
                        {
                            tc = TC_UNDS;
                        }
                        register_keycode_press(ti, tc);
                    }
                }
                else if (smartcaps_active_any(SMART_CAPS_CAMEL | SMART_CAPS_SNAKE))
                {
                    if (tc >= TC_A && tc <= TC_Z)
                    {
                        if (smartcaps_active_all(SMART_CAPS_SHIFT))
                        {
                            register_keycode_press_with_shift(ti, tc);
                            s_smartcaps_state &= ~(SMART_CAPS_SHIFT);
                        }
                        else
                        {
                            register_keycode_press(ti, tc);
                        }
                    }
                    else if (tc == TC_SPACE)
                    {
                        if (smartcaps_active_all(SMART_CAPS_CAMEL))
                        {
                            s_smartcaps_state |= SMART_CAPS_SHIFT;
                        }
                        else
                        {
                            tc = TC_UNDS;
                        }
                        register_keycode_press(ti, tc);
                    }
                    else if (tc == TC_COMMA)
                    {
                        s_smartcaps_state ^= SMART_CAPS_SHIFT;
                    }
                    else if (tc == TC_DOT)
                    {
                        // nothing
                    }
                    else
                    {
                        register_keycode_press(ti, tc);
                    }
                }
            }
            else // record->event.pressed == false
            {
                // This will unregister the keycode as it was registered when it was pressed.
                register_keycode_release(ti, tc);

                if (smartcaps_active_all(SMART_CAPS_NORMAL))
                {
                    if (tc == TC_SPACE)
                    {
                        if (s_smartcaps_num_seps == 0)
                        {

                        }
                        else
                        {
                            // do not emit 'space' but emit the seperator(s)
                            for (int8_t i = 0; i < s_smartcaps_num_seps; ++i)
                            {
                                uint8_t tc = s_smartcaps_arr_seps[i];
                                if (tc == TC_SCLN)
                                {
                                    tc = TC_UNDS;
                                }
                                register_keycode_tap(ti, tc);
                            }
                        }
                    }
                }
                else if (smartcaps_active_all(SMART_CAPS_CAMEL))
                {
                    if (tc == TC_DOT)
                    {
                        s_feature_state &= ~FEATURE_CAPS;
                        s_smartcaps_state = 0;
                        s_smartcaps_num_seps = 0;
                    }
                }
            }
        }

        ret = false;
    }

    return ret;
}
