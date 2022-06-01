#include QMK_KEYBOARD_H
#include "config.h"
#include "user_cushi.h"
#include "user_keycodes.h"
#include "user_layers.h"
#include "feature.h"

/*

FEATURE_NUM, FEATURE_CAPS, FEATURE_SYM and FEATURE_NAV.

The main reason for processing layer and smart feature keys for tri layer state is that it allows more flexibility in terms
of how and when layers are turned on and off.

The key KC_FNAV can basically turn off any feature by just pressing and releasing it, it acts as a 'reset' to the default.

Pressing and releasing the KC_FSYM key will activate the _SYM layer in one-shot mode and allow one other key press after which
the layer will turn off, it can be cancelled by pressing and releasing KC_SPACE, KC_BSPACE, KC_FCAPS, KC_FNUM.
Pressing and releasing the KC_FNAV key while the _SYM layer is in one-shot mode will lock the _RAISE layer.

Pressing and releasing the KC_FNUM key will activate the _NUM layer and stay active until one of the following keys is
pressed: KC_FNUM, KC_FNAV, KC_FSYM, KC_SPACE.

Pressing and releasing the KC_FCAPS key will activate _QWERTY_CAPS layer and stay on until one of the following keys is pressed:
KC_FCAPS, KC_FNAV, KC_FSYM, KC_SPACE.

Holding the KC_FNUM key will activate the _NUM layer and while other keys are pressed it will stay on until the KC_FNUM key is released.
Holding the KC_FCAPS key will activate the _QWERTY_CAPS layer and when other keys are pressed it will stay on until the KC_FCAPS key is released.
Holding the KC_FSYM key will activate the _SYM layer and while other keys are pressed it will stay on until the KC_FSYM key is released.
Holding the KC_FNAV key will activate the _NAV layer and while other keys are pressed it will stay on until the KC_FNAV key is released.
Holding the KC_FNAV and KC_FSYM keys will activate the _RAISE layer and when releasing the KC_FNAV key or the KC_FSYM key it will deactivate the _RAISE layer.

Smart Capslock

Tapping or holding KC_FCAPS will activate 'smart capslock' mode. Normal behaviour will deactivate it when you press space.
However when 'smart capslock' mode is active, N different symbols can be set to repeat by pressing symbols at the beginning.

Pressing KC_FCAPS, KC_FNAC or KC_FSYM will deactivate this special 'smart capslock' mode. When the separator is space, pressing
space will deactivate 'smart capslock' mode.

*/

enum
{
    FEATURE_CAPS        = 1,
    FEATURE_NUM         = 2,
    FEATURE_SYM         = 4,
    FEATURE_SYM_ONESHOT = 8,
    FEATURE_NAV         = 16,
    FEATURE_NAV_ONESHOT = 32,
    FEATURE_USED        = 64,
};

enum
{
    SMART_CAPS_OFF    = 0x00,
    SMART_CAPS_SHIFT  = 0x01,
    SMART_CAPS_HOLD   = 0x02,
    SMART_CAPS_ON     = 0x10,
    SMART_CAPS_NORMAL = 0x20,
    SMART_CAPS_REPEAT = 0x40,
    SMART_CAPS_CAMEL  = 0x80,
};

#define SMART_CAPS_MAX_SEPARATORS 4

static uint8_t     s_smartcaps_state                               = 0;
static uint8_t     s_smartcaps_arr_seps[SMART_CAPS_MAX_SEPARATORS] = {TC_NO};
static int8_t      s_smartcaps_num_seps                            = 0;
static inline bool smartcaps_active_all(uint8_t features) { return (s_smartcaps_state & features) == features; }
static inline bool smartcaps_active_any(uint8_t features) { return (s_smartcaps_state & features) != 0; }

static uint8_t     s_feature_state = 0;
static inline bool features_active_all(uint8_t features) { return (s_feature_state & features) == features; }
static inline bool features_active_any(uint8_t features) { return (s_feature_state & features) != 0; }

void enable_smart_capslock(void)
{
    if (!features_active_all(FEATURE_NAV | FEATURE_SYM))
    {
        s_smartcaps_state    = SMART_CAPS_ON;
        s_smartcaps_num_seps = 0;

        s_feature_state &= ~(FEATURE_NUM | FEATURE_USED);
        s_feature_state |= FEATURE_CAPS;
        s_feature_state &= ~FEATURE_USED;
    }
}

void disable_smart_capslock(void)
{
    s_feature_state &= ~(FEATURE_CAPS | FEATURE_USED);
    s_smartcaps_state = 0;
}

void enable_smart_numbers(void)
{
    if (!features_active_all(FEATURE_NAV | FEATURE_SYM))
    {
        s_feature_state |= FEATURE_NUM;
        s_feature_state &= ~FEATURE_USED;
        user_layer_on(LAYER_NUMBERS);
    }
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

                // pressed
                case TC_A ... TC_Z:
                    s_feature_state |= FEATURE_USED;
                    if (features_active_all(FEATURE_CAPS))
                    {
                        if (smartcaps_active_any(SMART_CAPS_NORMAL | SMART_CAPS_REPEAT | SMART_CAPS_CAMEL) == false)
                        {
                            if (s_smartcaps_num_seps == 0)
                            {
                                s_smartcaps_state |= SMART_CAPS_NORMAL;
                                s_smartcaps_arr_seps[0] = TC_UNDS;
                                s_smartcaps_num_seps    = 1;
                            }
                            else
                            {
                                s_smartcaps_state |= SMART_CAPS_REPEAT;
                            }
                        }
                    }
                    break;

                case TC_AT ... TC_BSLASH:
                    s_feature_state |= FEATURE_USED;
                    if (features_active_all(FEATURE_CAPS))
                    {
                        if (smartcaps_active_any(SMART_CAPS_NORMAL | SMART_CAPS_REPEAT | SMART_CAPS_CAMEL) == false)
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
                    if (features_active_all(FEATURE_CAPS))
                    {
                        disable_smart_capslock();
                    }
                    else if (features_active_all(FEATURE_NUM))
                    {
                        s_feature_state &= ~(FEATURE_NUM | FEATURE_USED);
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
                        disable_smart_capslock();
                    }
                    else if (features_active_all(FEATURE_NUM))
                    {
                        s_feature_state &= ~(FEATURE_NUM | FEATURE_USED);
                        user_layer_on(LAYER_QWERTY);
                    }
                    else
                    {
                        enable_smart_numbers();
                    }
                    break;
                case CC_FCAPS:
                    if (features_active_all(FEATURE_CAPS))
                    {
                        if (smartcaps_active_any(SMART_CAPS_CAMEL))
                        {
                            disable_smart_capslock();
                        }
                        else
                        {
                            s_feature_state &= ~FEATURE_USED;
                            s_smartcaps_state &= ~(SMART_CAPS_REPEAT | SMART_CAPS_CAMEL | SMART_CAPS_SHIFT | SMART_CAPS_NORMAL);
                            s_smartcaps_state |= SMART_CAPS_CAMEL;
                            s_smartcaps_state |= SMART_CAPS_SHIFT;
                        }
                    }
                    else
                    {
                        enable_smart_capslock();
                        s_feature_state &= ~FEATURE_USED;
                        s_smartcaps_state |= SMART_CAPS_HOLD;
                    }
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
                    if (features_active_all(FEATURE_CAPS))
                    {
                        if (smartcaps_active_any(SMART_CAPS_NORMAL | SMART_CAPS_REPEAT | SMART_CAPS_CAMEL) == false)
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
                        user_layer_on(LAYER_SYMBOLS);
                        s_feature_state |= FEATURE_USED;
                        s_feature_state &= ~FEATURE_NAV;
                    }
                    else if (features_active_all(FEATURE_NAV))
                    {
                        s_feature_state &= ~FEATURE_NAV;
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
                    break;

                case CC_FSYM: // released
                    if (features_active_all(FEATURE_NAV | FEATURE_SYM))
                    {
                        user_layer_on(LAYER_NAVIGATION);
                        s_feature_state &= ~(FEATURE_SYM | FEATURE_USED | FEATURE_SYM_ONESHOT);
                    }
                    else if (features_active_all(FEATURE_SYM))
                    {
                        if (features_active_all(FEATURE_USED))
                        {
                            user_layer_on(LAYER_QWERTY);
                            if (features_active_all(FEATURE_NUM))
                            {
                                user_layer_on(LAYER_NUMBERS);
                            }
                            s_feature_state &= ~(FEATURE_SYM | FEATURE_USED | FEATURE_SYM_ONESHOT);
                        }
                        else
                        {
                            s_feature_state &= ~(FEATURE_SYM | FEATURE_USED | FEATURE_SYM_ONESHOT);
                            s_feature_state |= FEATURE_SYM_ONESHOT;
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
                    if (features_active_all(FEATURE_CAPS))
                    {
                        s_smartcaps_state &= ~SMART_CAPS_HOLD;
                        if (features_active_all(FEATURE_USED))
                        {
                            s_feature_state &= ~FEATURE_CAPS;
                        }
                    }
                    break;
            }
        }
    }

    if (features_active_all(FEATURE_CAPS))
    {
        if (tc >= TC_RANGE_START && tc <= TC_RANGE_END)
        {
            if (record->event.pressed)
            {
                // Normal Caps, all letters are emitted in 'upper' case.
                // The ';' symbol is handled to be converted to the '_' symbol.
                // When 'space' is pressed smart capslock is disabled.

                // Camel Case, when pressing 'space' we mark the next key to be registered with 'shift' and we
                // also register 'space'.
                // When pressing 'comma' we mark the next key to be registered with 'shift'.
                // When pressing 'dot' we disable smart capslock.

                if (smartcaps_active_all(SMART_CAPS_NORMAL))
                {
                    if (tc >= TC_A && tc <= TC_Z)
                    {
                        register_keycode_press_with_shift(ti, tc);
                    }
                    else if (tc == TC_SPACE)
                    {
                        // nothing, on release will turn off smart capslock
                        register_keycode_press(ti, tc);
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
                else if (smartcaps_active_all(SMART_CAPS_REPEAT))
                {
                    if (tc >= TC_A && tc <= TC_Z)
                    {
                        register_keycode_press_with_shift(ti, tc);
                    }
                    else if (tc == TC_SPACE)
                    {
                        // nothing, on release will emit the separators
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
                else if (smartcaps_active_all(SMART_CAPS_CAMEL))
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
                        register_keycode_press(ti, tc);
                        s_smartcaps_state |= SMART_CAPS_SHIFT;
                    }
                    else if (tc == TC_COMMA)
                    {
                        s_smartcaps_state ^= SMART_CAPS_SHIFT;
                    }
                    else if (tc == TC_BSPACE)
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
                        if (!smartcaps_active_all(SMART_CAPS_HOLD))
                        {
                            disable_smart_capslock();
                        }
                    }
                }
                else if (smartcaps_active_all(SMART_CAPS_REPEAT))
                {
                    if (tc == TC_SPACE)
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
                else if (smartcaps_active_all(SMART_CAPS_CAMEL))
                {
                    if (tc == TC_DOT)
                    {
                        disable_smart_capslock();
                    }
                }
            }
        }

        ret = false;
    }

    return ret;
}
