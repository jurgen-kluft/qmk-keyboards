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

bool process_record_user(uint16_t kc16, keyrecord_t* record)
{
    uint8_t const kc8 = user_layer_get_code(kc16, record->event.pressed);

#ifdef OLED_DRIVER_ENABLE
    process_record_oled(kc16, record);
#endif

    switch (kc8)
    {
#ifdef KEYBOARD_MOONLANDER
        case CC_GAMEL:
            if (record->event.pressed)
            {
                if (user_layer() == LAYER_GAMEL)
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
                kc16 = process_cukey(kc8);
                if (kc16 != KC_NO)
                    register_code16(kc16);
            }
            else
            {
                kc16 = process_cukey(kc8);
                if (kc16 != KC_NO)
                    unregister_code16(kc16);
            }

            return false;
        }
        case CC_SECRET_1 ... CC_SECRET_8:
            if (!record->event.pressed)
            {
                turnoff_oneshot_modifiers();
                send_string_with_delay(gSecrets[kc8 - CC_SECRET_1], MACRO_TIMER);
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
        process_vim(kc8, record);
        return false;
    }

    if (!leader_is_active() && !vim_is_active())
    {
        if (!process_feature_key(kc8, record))
        {
            return false;
        }

        update_oneshot_modifiers(kc8, record);

        switch (kc8)
        {
            case CC_QWERTY:
                if (record->event.pressed)
                {
                    keyboard_set_layout(LAYER_QWERTY);
                }
                break;
            case CC_RSTHD:
                if (record->event.pressed)
                {
                    keyboard_set_layout(LAYER_RSTHD);
                }
                break;
        }
    }

    if (process_leader_user(kc8, record))
        return false;

    user_apply_keycode(kc8, record->event.pressed);
    return false;
}
