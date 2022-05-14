#include QMK_KEYBOARD_H
#include "config.h"
#include "layers.h"
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
    SMART_CAPS_OFF            = 0,
    SMART_CAPS_INIT           = 1,
    SMART_CAPS_COUNT          = 2,
    SMART_CAPS_REPEAT         = 3,
    SMART_CAPS_DEFAULT        = 4,
    SMART_CAPS_MAX_SEPARATORS = 4,
};
static uint8_t s_smartcaps_state                                 = SMART_CAPS_OFF;
static uint8_t s_smartcaps_separators[SMART_CAPS_MAX_SEPARATORS] = {CC_NO};
static int8_t  s_smartcaps_repeat                                = 0;

static uint8_t     s_feature_state = 0;
static inline bool features_active(uint8_t features) { return (s_feature_state & features) == features; }
static inline bool features_active_any(uint8_t features) { return (s_feature_state & features) != 0; }

bool process_feature_key(uint8_t keycode, keyrecord_t* record)
{
    bool ret = true;
    {
        if (record->event.pressed)
        {
            if (features_active(FEATURE_SYM_ONESHOT | FEATURE_NAV_ONESHOT))
            {
                if (keycode == TC_BSPACE || keycode == TC_SPACE || keycode == CC_FNUM || keycode == CC_FNAV || keycode == CC_FCAPS || keycode == CC_FSYM)
                {
                    s_feature_state &= ~(FEATURE_SYM_ONESHOT | FEATURE_NAV_ONESHOT | FEATURE_USED);
                    user_layer_off(LAYER_RAISE);
                }
            }

            if (features_active(FEATURE_CAPS))
            {
                const bool terminate_feature = (keycode == CC_FNUM || keycode == CC_FNAV || keycode == CC_FCAPS);
                if (keycode == TC_SPACE || terminate_feature)
                {
                    if (terminate_feature || s_smartcaps_state == SMART_CAPS_INIT || s_smartcaps_state == SMART_CAPS_DEFAULT)
                    {
                        s_feature_state &= ~(FEATURE_CAPS | FEATURE_USED);
                        s_smartcaps_repeat = 0;
                        s_smartcaps_state  = SMART_CAPS_OFF;

                        user_smartshift_off();

                        if (keycode == CC_FCAPS)
                        {
                            // stop execution otherwise we will again turn on this feature below
                            return false;
                        }

                        if (keycode == CC_FNAV)
                        {
                            // process_record_user should not execute any further otherwise the press/release of KC_FNAV will result in
                            // the activation of 'leader'.
                            // but we do want to continue execution below so that we activate the NAV layer
                            ret = false;
                        }
                    }
                    else
                    {
                        if (s_smartcaps_state == SMART_CAPS_REPEAT)
                        {
                            // emit seperator(s)
                            for (int8_t i = 0; i < s_smartcaps_repeat; ++i)
                            {
                                uint16_t kc = user_get_code16(s_smartcaps_separators[i]);
                                tap_code16(kc);
                            }
                            return false;
                        }
                    }
                }
            }
            if (features_active(FEATURE_NUM))
            {
                if (keycode == TC_SPACE || (keycode == CC_FNUM || keycode == CC_FNAV || keycode == CC_FCAPS))
                {
                    s_feature_state &= ~(FEATURE_NUM | FEATURE_USED);
                    user_layer_off(LAYER_NUMBERS);

                    if (keycode == CC_FNUM)
                    {
                        // stop execution otherwise we will again turn on this feature below
                        return false;
                    }
                }
            }

            // logic for when a key is pressed
            switch (keycode)
            {
                // pressed
                case CC_SHFT:
                case CC_CTRL:
                case CC_ALT:
                case CC_CMD: break;

                // pressed
                case TC_A ... TC_Z:
                    if (features_active(FEATURE_CAPS))
                    {
                        if (s_smartcaps_repeat == 0)
                        {
                            s_smartcaps_state = SMART_CAPS_DEFAULT;
                        }
                        else
                        {
                            s_smartcaps_state = SMART_CAPS_REPEAT;
                        }
                        s_feature_state |= FEATURE_USED;
                        break;
                    }
                case TC_AT ... TC_BSLASH:
                    if (features_active(FEATURE_CAPS))
                    {
                        // override the semicolon -> underscore
                        if (keycode == TC_SCLN)
                        {
                            keycode = TC_UNDS;
                        }

                        s_feature_state |= FEATURE_USED;
                        if (s_smartcaps_state == SMART_CAPS_INIT)
                        {
                            s_smartcaps_state         = SMART_CAPS_COUNT;
                            s_smartcaps_separators[0] = keycode;
                            s_smartcaps_repeat        = 1;
                            ret                       = false;
                        }
                        else if (s_smartcaps_state == SMART_CAPS_COUNT)
                        {
                            if (s_smartcaps_repeat < SMART_CAPS_MAX_SEPARATORS)
                            {
                                s_smartcaps_separators[s_smartcaps_repeat] = keycode;
                                s_smartcaps_repeat++;
                                ret = false;
                            }
                            else
                            {
                                s_smartcaps_state = SMART_CAPS_REPEAT;
                            }
                        }
                        break;
                    }

                case TC_0 ... TC_9:
                case TC_F1 ... TC_F12: s_feature_state |= FEATURE_USED; break;

                case CC_FNAV: // pressed
                    s_feature_state |= FEATURE_NAV;
                    s_feature_state &= ~FEATURE_USED;
                    if (features_active(FEATURE_NAV | FEATURE_SYM))
                    {
                        user_layer_off(LAYER_SYMBOLS);
                        user_layer_off(LAYER_NAVIGATION);
                        user_layer_on(LAYER_RAISE);
                    }
                    else
                    {
                        user_layer_on(LAYER_NAVIGATION);
                    }
                    break;
                case CC_FSYM: // pressed
                    if (features_active(FEATURE_SYM_ONESHOT))
                    {
                        s_feature_state &= ~(FEATURE_USED | FEATURE_SYM | FEATURE_SYM_ONESHOT);
                        user_layer_off(LAYER_SYMBOLS);
                    }
                    else
                    {
                        s_feature_state |= FEATURE_SYM;
                        s_feature_state &= ~FEATURE_USED;
                        if (features_active(FEATURE_SYM | FEATURE_NAV))
                        {
                            user_layer_off(LAYER_SYMBOLS);
                            user_layer_off(LAYER_NAVIGATION);
                            user_layer_on(LAYER_RAISE);
                        }
                        else
                        {
                            user_layer_on(LAYER_SYMBOLS);
                        }
                    }
                    break;
                case CC_FNUM: // pressed
                    if (!features_active(FEATURE_NAV | FEATURE_SYM))
                    {
                        s_feature_state |= FEATURE_NUM;
                        s_feature_state &= ~FEATURE_USED;
                        user_layer_on(LAYER_NUMBERS);
                    }
                    break;
                case CC_FCAPS: // pressed
                    if (!features_active(FEATURE_NAV | FEATURE_SYM))
                    {
                        s_smartcaps_state  = SMART_CAPS_INIT;
                        s_smartcaps_repeat = 0;

                        s_feature_state |= FEATURE_CAPS;
                        s_feature_state &= ~FEATURE_USED;
                        user_smartshift_on();
                    }
                    break;
            }
        }
        else
        {
            switch (keycode)
            {
                case CC_SHFT:
                case CC_CTRL:
                case CC_ALT:
                case CC_CMD: break;

                // released
                case TC_AT ... TC_BSLASH:
                case TC_0 ... TC_9:
                case TC_F1 ... TC_F12:
                case TC_A ... TC_Z:
                case TC_BSPACE:
                case TC_SPACE:
                    if (features_active(FEATURE_SYM_ONESHOT) && !features_active(FEATURE_NAV_ONESHOT))
                    {
                        s_feature_state &= ~FEATURE_SYM_ONESHOT;
                        user_layer_off(LAYER_SYMBOLS);
                    }
                    break;

                case CC_FNAV: // released
                    if (features_active(FEATURE_NAV | FEATURE_SYM))
                    {
                        user_layer_off(LAYER_RAISE);
                        user_layer_off(LAYER_NAVIGATION);
                        user_layer_on(LAYER_SYMBOLS);
                        s_feature_state |= FEATURE_USED;
                        s_feature_state &= ~FEATURE_NAV;
                    }
                    else if (features_active(FEATURE_NAV))
                    {
                        s_feature_state &= ~FEATURE_NAV;
                        if (features_active(FEATURE_SYM_ONESHOT))
                        {
                            s_feature_state |= FEATURE_NAV_ONESHOT;
                            user_layer_off(LAYER_SYMBOLS);
                            user_layer_off(LAYER_NAVIGATION);
                            user_layer_on(LAYER_RAISE);
                        }
                        else
                        {
                            user_layer_off(LAYER_NAVIGATION);
                        }
                    }
                    break;

                case CC_FSYM: // released
                    if (features_active(FEATURE_NAV | FEATURE_SYM))
                    {
                        user_layer_off(LAYER_RAISE);
                        user_layer_off(LAYER_SYMBOLS);
                        user_layer_on(LAYER_NAVIGATION);
                        s_feature_state &= ~(FEATURE_SYM | FEATURE_USED | FEATURE_SYM_ONESHOT);
                    }
                    else if (features_active(FEATURE_SYM))
                    {
                        if (features_active(FEATURE_USED))
                        {
                            user_layer_off(LAYER_SYMBOLS);
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
                    if (features_active(FEATURE_NUM))
                    {
                        if (features_active(FEATURE_USED))
                        {
                            s_feature_state &= ~FEATURE_NUM;
                            user_layer_off(LAYER_NUMBERS);
                        }
                    }
                    break;

                case CC_FCAPS: // released
                    if (features_active(FEATURE_CAPS))
                    {
                        if (features_active(FEATURE_USED))
                        {
                            s_feature_state &= ~FEATURE_CAPS;
                            user_smartshift_off();
                        }
                    }
                    break;
            }
        }
    }

    return ret;
}
