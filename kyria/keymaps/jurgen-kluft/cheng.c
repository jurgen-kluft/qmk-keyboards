#include QMK_KEYBOARD_H
#include "cheng.h"
#include "cukey.h"

#define CHENG_ENABLE

#ifdef CHENG_ENABLE

#define static_assert(bExpression, msg) typedef uint8_t assert_failed[(bExpression) ? 1 : -1]
static_assert(sizeof(bool) == sizeof(uint8_t), "bool is not 1 byte");
static_assert(sizeof(bool*) == 2, "pointer is not 4 bytes");

// A chord is a sequence of keys that are pressed at the same time.
// They result in a dedicated keycode for that chord:
// e.g. SC_A | SC_S = KC_ASTR, *

#if 1
static uint16_t chord_key_to_keycode(uint16_t sc)
{
    uint16_t keycode = sc;
    switch (sc)
    {
        case SC_A ... SC_Z: keycode = KC_A + (sc - SC_BEGIN); break;
        case SC_SCN: keycode = KC_SCLN; break;
        case SC_SPC: keycode = KC_SPACE; break;
        case SC_BPC: keycode = KC_BSPACE; break;
        case SC_CMA: keycode = KC_COMMA; break;
        case SC_DOT: keycode = KC_DOT; break;
        case SC_SLS: keycode = KC_SLASH; break;
    }
    return keycode;
}
#endif

#if 1
#define CHORD2(sc1, sc2) (((uint32_t)1 << sc1) | ((uint32_t)1 << sc2))

static uint16_t chord_to_keycode2(uint8_t sc1, uint8_t sc2)
{
    uint16_t keycode = KC_NO;
    uint32_t regoc   = CHORD2(sc1, sc2);
    switch (regoc)
    {
        case CHORD2((SC_F - SC_BEGIN), (SC_J - SC_BEGIN)): keycode = KC_ENTER; break;
        case CHORD2((SC_F - SC_BEGIN), (SC_K - SC_BEGIN)): keycode = KC_ESC; break;
        case CHORD2((SC_F - SC_BEGIN), (SC_L - SC_BEGIN)): keycode = KC_BSPACE; break;
    }
    return keycode;
}
#endif

#if 1
#define CHORD3(sc1, sc2, sc3) (((uint32_t)1 << sc1) | ((uint32_t)1 << sc2) | ((uint32_t)1 << sc3))
static uint16_t chord_to_keycode3(uint8_t sc1, uint8_t sc2, uint8_t sc3)
{
    uint16_t keycode = KC_NO;
    uint32_t regoc   = CHORD3(sc1, sc2, sc3);
    switch (regoc)
    {
        case CHORD3((SC_D - SC_BEGIN), (SC_F - SC_BEGIN), (SC_J - SC_BEGIN)): keycode = KC_LPRN; break;
        case CHORD3((SC_D - SC_BEGIN), (SC_F - SC_BEGIN), (SC_K - SC_BEGIN)): keycode = KC_RPRN; break;
    }
    return keycode;
}
#endif

#if 1
#define CHORD4(sc1, sc2, sc3, sc4) (((uint32_t)1 << sc1) | ((uint32_t)1 << sc2) | ((uint32_t)1 << sc3) | ((uint32_t)1 << sc4))
static uint16_t chord_to_keycode4(uint8_t sc1, uint8_t sc2, uint8_t sc3, uint8_t sc4)
{
    uint16_t keycode = KC_NO;
    uint32_t regoc   = CHORD4(sc1, sc2, sc3, sc4);
    switch (regoc)
    {
        case CHORD4((SC_J - SC_BEGIN), (SC_K - SC_BEGIN), (SC_D - SC_BEGIN), (SC_F - SC_BEGIN)): keycode = KC_SPACE; break;
    }
    return keycode;
}
#endif

/*

You register an incoming key press and set an expiration time N1. When N1 ms has passed
you register the key and remove it from the list of pressed keys.
When another key is pressed within the N1 ms you mark it as a chord and delay the expiration
time by N2 ms. The 3rd key now needs to register before the new expiration time.
If the 3rd key comes in then the expiration time is pushed N3 ms into the future so that the
4th key can come in.
If the 4th key does not arrive in time then the current chord is resolved and registered.

The total time window of chord should not exceed NC ms, this means from the time of the first
registered key to the actual recognition of a chord.
The 1st, 2nd and 3rd key could come in very rapidly, within for example 20 ms. That means that
the timer after the 3rd key will be 30 ms.

If a key is released it is removed from 'hold', or if it is part of the current chord the bit
is removed. If the current chord ends up with less than 2 keys then the whold chord is deactivated.
However, if the chord still has 2 or more keys pressed then the timer is set to NC ms again.

Example:
Key 1 comes in and timer is set to NC ms
N = 50 ms, key 2 comes in after 10 ms
N = 40 ms, key 3 comes in after 15 ms
N = 25 ms, no further key comes in and the chord is registered after 25 ms

*/
static uint16_t chord_current_etime          = 0;
static uint8_t  chord_current_timeout        = 0;
static int8_t   chord_current_pkeys_count    = 0;
static uint16_t chord_current_pkeys[16]      = {0};
static uint16_t chord_current_pkeys_time[16] = {0};
static int8_t   chord_current_rkeys_count    = 0;
static uint16_t chord_current_rkeys[16]      = {0};

#define CHORD_TIMEOUT 60

bool process_record_cheng(uint16_t keycode, keyrecord_t* record)
{
    if (keycode >= SC_BEGIN && keycode <= SC_END)
    {
        if (record->event.pressed)
        {
            uint16_t timer = timer_read();

            int8_t u = 0;
            if (chord_current_pkeys_count == 0)
            {
                chord_current_timeout                               = 30;
                chord_current_etime                                 = timer;
                chord_current_pkeys_time[chord_current_pkeys_count] = timer;
                chord_current_pkeys[chord_current_pkeys_count++]    = keycode;
            }
            else if (chord_current_pkeys_count == 1)
            {
                if ((timer - chord_current_etime) > chord_current_timeout)
                {
                    u = 1;
                }
                else
                {
                    chord_current_etime                                 = timer;
                    chord_current_timeout                               = 30;
                    chord_current_pkeys_time[chord_current_pkeys_count] = timer;
                    chord_current_pkeys[chord_current_pkeys_count++]    = keycode;
                }
            }
            else if (chord_current_pkeys_count == 2)
            {
                if (timer - chord_current_etime > chord_current_timeout)
                {
                    u = 2;
                }
                else
                {
                    chord_current_etime                                 = timer;
                    chord_current_timeout                               = 30;
                    chord_current_pkeys_time[chord_current_pkeys_count] = timer;
                    chord_current_pkeys[chord_current_pkeys_count++]    = keycode;
                }
            }
            else if (chord_current_pkeys_count == 3)
            {
                if (timer - chord_current_etime > chord_current_timeout)
                {
                    u = 3;
                }
                else
                {
                    chord_current_pkeys_time[chord_current_pkeys_count] = timer;
                    chord_current_pkeys[chord_current_pkeys_count++]    = keycode;
                }
            }

            if (u > 0)
            {
                int8_t i = 0;
                while (i < u)
                {
                    uint16_t kc = chord_key_to_keycode(chord_current_pkeys[i]);
                    register_code16(kc);
                    chord_current_rkeys[chord_current_rkeys_count++] = chord_current_pkeys[i];
                    i += 1;
                }
                chord_current_pkeys_count -= u;
                while (i < chord_current_pkeys_count)
                {
                    chord_current_pkeys[i]      = chord_current_pkeys[i + u];
                    chord_current_pkeys_time[i] = chord_current_pkeys_time[i + u];
                    i++;
                }
                if (chord_current_pkeys_count > 0)
                {
                    chord_current_etime = chord_current_pkeys_time[0];
                }
            }
        }
        else
        {
            for (int8_t i = 0; i < chord_current_pkeys_count; i++)
            {
                if (chord_current_pkeys[i] == keycode)
                {
                    uint16_t kc = chord_key_to_keycode(keycode);
                    register_code16(kc);
                    chord_current_rkeys[chord_current_rkeys_count++] = keycode;

                    chord_current_etime = chord_current_pkeys_time[i];

                    chord_current_pkeys_count--;
                    while (i < chord_current_pkeys_count)
                    {
                        chord_current_pkeys[i] = chord_current_pkeys[i + 1];
                        i++;
                    }
                    break;
                }
            }

            for (int8_t i = 0; i < chord_current_rkeys_count; i++)
            {
                if (chord_current_rkeys[i] == keycode)
                {
                    uint16_t kc = chord_key_to_keycode(keycode);
                    unregister_code16(kc);

                    chord_current_rkeys_count--;
                    while (i < chord_current_rkeys_count)
                    {
                        chord_current_rkeys[i] = chord_current_rkeys[i + 1];
                        i++;
                    }
                    break;
                }
            }

            if (chord_current_pkeys_count > 1)
            {
                chord_current_etime = timer_read() + CHORD_TIMEOUT;
            }
            else
            {
                chord_current_etime = 0;
            }
        }
        return true;
    }
    return false;
}

void matrix_init_user(void)
{
    chord_current_pkeys_count = 0;
    chord_current_rkeys_count = 0;
    chord_current_etime       = 0;
}

void matrix_scan_user(void)
{
    // if we have more than one key that is pressed and the timer has expired
    // then we register the chord
    if (chord_current_pkeys_count > 1 && (timer_elapsed(chord_current_etime) >= chord_current_timeout))
    {
        uint16_t keycode = KC_NO;
        if (chord_current_pkeys_count == 2)
        {
            keycode = chord_to_keycode2((uint8_t)(chord_current_pkeys[0] - SC_BEGIN), (uint8_t)(chord_current_pkeys[1] - SC_BEGIN));
        }
        else if (chord_current_pkeys_count == 3)
        {
            keycode = chord_to_keycode3((uint8_t)(chord_current_pkeys[0] - SC_BEGIN), (uint8_t)(chord_current_pkeys[1] - SC_BEGIN), (uint8_t)(chord_current_pkeys[2] - SC_BEGIN));
        }
        else if (chord_current_pkeys_count == 4)
        {
            keycode = chord_to_keycode4((uint8_t)(chord_current_pkeys[0] - SC_BEGIN), (uint8_t)(chord_current_pkeys[1] - SC_BEGIN), (uint8_t)(chord_current_pkeys[2] - SC_BEGIN),
                                        (uint8_t)(chord_current_pkeys[3] - SC_BEGIN));
        }
        if (keycode != KC_NO)
        {
            register_code(keycode);

            // We actually need to unregister at the moment we release one of the keys of the chord, in that way we have repeating on the chord
            unregister_code(keycode);
        }

        chord_current_pkeys_count = 0;
        chord_current_etime       = 0;
    }
}

#else

bool process_record_cheng(uint16_t keycode, keyrecord_t* record)
{
    if (keycode >= SC_BEGIN && keycode <= SC_END)
    {
        return true;
    }
    return false;
}

#endif