#include QMK_KEYBOARD_H
#include "cukey.h"
#include "oneshot.h"

#ifdef ENABLE_ONESHOT

bool is_oneshot_modifier_cancel_key(uint16_t keycode, bool pressed)
{
    switch (keycode)
    {
        case KC_FNAV:
        case KC_FCAPS: return pressed;
    }
    return false;
}

bool is_oneshot_modifier_ignored_key(uint16_t keycode, bool pressed)
{
    switch (keycode)
    {
        case KC_FNAV:
        case KC_FSYM: return true;
    }
    return false;
}

oneshot_mod get_modifier_for_trigger_key(uint16_t keycode)
{
    switch (keycode)
    {
        case OS_CTRL:
        case OS_SHFT:
        case OS_ALT:
        case OS_CMD: return (keycode - OS_CTRL) + ONESHOT_LCTL;
    }
    return ONESHOT_NONE;
}

#endif
