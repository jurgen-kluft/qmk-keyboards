#include QMK_KEYBOARD_H
#include "config.h"
#include "user_keycodes.h"
#include "user_layers.h"
#include "oneshot.h"
#include "feature.h"

enum
{
    FEATURE_SYM         = 0x04,
    FEATURE_SYM_ONESHOT = 0x08,
    FEATURE_NAV         = 0x10,
    FEATURE_RAISE       = 0x20,
    FEATURE_USED        = 0x40,
};

static uint8_t     s_feature_state = 0;
static inline bool features_active_all(uint8_t features) { return (s_feature_state & features) == features; }
static inline bool features_active_any(uint8_t features) { return (s_feature_state & features) != 0; }

bool process_feature_key(uint16_t kc, keyrecord_t* record)
{
    if (record->event.pressed)
    {
        if (features_active_all(FEATURE_SYM_ONESHOT | FEATURE_RAISE))
        {
            if (kc == KC_BSPC || kc == KC_SPACE || kc == CC_FNAV || kc == CC_FSYM)
            {
                s_feature_state &= ~(FEATURE_SYM_ONESHOT | FEATURE_RAISE | FEATURE_USED);
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
                // s_smartcaps_state |= SMART_CAPS_USED;
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
            case KC_QUES: s_feature_state |= FEATURE_USED; break;

            case KC_1 ... KC_0:
            case KC_F1 ... KC_F12: s_feature_state |= FEATURE_USED; break;

            case CC_FNAV: // pressed
                s_feature_state &= ~(FEATURE_USED);
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
                    user_layer_on(LAYER_QWERTY);
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
            case KC_COMM:
            case KC_DOT:
            case KC_F1 ... KC_F12:
            case KC_A ... KC_Z:
            case S(KC_A)... S(KC_Z): s_feature_state |= FEATURE_USED;

            case KC_BSPC:
            case KC_SPACE:
                if (features_active_all(FEATURE_SYM_ONESHOT) && !features_active_all(FEATURE_RAISE))
                {
                    s_feature_state &= ~FEATURE_SYM_ONESHOT;
                    user_layer_on(LAYER_QWERTY);
                }
                break;

            case CC_FNAV: // released
                if (features_active_all(FEATURE_NAV | FEATURE_SYM))
                {
                    s_feature_state &= ~FEATURE_NAV;
                    user_layer_on(LAYER_SYMBOLS);
                }
                else if (features_active_all(FEATURE_NAV))
                {
                    s_feature_state &= ~(FEATURE_NAV);
                    if (features_active_all(FEATURE_SYM_ONESHOT))
                    {
                        s_feature_state |= FEATURE_RAISE;
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
                    s_feature_state &= ~(FEATURE_SYM | FEATURE_SYM_ONESHOT);
                }
                else if (features_active_all(FEATURE_SYM))
                {
                    s_feature_state &= ~(FEATURE_SYM | FEATURE_SYM_ONESHOT);
                    if (features_active_all(FEATURE_USED))
                    {
                        s_feature_state &= ~FEATURE_USED;
                        user_layer_on(LAYER_QWERTY);
                    }
                    else
                    {
                        s_feature_state |= FEATURE_SYM_ONESHOT;
                    }
                }
                break;
        }
    }

    return true;
}