#include QMK_KEYBOARD_H
#include "leader.h"
#include "cukey.h"

/*
Leader

When pressing/releasing FNAV we start a timer and for the first incoming key.
This leader implementation requires you to keep the first key pressed while you press the
rest of the leader chain. You could however hold a second key and release the first, the
main requirement is that you hold one or more keys of the full chain. Upon releasing all
keys the leader chain will be executed.
There is no timeout on finalizing the leader chain, only from FNAV and the next key.

e.g.
FNAV -> g -> m = jurgen.kluft@gmail.com
FNAV -> h -> m = jurgen_kluft@hotmail.com
FNAV -> p -> w = 608b7243a742-505a-9098
FNAV -> c -> m = ,
FNAV -> c -> l = :
FNAV -> q -> m = ?
FNAV -> e -> m = !
FNAV -> e -> q = =
*/
__attribute__((weak)) int8_t process_leader_chain(uint8_t count, uint8_t* leader_chain) { return -1; }
__attribute__((weak)) void   execute_leader_action(uint8_t action) {}

#define LEADER_TIMEOUT   (200)
#define LEADER_MAX_CHAIN (6)

static uint8_t  leader_active                  = 0;
static uint16_t leader_timer                   = 0;
static uint8_t  leader_chain_recorded_pressed  = 0;
static uint8_t  leader_chain_recorded_released = 0;
static uint8_t  leader_chain[LEADER_MAX_CHAIN] = {0};

static void reset_leader(void)
{
    leader_active                  = 0;
    leader_timer                   = 0;
    leader_chain_recorded_pressed  = 0;
    leader_chain_recorded_released = 0;
}

bool process_record_leader(uint16_t keycode, keyrecord_t* record)
{
    if (leader_active == 2)
    {
        if (keycode < KC_A && keycode > 0x80)
            return false;

        switch (keycode)
        {
            case OS_CTRL:
            case OS_SHFT:
            case OS_ALT:
            case OS_CMD:
            case KC_FSYM:
            case KC_FNUM:
            case KC_FCAPS: return false;
        }
    }

    if (record->event.pressed)
    {
        if (keycode == KC_FNAV)
        {
            leader_active                  = 1;
            leader_timer                   = 0;
            leader_chain_recorded_pressed  = 0;
            leader_chain_recorded_released = 0;
            leader_timer                   = timer_read();
        }
        else if (leader_active == 2)
        {
            if ((leader_chain_recorded_pressed == 0) && (timer_elapsed(leader_timer) >= LEADER_TIMEOUT))
            {
                reset_leader();
            }
            else
            {
                leader_chain[leader_chain_recorded_pressed++] = keycode;
                leader_timer                                  = timer_read();

                uint8_t action = process_leader_chain(leader_chain_recorded_pressed, leader_chain);
                return action != -1;
            }
        }
        else
        {
            leader_active = 0;
        }
    }
    else
    {
        if (keycode == KC_FNAV)
        {
            leader_active = leader_active << 1;
            leader_timer  = timer_read();
        }
        else if (leader_active == 2)
        {
            // scan in the leader chain for the keycode that is released and if found increment leader_chain_recorded_released
            for (uint8_t i = 0; i < leader_chain_recorded_pressed; i++)
            {
                if (leader_chain[i] == keycode)
                {
                    leader_chain_recorded_released++;
                    break;
                }
            }

            if (leader_chain_recorded_released == leader_chain_recorded_pressed)
            {
                uint8_t leader_action = process_leader_chain(leader_chain_recorded_pressed, leader_chain);
                if (leader_action > 0)
                {
                    execute_leader_action(leader_action);
                    reset_leader();
                }
            }
        }
    }

    return false;
}
