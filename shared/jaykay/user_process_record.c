#include QMK_KEYBOARD_H
#include "config.h"
#include "oneshot.h"
#include "cushi.h"
#include "cukey.h"
#include "feature.h"
#include "leader.h"
#include "user_leader.h"
#include "user_keycodes.h"
#include "user_layers.h"

#ifdef OLED_ENABLE
#include "oled.h"
#endif

#if (__has_include("secrets.x") && !defined(NO_SECRETS))
#include "secrets.x"
static const char* gSecrets[] = {SECRET_1, SECRET_2, SECRET_3, SECRET_4, SECRET_5, SECRET_6, SECRET_7, SECRET_8};
#else
static const char* gSecrets[] = {"SECRET_1", "SECRET_2", "SECRET_3", "SECRET_4", "SECRET_5", "SECRET_6", "SECRET_7", "SECRET_8"};
#endif

bool process_record_user(uint16_t kc, keyrecord_t* record)
{
#ifdef OLED_DRIVER_ENABLE
    process_record_oled(kc, record);
#endif

    switch (kc)
    {
#ifdef KEYBOARD_MOONLANDER
        case CC_GAMEL:
            if (record->event.pressed)
            {
                if (user_layer_current() == LAYER_GAMEL)
                {
                    user_layer_on(LAYER_BASE);
                }
                else
                {
                    user_layer_on(LAYER_GAMEL);
                }
            }
            return false;

        case CC_GAMER:
            if (record->event.pressed)
            {
                user_layer_on(LAYER_GAMER);
            }
            else
            {
                user_layer_on(LAYER_GAMEL);
            }
            return false;
#endif
        case CC_UNDO ... CC_CLOSE:
        {
            if (record->event.pressed)
            {
                uint16_t const keycode = process_cukey(kc);
                if (keycode != KC_NO)
                    register_code16(keycode);
            }
            else
            {
                uint16_t const keycode = process_cukey(kc);
                if (keycode != KC_NO)
                    unregister_code16(keycode);
            }
            return false;
        }
        case CC_SECRET_1 ... CC_SECRET_8:
            if (!record->event.pressed)
            {
                turnoff_oneshot_modifiers();
                send_string_with_delay(gSecrets[kc - CC_SECRET_1], MACRO_TIMER);
            }
            return false;
        case CC_SPIFT:
            if (record->event.pressed)
            {
                register_code(KC_SPACE);
                press_oneshot_modifier(ONESHOT_LSFT);
            }
            else
            {
                unregister_code(KC_SPACE);
                release_oneshot_modifier(ONESHOT_LSFT);
            }
            return false;
#if defined(OLED_ENABLE)
        case CC_OLED:
            if (record->event.pressed)
            {
                toggle_display_oled();
            }
            return true;
#elif defined(RGBLIGHT_ENABLE)
        case CC_OLED:
            if (record->event.pressed)
            {
                rgblight_enable();
            }
            return false;
#endif
    }

    if (process_leader_user(kc, record))
    {
        return false;
    }

    {
        if (!process_feature_key(kc, record))
        {
            return false;
        }

        uint16_t cushi = process_cushi_keys(kc, record);
        if (cushi != KC_NO)
        {
            const uint16_t cukc = process_cukey(cushi);
            if (cukc != KC_NO)
            {
                cushi = cukc;
            }

            if (record->event.pressed)
            {
                tap_code16_nomods(cushi);
            }

            update_oneshot_modifiers(cushi, record);
            return false;
        }

        update_oneshot_modifiers(kc, record);
    }

    return true;
}
