#include QMK_KEYBOARD_H
#include "config.h"
#include "feature.h"
#include "oneshot.h"
#include "user_keycodes.h"

#ifdef ENABLE_ONESHOT

bool is_oneshot_modifier_cancel_key(uint16_t keycode, bool pressed)
{
    switch (keycode)
    {
        case CC_FNAV:
        case CC_FCAPS: return pressed;
    }
    return false;
}

bool is_oneshot_modifier_ignored_key(uint16_t keycode, bool pressed)
{
    switch (keycode) {
        case KC_HOME:
        case KC_END:
        case KC_PGUP:
        case KC_PGDOWN:
        case KC_LEFT:
        case KC_RIGHT:
        case KC_UP:
        case KC_DOWN: return true;
        
        case CC_FNUM: return true; 
        case CC_FSYM: return true; 
        case CC_FNAV:
        case CC_FCAPS: return true;
    }
    return false;
}

oneshot_mod get_modifier_for_trigger_key(uint16_t keycode)
{
    switch (keycode)
    {
        case CC_CTRL:
        case CC_SHFT:
        case CC_ALT:
        case CC_CMD: return (keycode - CC_CTRL) + ONESHOT_LCTL;
    }
    return ONESHOT_NONE;
}


#endif

