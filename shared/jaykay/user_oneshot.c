#include QMK_KEYBOARD_H
#include "config.h"
#include "feature.h"
#include "oneshot.h"
#include "user_keycodes.h"

#ifdef ENABLE_ONESHOT

bool is_oneshot_modifier_cancel_key(uint8_t keycode, bool pressed)
{
    switch (keycode)
    {
        case CC_FNAV:
        case CC_FCAPS: return pressed;
    }
    return false;
}

bool is_oneshot_modifier_ignored_key(uint8_t keycode, bool pressed)
{
    if (keycode >= CC_RANGE_START && keycode <= CC_RANGE_END)
        return true;
    return false;
}

oneshot_mod get_modifier_for_trigger_key(uint8_t keycode)
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

