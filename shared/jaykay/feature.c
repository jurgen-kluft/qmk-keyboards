#include QMK_KEYBOARD_H
#include "layers.h"
#include "feature.h"
#include "user_oneshot.h"
#include "user_cushi.h"

/*

FEATURE_NUM, FEATURE_CAPS, FEATURE_SYM and FEATURE_NAV.

The main reason for processing layer and smart feature keys for tri layer state is that it allows more flexibility in terms
of how and when layers are turned on and off.

The key KC_FNAV can basically turn off any feature by just pressing and releasing it.

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

static uint8_t s_feature_state = 0;

static inline bool features_active(uint8_t features) { return (s_feature_state & features) == features; }
static inline bool features_active_any(uint8_t features) { return (s_feature_state & features) != 0; }

static inline bool is_qwerty(void)
{
    uint16_t layers = layer_state | default_layer_state;
    return (layers & (1 << _QWERTY)) != 0;
}

bool process_feature_key(uint16_t keycode, keyrecord_t* record)
{
    // if ((keycode < QK_MODS_MAX) && (!IS_MOD(keycode)))
    {
        if (record->event.pressed)
        {
            if (features_active(FEATURE_SYM_ONESHOT | FEATURE_NAV_ONESHOT))
            {
                if (keycode == KC_BSPACE || keycode == KC_SPACE || keycode == KC_FNUM || keycode == KC_FNAV || keycode == KC_FCAPS || keycode == KC_FSYM)
                {
                    s_feature_state &= ~(FEATURE_SYM_ONESHOT | FEATURE_NAV_ONESHOT | FEATURE_USED);
                    layer_off(_RAISE);
                }
                else
                {
                    return true;
                }
            }

            if (features_active_any(FEATURE_NUM | FEATURE_CAPS))
            {
                if (keycode == KC_SPACE || keycode == KC_FNUM || keycode == KC_FNAV || keycode == KC_FCAPS)
                {
                    if (features_active(FEATURE_CAPS))
                    {
                        s_feature_state &= ~(FEATURE_CAPS | FEATURE_USED);
                        if (is_qwerty())
                        {
                            layer_off(_QWERTY_CAPS);
                            layer_off(_RSTHD_CAPS);
                        }
                        else
                        {
                            layer_off(_QWERTY_CAPS);
                            layer_off(_RSTHD_CAPS);
                        }

                        if (keycode == KC_FCAPS)
                        {
                            return false;
                        }
                    }
                    if (features_active(FEATURE_NUM))
                    {
                        s_feature_state &= ~(FEATURE_NUM | FEATURE_USED);
                        layer_off(_NUM);
                        if (keycode == KC_FNUM)
                        {
                            return false;
                        }
                    }
                }
            }

            // logic for when a key is pressed
            switch (keycode)
            {
                // pressed
                case OS_SHFT:
                case OS_CTRL:
                case OS_ALT:
                case OS_CMD: break;

                // pressed
                case KC_COMMA_QUES:
                case KC_DOT_EXCL: break;

                // pressed
                case SH_TG:

                // pressed
                case KC_1 ... KC_0:
                case S(KC_1)... S(KC_0):
                case KC_F1 ... KC_F12:
                case KC_A ... KC_Z:
                case KC_MINUS ... KC_SLASH:
                case S(KC_MINUS)... S(KC_SLASH): s_feature_state |= FEATURE_USED; break;

                case KC_FNAV: // pressed
                    s_feature_state |= FEATURE_NAV;
                    s_feature_state &= ~FEATURE_USED;
                    if (features_active(FEATURE_NAV | FEATURE_SYM))
                    {
                        layer_off(_SYM);
                        layer_off(_NAV);
                        layer_on(_RAISE);
                    }
                    else
                    {
                        layer_on(_NAV);
                    }
                    break;
                case KC_FSYM: // pressed
                    if (features_active(FEATURE_SYM_ONESHOT))
                    {
                        s_feature_state &= ~(FEATURE_USED | FEATURE_SYM | FEATURE_SYM_ONESHOT);
                        layer_off(_SYM);
                    }
                    else
                    {
                        s_feature_state |= FEATURE_SYM;
                        s_feature_state &= ~FEATURE_USED;
                        if (features_active(FEATURE_SYM | FEATURE_NAV))
                        {
                            layer_off(_SYM);
                            layer_off(_NAV);
                            layer_on(_RAISE);
                        }
                        else
                        {
                            layer_on(_SYM);
                        }
                    }
                    break;
                case KC_FNUM: // pressed
                    if (!features_active(FEATURE_NAV | FEATURE_SYM))
                    {
                        s_feature_state |= FEATURE_NUM;
                        s_feature_state &= ~FEATURE_USED;
                        layer_on(_NUM);
                    }
                    break;
                case KC_FCAPS: // pressed
                    if (!features_active(FEATURE_NAV | FEATURE_SYM))
                    {
                        s_feature_state |= FEATURE_CAPS;
                        s_feature_state &= ~FEATURE_USED;
                        if (is_qwerty())
                        {
                            layer_on(_QWERTY_CAPS);
                        }
                        else
                        {
                            layer_on(_RSTHD_CAPS);
                        }
                    }
                    break;
            }
        }
        else
        {
            switch (keycode)
            {
                case OS_SHFT:
                case OS_CTRL:
                case OS_ALT:
                case OS_CMD: break;

                // released
                case KC_COMMA_QUES:
                case KC_DOT_EXCL: break;

                // released
                case KC_1 ... KC_0:
                case S(KC_1)... S(KC_0):
                case KC_F1 ... KC_F12:
                case KC_A ... KC_Z:
                case KC_MINUS ... KC_SLASH:
                case S(KC_MINUS)... S(KC_SLASH):
                case KC_BSPACE:
                case KC_SPACE:
                case SH_TG:
                    if (features_active(FEATURE_SYM_ONESHOT) && !features_active(FEATURE_NAV_ONESHOT))
                    {
                        s_feature_state &= ~FEATURE_SYM_ONESHOT;
                        layer_off(_SYM);
                    }
                    break;

                case KC_FNAV: // released
                    if (features_active(FEATURE_NAV | FEATURE_SYM))
                    {
                        layer_off(_RAISE);
                        layer_off(_NAV);
                        layer_on(_SYM);
                        s_feature_state |= FEATURE_USED;
                        s_feature_state &= ~FEATURE_NAV;
                    }
                    else if (features_active(FEATURE_NAV))
                    {
                        s_feature_state &= ~FEATURE_NAV;
                        if (features_active(FEATURE_SYM_ONESHOT))
                        {
                            s_feature_state |= FEATURE_NAV_ONESHOT;
                            layer_off(_SYM);
                            layer_off(_NAV);
                            layer_on(_RAISE);
                        }
                        else
                        {
                            layer_off(_NAV);
                        }
                    }
                    break;

                case KC_FSYM: // released
                    if (features_active(FEATURE_NAV | FEATURE_SYM))
                    {
                        layer_off(_RAISE);
                        layer_on(_NAV);
                        layer_off(_SYM);
                        s_feature_state &= ~(FEATURE_SYM | FEATURE_USED | FEATURE_SYM_ONESHOT);
                    }
                    else if (features_active(FEATURE_SYM))
                    {
                        if (features_active(FEATURE_USED))
                        {
                            layer_off(_SYM);
                            s_feature_state &= ~(FEATURE_SYM | FEATURE_USED | FEATURE_SYM_ONESHOT);
                        }
                        else
                        {
                            s_feature_state &= ~(FEATURE_SYM | FEATURE_USED | FEATURE_SYM_ONESHOT);
                            s_feature_state |= FEATURE_SYM_ONESHOT;
                        }
                    }
                    break;

                case KC_FNUM: // released
                    if (features_active(FEATURE_NUM))
                    {
                        if (features_active(FEATURE_USED))
                        {
                            s_feature_state &= ~FEATURE_NUM;
                            layer_off(_NUM);
                        }
                    }
                    break;

                case KC_FCAPS: // released
                    if (features_active(FEATURE_CAPS))
                    {
                        if (features_active(FEATURE_USED))
                        {
                            s_feature_state &= ~FEATURE_CAPS;
                            layer_off(_QWERTY_CAPS);
                        }
                    }
                    break;
            }
        }
    }

    return true;
}
