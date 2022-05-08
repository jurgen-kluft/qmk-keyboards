#define ENABLE_ONESHOT
#ifdef ENABLE_ONESHOT
#pragma once

// Note: the order of the enums is important, do not change it!
typedef enum
{
    ONESHOT_LCTL      = 0,
    ONESHOT_LSFT      = 1,
    ONESHOT_LALT      = 2,
    ONESHOT_LGUI      = 3,
    //ONESHOT_RCTL      = 4,
    //ONESHOT_RSFT      = 5,
    //ONESHOT_RALT      = 6,
    //ONESHOT_RGUI      = 7,
    ONESHOT_COUNT,
    ONESHOT_NONE      = ONESHOT_COUNT,
} oneshot_mod;

// This function should be called inside proces_record_user and does everything needed to get one shot modifiers working.
void update_oneshot_modifiers(uint16_t keycode, keyrecord_t* record);

// Call this to turn off (release) all modifiers
void turnoff_oneshot_modifiers(void);

void press_oneshot_modifier(oneshot_mod osmod);
void release_oneshot_modifier(oneshot_mod osmod);

// TO BE IMPLEMENTED BY THE USER
// This function should return one of the oneshot_mod enumerations (see keymap.c implementation)
oneshot_mod get_modifier_for_trigger_key(uint16_t keycode);

// TO BE IMPLEMENTED BY THE USER
// This function should return true for keycodes that must be ignored in the oneshot modifier behaviour.
// You probably want to ignore layer keys. Trigger keys don't need to be specified here.
bool is_oneshot_modifier_ignored_key(uint16_t keycode, bool pressed);

// TO BE IMPLEMENTED BY THE USER
// This function should return true for keycodes that should reset all oneshot modifiers.
bool is_oneshot_modifier_cancel_key(uint16_t keycode, bool pressed);

#else

void update_oneshot_modifiers(uint16_t keycode, keyrecord_t* record) {}

#endif