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

#define CHORD1(sc1)                (((uint32_t)1 << sc1))
#define CHORD2(sc1, sc2)           (((uint32_t)1 << sc1) | ((uint32_t)1 << sc2))
#define CHORD3(sc1, sc2, sc3)      (((uint32_t)1 << sc1) | ((uint32_t)1 << sc2) | ((uint32_t)1 << sc3))
#define CHORD4(sc1, sc2, sc3, sc4) (((uint32_t)1 << sc1) | ((uint32_t)1 << sc2) | ((uint32_t)1 << sc3) | ((uint32_t)1 << sc4))

#if 0

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

#if 0
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

#if 0
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

static uint16_t chord_to_keycodex(uint32_t scx)
{
    uint16_t keycode = KC_NO;
    switch (scx)
    {
        case CHORD1((SC_SCN - SC_BEGIN)): keycode = KC_SCLN; break;
        case CHORD1((SC_SPC - SC_BEGIN)): keycode = KC_SPACE; break;
        case CHORD1((SC_BPC - SC_BEGIN)): keycode = KC_BSPACE; break;
        case CHORD1((SC_CMA - SC_BEGIN)): keycode = KC_COMMA; break;
        case CHORD1((SC_DOT - SC_BEGIN)): keycode = KC_DOT; break;
        case CHORD1((SC_SLS - SC_BEGIN)): keycode = KC_SLASH; break;
        case CHORD2((SC_F - SC_BEGIN), (SC_J - SC_BEGIN)): keycode = KC_ENTER; break;
        case CHORD2((SC_F - SC_BEGIN), (SC_K - SC_BEGIN)): keycode = KC_ESC; break;
        case CHORD2((SC_F - SC_BEGIN), (SC_L - SC_BEGIN)): keycode = KC_BSPACE; break;
        case CHORD3((SC_D - SC_BEGIN), (SC_F - SC_BEGIN), (SC_J - SC_BEGIN)): keycode = KC_LPRN; break;
        case CHORD3((SC_D - SC_BEGIN), (SC_F - SC_BEGIN), (SC_K - SC_BEGIN)): keycode = KC_RPRN; break;
        case CHORD4((SC_J - SC_BEGIN), (SC_K - SC_BEGIN), (SC_D - SC_BEGIN), (SC_F - SC_BEGIN)): keycode = KC_SPACE; break;
    }
    return keycode;
}

static uint16_t chord_current_keycode = KC_NO;
static uint16_t chord_current_timer   = 0;
static uint32_t chord_current_nkeys   = 0;
static uint32_t chord_scanned_nkeys   = 0;
static uint32_t chord_current_bits    = 0;
static uint32_t chord_scanned_bits    = 0;
static uint32_t chord_used_bits       = 0;

#define CHORD_TIMEOUT 60

bool process_record_cheng(uint16_t keycode, keyrecord_t* record)
{
    if (keycode >= SC_BEGIN && keycode <= SC_END)
    {
        if (chord_current_keycode != KC_NO)
        {
            unregister_code16(chord_current_keycode);
            chord_current_keycode = KC_NO;
        }

        chord_current_timer = timer_read();
        int8_t bit          = keycode - SC_BEGIN;
        if (record->event.pressed)
        {
            chord_current_nkeys++;
            chord_current_bits |= ((uint32_t)1 << bit);
        }
        else
        {
            chord_current_nkeys--;

            if ((chord_used_bits & ((uint32_t)1 << bit)) != 0)
            {
                chord_used_bits &= ~((uint32_t)1 << bit);
                chord_current_bits &= ~((uint32_t)1 << bit);
            }
            else
            {
                chord_current_bits &= ~((uint32_t)1 << bit);
                uint16_t kc = chord_key_to_keycode(keycode);
                register_code16(kc);
                unregister_code16(kc);
            }
        }
        return true;
    }
    return false;
}

void matrix_init_user(void)
{
    chord_current_keycode = KC_NO;
    chord_current_bits    = 0;
    chord_scanned_bits    = 0;
    chord_current_timer   = 0;
}

void matrix_scan_user(void)
{
    // if we have more than one key that is pressed and the timer has expired
    // then we register the chord
    if (chord_scanned_bits != chord_current_bits)
    {
        chord_scanned_bits  = chord_current_bits;
        chord_scanned_nkeys = chord_current_nkeys;
        chord_current_timer = timer_read();
    }
    if (chord_scanned_nkeys >= 1 && (timer_elapsed(chord_current_timer) >= 100))
    {
        if (chord_used_bits != chord_scanned_bits)
        {
            uint16_t keycode = chord_to_keycodex(chord_scanned_bits);
            if (keycode != KC_NO)
            {
                register_code16(keycode);
                chord_current_keycode = keycode;
                chord_current_timer   = timer_read();
                chord_used_bits = chord_scanned_bits;
            }
        }
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