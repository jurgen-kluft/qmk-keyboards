#include QMK_KEYBOARD_H
#include "layers.h"
#include "oneshot.h"
#include "cushi.h"
#include "cukey.h"
#include "feature.h"
#include "cheng.h"
#include "user_leader.h"

#ifdef OLED_ENABLE
#include "oled.h"
#endif

#if (__has_include("secrets.x") && !defined(NO_SECRETS))
#include "secrets.x"
static const char* gSecrets[] = {SECRET_1, SECRET_2, SECRET_3, SECRET_4, SECRET_5, SECRET_6, SECRET_7, SECRET_8};
#else
static const char* gSecrets[] = {"SECRET_1", "SECRET_2", "SECRET_3", "SECRET_4", "SECRET_5", "SECRET_6", "SECRET_7", "SECRET_8"};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
#ifdef OLED_DRIVER_ENABLE
    process_record_oled(keycode, record);
#endif

    if (process_record_cheng(keycode, record))
        return false;

    switch (keycode)
    {
        case KC_OS_UNDO ... KC_OS_CLOSE:
        {
            if (!process_cushi_keys(keycode, record))
                return false;

            if (record->event.pressed)
            {
                keycode = process_cukey(keycode);
                if (keycode != KC_NO)
                    tap_code16(keycode);
            }

            return false;
        }
        case KC_SECRET_1 ... KC_SECRET_8: // Secrets!  Externally defined strings, not stored in repo
            if (!record->event.pressed)
            {
                turnoff_oneshot_modifiers();
                send_string_with_delay(gSecrets[keycode - KC_SECRET_1], MACRO_TIMER);
            }
            return false;
            break;
        case KC_OLED:
            if (record->event.pressed)
            {
#ifdef OLED_ENABLE
                toggle_display_oled();
#endif
#ifdef RGBLIGHT_ENABLE
                rgblight_enable();
#endif
            }
            return true;
    }

    if (!process_feature_key(keycode, record))
    {
        return false;
    }

    if (!process_cushi_keys(keycode, record))
    {
        return false;
    }

    update_oneshot_modifiers(keycode, record);

    switch (keycode)
    {
        case KC_QWERTY:
            if (record->event.pressed)
            {
                set_single_persistent_default_layer(_QWERTY);
            }
            break;
        case KC_RSTHD:
            if (record->event.pressed)
            {
                set_single_persistent_default_layer(_RSTHD);
            }
            break;
    }

    if (process_leader_user(keycode, record))
        return false;

    return true;
}
