#include QMK_KEYBOARD_H

#include "oneshot.h"

#ifdef ENABLE_ONESHOT

// The original implementation was written by Tom (@tvlerber)
// You can find it here: https://gitlab.com/tvlerber/qmk/-/blob/my-qmk/users/tvlerber/tomsosms.c

// the basic states a oneshot modifier can be in
typedef enum
{
    ONESHOT_STATE_OFF         = 0,
    ONESHOT_STATE_PRESSED     = 1,
    ONESHOT_STATE_QUEUED      = 2,
    ONESHOT_STATE_LOCK        = 3,
    ONESHOT_STATE_END_PRESSED = 4,
} oneshot_state;

// ONESHOT_STATE_OFF          => ONESHOT_STATE_PRESSED       , 0 => 1
// ONESHOT_STATE_PRESSED      => ONESHOT_STATE_QUEUED        , 1 => 2
// ONESHOT_STATE_QUEUED       => ONESHOT_STATE_LOCK          , 2 => 3
// ONESHOT_STATE_LOCK         => ONESHOT_STATE_END_PRESSED   , 3 => 4
// ONESHOT_STATE_END_PRESSED  => ONESHOT_STATE_OFF           , 4 => 0
//
// oneshot_state modifiers_state_transitions_normal[5] = {ONESHOT_STATE_PRESSED, ONESHOT_STATE_QUEUED, ONESHOT_STATE_LOCK, ONESHOT_STATE_END_PRESSED, ONESHOT_STATE_END_PRESSED};
//

static oneshot_state modifiers_with_state[ONESHOT_MOD_COUNT] = {
    ONESHOT_STATE_OFF, ONESHOT_STATE_OFF, ONESHOT_STATE_OFF, ONESHOT_STATE_OFF, ONESHOT_STATE_OFF, ONESHOT_STATE_OFF, ONESHOT_STATE_OFF, ONESHOT_STATE_OFF,
};

// oneshot mods always get registered immediately to the operating system, but we also
// need to keep track if the mod(s) got combined with a normal key (applied)
static bool unapplied_mods_present = false;

// keycode of the last pressed 'normal' key which haven't been released yet
static uint16_t repeating_normal_key = 0;

// utility functions (implemented at the bottom of this file)
static void   set_modifier_state(oneshot_mod osmod, oneshot_state new_state);
static int8_t set_modifier_state_all(oneshot_state new_state);
static void   set_modifier_state_all_from_to(oneshot_state oneshot_state_from, oneshot_state oneshot_state_to);
static bool   all_modifiers_are_off(void);

int8_t turnoff_oneshot_modifiers() { return set_modifier_state_all(ONESHOT_STATE_OFF); }

// see comment in corresponding headerfile
void update_oneshot_modifiers(uint16_t keycode, keyrecord_t* record)
{
    // cancel keys
    if (is_oneshot_modifier_cancel_key(keycode, record->event.pressed))
    {
        unapplied_mods_present = false;
        set_modifier_state_all(ONESHOT_STATE_OFF);
        return;
    }

    // ignored keys
    if (is_oneshot_modifier_ignored_key(keycode, record->event.pressed))
    {
        return;
    }

    oneshot_mod osmod = get_modifier_for_trigger_key(keycode);

    // trigger keys
    if (osmod != ONESHOT_NONE)
    {
        oneshot_state state = modifiers_with_state[osmod];
        if (record->event.pressed)
        {
            if (state == ONESHOT_STATE_OFF)
            {
                unapplied_mods_present = (repeating_normal_key == 0);
            }
            // oneshot_state tostate = modifiers_state_transitions_normal[state];
            oneshot_state tostate = (state + 1);
            set_modifier_state(osmod, tostate);
        }
        else
        {
            if (state == ONESHOT_STATE_PRESSED)
            {
                if (!unapplied_mods_present)
                {
                    set_modifier_state(osmod, ONESHOT_STATE_OFF);
                }
                else
                {
                    set_modifier_state(osmod, ONESHOT_STATE_QUEUED);
                }
            }
            else if (state >= ONESHOT_STATE_END_PRESSED)
            {
                set_modifier_state(osmod, ONESHOT_STATE_OFF);
            }
        }
    }
    // normal keys
    else
    {
        if (record->event.pressed)
        {
            if (!all_modifiers_are_off())
            {
                if (unapplied_mods_present)
                {
                    unapplied_mods_present = false;
                }
                else
                {
                    unregister_code(repeating_normal_key);
                    set_modifier_state_all_from_to(ONESHOT_STATE_QUEUED, ONESHOT_STATE_OFF);
                }
            }
            repeating_normal_key = keycode;
        }
        else
        {
            if (!all_modifiers_are_off())
            {
                unregister_code(keycode);
                set_modifier_state_all_from_to(ONESHOT_STATE_QUEUED, ONESHOT_STATE_OFF);
            }
            repeating_normal_key = 0;
        }
    }
}

// implementation of utility functions

// registers/unregisters a mod to the operating system on state change if necessary
void update_modifier(oneshot_mod osmod, oneshot_state previous_state, oneshot_state current_state)
{
    if (previous_state == ONESHOT_STATE_OFF)
    {
        register_code(KC_LCTRL + osmod);
    }
    else
    {
        if (current_state == ONESHOT_STATE_OFF)
        {
            unregister_code(KC_LCTRL + osmod);
        }
    }
}

void set_modifier_state(oneshot_mod osmod, oneshot_state new_state)
{
    oneshot_state previous_state = modifiers_with_state[osmod];
    if (previous_state != new_state)
    {
        modifiers_with_state[osmod] = new_state;
        update_modifier(osmod, previous_state, new_state);
    }
}

int8_t set_modifier_state_all(oneshot_state new_state)
{
    int8_t c = 0;
    for (int8_t i = 0; i < ONESHOT_MOD_COUNT; i++)
    {
        oneshot_state previous_state = modifiers_with_state[i];
        if (previous_state != new_state)
        {
            modifiers_with_state[i] = new_state;
            update_modifier(i, previous_state, new_state);
            c += 1;
        }
    }
    return c;
}

void set_modifier_state_all_from_to(oneshot_state oneshot_state_from, oneshot_state oneshot_state_to)
{
    for (int8_t i = 0; i < ONESHOT_MOD_COUNT; i++)
    {
        if (modifiers_with_state[i] == oneshot_state_from)
        {
            modifiers_with_state[i] = oneshot_state_to;
            update_modifier(i, oneshot_state_from, oneshot_state_to);
        }
    }
}

bool all_modifiers_are_off()
{
    for (int8_t i = 0; i < ONESHOT_MOD_COUNT; i++)
    {
        if (modifiers_with_state[i] != ONESHOT_STATE_OFF)
        {
            return false;
        }
    }
    return true;
}

#endif
