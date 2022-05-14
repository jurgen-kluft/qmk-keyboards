#include QMK_KEYBOARD_H
#include "config.h"
#include "oneshot.h"
#include "cushi.h"
#include "cukey.h"
#include "feature.h"
#include "leader.h"
#include "vim.h"
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

bool process_record_user(uint16_t _keycode, keyrecord_t* record)
{
    uint16_t keycode = user_layer_get_code(_keycode, record->event.pressed);

#ifdef OLED_DRIVER_ENABLE
    process_record_oled(_keycode, record);
#endif

    switch (keycode)
    {
        case CC_UNDO ... CC_CLOSE:
        {
            if (record->event.pressed)
            {
                keycode = process_cukey(keycode);
                if (keycode != KC_NO)
                    register_code16(keycode);
            }
            else
            {
                keycode = process_cukey(keycode);
                if (keycode != KC_NO)
                    unregister_code16(keycode);
            }

            return false;
        }
        case CC_SECRET_1 ... CC_SECRET_8:
            if (!record->event.pressed)
            {
                turnoff_oneshot_modifiers();
                send_string_with_delay(gSecrets[keycode - CC_SECRET_1], MACRO_TIMER);
            }
            return false;
            break;
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
            break;
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
            return true;
#endif
    }

    if (vim_is_active())
    {
        process_vim(keycode, record);
        return false;
    }

    if (!leader_is_active() && !vim_is_active())
    {
        if (!process_feature_key(keycode, record))
        {
            return false;
        }

        update_oneshot_modifiers(keycode, record);

        switch (keycode)
        {
            case CC_QWERTY:
                if (record->event.pressed)
                {
                    set_single_persistent_default_layer(LAYER_QWERTY);
                }
                break;
            case CC_RSTHD:
                if (record->event.pressed)
                {
                    set_single_persistent_default_layer(LAYER_RSTHD);
                }
                break;
        }
    }

    if (process_leader_user(keycode, record))
        return false;

    user_apply_keycode(keycode, record->event.pressed);
    return false;
}
