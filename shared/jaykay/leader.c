#include QMK_KEYBOARD_H
#include "leader.h"
#include "cukey.h"

/*
Leader

When pressing/releasing FNAV we start a timer and for each incoming key we reset the timer.
Timing out will resolve the key chain and see if there is a combination that needs to be
executed.

e.g.
FNAV -> g -> m = gmail
FNAV -> h -> m = hotmail
FNAV -> p -> w = password
FNAV -> c -> m = comma
FNAV -> c -> l = colon
FNAV -> q -> m = question mark
FNAV -> e -> m = exclamation mark
FNAV -> e -> q = equal
*/
static uint8_t  leader_active   = 0;
static uint16_t leader_timer    = 0;
static uint8_t  leader_chain_recorded_pressed = 0;
static uint8_t  leader_chain_recorded_released = 0;
static uint16_t leader_chain[8] = {0};

#define LEADER_TIMEOUT (200)

static void reset_leader(void) {
  leader_active = 0;
  leader_timer = 0;
  leader_chain_recorded_pressed = 0;
  leader_chain_recorded_released = 0;
}

bool process_record_leader(uint16_t keycode, keyrecord_t* record)
{
    if (record->event.pressed)
    {
        if (keycode == KC_FNAV)
        {
            leader_active = 1;
            leader_timer = 0;
            leader_chain_recorded_pressed = 0;
            leader_chain_recorded_released = 0;
            leader_timer  = timer_read();
        }
        else if (leader_active == 2)
        {
            if ((leader_chain_recorded_pressed > 0) || (timer_elapsed(leader_timer) < LEADER_TIMEOUT))
            {
                leader_chain[leader_chain_recorded_pressed++] = keycode;
                leader_timer = timer_read();
                return true;
            }
            else
            {
                reset_leader();
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
            // if we release a key that is registered in the leader chain, we need to execute what is associated with the keys in the leader chain
            // e.g. FNAV -> g -> m = gmail

            // scan in the leader chain for the keycode that is released and if found increment leader_chain_recorded_released
            for (uint8_t i = 0; i < leader_chain_recorded_pressed; i++)
            {
                if (leader_chain[i] == keycode)
                {
                    leader_chain_recorded_released++;
                    break;
                }
            }

            if (leader_chain_recorded_pressed == 2 && leader_chain_recorded_released == 2)
            {
                reset_leader();

                if (leader_chain[0] == KC_G)
                {
                    if (leader_chain[1] == KC_M)
                    {
                        SEND_STRING("gmail");
                    }
                }
                else if (leader_chain[0] == KC_H)
                {
                    if (leader_chain[1] == KC_M)
                    {
                        SEND_STRING("hotmail");
                    }
                }
                else if (leader_chain[0] == KC_P)
                {
                    if (leader_chain[1] == KC_W)
                    {
                        SEND_STRING("password");
                    }
                }
                else if (leader_chain[0] == KC_C)
                {
                    if (leader_chain[1] == KC_M)
                    {
                        SEND_STRING(",");
                    }
                    else if (leader_chain[1] == KC_L)
                    {
                        SEND_STRING(":");
                    }
                }
                else if (leader_chain[0] == KC_Q)
                {
                    if (leader_chain[1] == KC_M)
                    {
                        SEND_STRING("?");
                    }
                }
                else if (leader_chain[0] == KC_E)
                {
                    if (leader_chain[1] == KC_M)
                    {
                        SEND_STRING("!");
                    }
                    else if (leader_chain[1] == KC_Q)
                    {
                        SEND_STRING("=");
                    }
                }
            }
            else if (leader_chain_recorded_pressed == 3 && leader_chain_recorded_released == 3)
            {
                reset_leader();

                if (leader_chain[0] == KC_K)
                {
                    if (leader_chain[1] == KC_A)
                    {
                        if (leader_chain[2] == KC_K)
                        {
                            SEND_STRING("www.kateandkimi.com");
                        }
                    }
                }
            }
        }
    }

    return false;
}
