// ISBN: 3 89028 035 8
// ISBN: 0 13 566423 3

#if __has_include("typos_dictionary.gen")

#include QMK_KEYBOARD_H
#include "user_keycodes.h"
#include "correction.h"

#include "typos_dictionary.gen"

static uint8_t typo_buffer[CORREX_MAX_LEN] = {KC_SPC};
static uint8_t typo_buffer_size            = 1;

bool autocorrect_is_enabled(void) { return userspace_config.autocorrection; }

void autocorrect_enable(void)
{
    userspace_config.autocorrection = true;
    eeconfig_update_user(userspace_config.raw);
}

void autocorrect_disable(void)
{
    userspace_config.autocorrection = false;
    typo_buffer_size                = 0;
    eeconfig_update_user(userspace_config.raw);
}

void autocorrect_toggle(void)
{
    userspace_config.autocorrection = !userspace_config.autocorrection;
    typo_buffer_size                = 0;
    eeconfig_update_user(userspace_config.raw);
}

__attribute__((weak)) bool process_autocorrect_user(uint16_t* keycode, keyrecord_t* record, uint8_t* typo_buffer_size, uint8_t* mods)
{
    // See quantum_keycodes.h for reference on these matched ranges.
    switch (*keycode)
    {
        // Exclude these keycodes from processing.
        case KC_LSFT:
        case KC_RSFT:
        case KC_CAPS:
            return false;

        // Mask for base keycode from shifted keys.
        case QK_LSFT ... QK_LSFT + 255:
        case QK_RSFT ... QK_RSFT + 255:
            if (*keycode >= QK_LSFT && *keycode <= (QK_LSFT + 255))
            {
                *mods |= MOD_LSFT;
            }
            else
            {
                *mods |= MOD_RSFT;
            }
            *keycode &= 0xFF; // Get the basic keycode.
            return true;
    }

    // Disable autocorrect while a mod other than shift is active.
    if ((*mods & ~MOD_MASK_SHIFT) != 0)
    {
        *typo_buffer_size = 0;
        return false;
    }

    return true;
}

__attribute__((weak)) bool apply_autocorrect(uint8_t backspaces, const char* str) { return true; }

bool process_autocorrection(uint16_t keycode, keyrecord_t* record)
{
    uint8_t mods = get_mods();

    if ((keycode >= CC_AUTOCORRECT_ON && keycode <= CC_AUTOCORRECT_TOGGLE) && record->event.pressed)
    {
        if (keycode == CC_AUTOCORRECT_ON)
        {
            autocorrect_enable();
        }
        else if (keycode == CC_AUTOCORRECT_OFF)
        {
            autocorrect_disable();
        }
        else if (keycode == CC_AUTOCORRECT_TOGGLE)
        {
            autocorrect_toggle();
        }
        else
        {
            return true;
        }
        return false;
    }

    if (!autocorrect_is_enabled())
    {
        typo_buffer_size = 0;
        return true;
    }

    if (!record->event.pressed)
    {
        return true;
    }

    // autocorrect keycode verification and extraction
    if (!process_autocorrect_user(&keycode, record, &typo_buffer_size, &mods))
    {
        return true;
    }

    // keycode buffer check
    switch (keycode)
    {
        case KC_A ... KC_Z:
            // process normally
            break;
        case KC_1 ... KC_0:
        case KC_TAB ... KC_SEMICOLON:
        case KC_GRAVE ... KC_SLASH:
            // Set a word boundary if space, period, digit, etc. is pressed.
            keycode = KC_SPC;
            break;
        case KC_ENTER:
            // Behave more conservatively for the enter key. Reset, so that enter
            // can't be used on a word ending.
            typo_buffer_size = 0;
            keycode          = KC_SPC;
            break;
        case KC_BSPC:
            // Remove last character from the buffer.
            if (typo_buffer_size > 0)
            {
                --typo_buffer_size;
            }
            return true;
        case KC_QUOTE:
            // Treat " (shifted ') as a word boundary.
            if ((mods & MOD_MASK_SHIFT) != 0)
            {
                keycode = KC_SPC;
            }
            break;
        default:
            // Clear state if some other non-alpha key is pressed.
            typo_buffer_size = 0;
            return true;
    }

    // Rotate oldest character if buffer is full.
    if (typo_buffer_size >= CORREX_MAX_LEN)
    {
        memmove(typo_buffer, typo_buffer + 1, CORREX_MAX_LEN - 1);
        typo_buffer_size = CORREX_MAX_LEN - 1;
    }

    // Append `keycode` to buffer.
    typo_buffer[typo_buffer_size++] = keycode;
    // Return if buffer is smaller than the shortest word.
    if (typo_buffer_size < CORREX_MIN_LEN)
    {
        return true;
    }

    uint16_t state = 0;
    uint8_t  code  = pgm_read_byte(autocorrect_data + state);
    for (int8_t i = typo_buffer_size - 1; i >= 0; --i)
    {
        uint8_t const key_i = typo_buffer[i];

        /*
        qmk:

#    define pgm_read_byte(address_short) *((uint8_t*)(address_short))
#    define pgm_read_word(address_short) *((uint16_t*)(address_short))
#    define pgm_read_dword(address_short) *((uint32_t*)(address_short))
#    define pgm_read_ptr(address_short) *((void**)(address_short))

        */

        if (code & 64)
        { // Check for match in node with multiple children.
            code &= 63;
            for (; code != key_i; code = pgm_read_byte(autocorrect_data + (state += 3)))
            {
                if (!code)
                    return true;
            }
            // Follow link to child node.
            state = (pgm_read_byte(autocorrect_data + state + 1) | pgm_read_byte(autocorrect_data + state + 2) << 8);
            // Check for match in node with single child.
        }
        else if (code != key_i)
        {
            return true;
        }
        else if (!(code = pgm_read_byte(autocorrect_data + (++state))))
        {
            ++state;
        }

        // Stop if `state` becomes an invalid index. This should not normally
        // happen, it is a safeguard in case of a bug, data corruption, etc.
        if (state >= DICTIONARY_SIZE)
        {
            return true;
        }

        code = pgm_read_byte(autocorrect_data + state);

        if (code & 128)
        { // A typo was found! Apply autocorrect.
            const uint8_t backspaces = (code & 63) + !record->event.pressed;
            if (apply_autocorrect(backspaces, (char const*)(autocorrect_data + state + 1)))
            {
                for (uint8_t i = 0; i < backspaces; ++i)
                {
                    tap_code(KC_BSPC);
                }
                send_string_P((char const*)(autocorrect_data + state + 1));
            }

            if (keycode == KC_SPC)
            {
                typo_buffer[0]   = KC_SPC;
                typo_buffer_size = 1;
                return true;
            }
            else
            {
                typo_buffer_size = 0;
                return false;
            }
        }
    }
    return true;
}

#else

// The following functions all have dummy implementations when autocorrect is disabled.

__attribute__((weak)) bool process_autocorrect_user(uint16_t* keycode, keyrecord_t* record, uint8_t* typo_buffer_size, uint8_t* mods) { return true; }

bool process_autocorrection(uint16_t keycode, keyrecord_t* record) { return true; }
bool apply_autocorrect(uint8_t backspaces, const char* str) { return true; }
bool autocorrect_is_enabled(void) { return false; }
void autocorrect_enable(void) {}
void autocorrect_disable(void) {}
void autocorrect_toggle(void) {}

#endif