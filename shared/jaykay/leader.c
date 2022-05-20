#include QMK_KEYBOARD_H
#include "config.h"
#include "feature.h"
#include "vim.h"
#include "user_keycodes.h"
#include "leader.h"

/*
Leader

When pressing/releasing 'FNAV' we start a timer for the first incoming key.
This leader implementation requires you to keep the first key pressed while you press the
rest of the leader chain. You could however hold a second key and release the first, the
main requirement is that you hold one or more keys of the full chain. Upon releasing all
keys the leader chain will be executed.
There is no timeout on finalizing the leader chain, only from FNAV to the first key.

Update: it has changed a little bit now, if the first key is part of a chain you can release
the first key. However if a key is part of a chain that has multiple lengths ('gt', 'gte') then
the 't' should be held if you want to get to the 'e' otherwise the 'gt' chain is recognized.

Note: We can still take it one step further. When we have the leader 'active', pressing SYM could
      change leader_mode for us. We could use that for lets say a 'accent' or 'vim' movement layer?

e.g.
FNAV -> p -> w = '608b7243a742-505a-9098'
FNAV -> g -> t = '>'
                 tap 'FNAV', quickly followed by a tap on 'g', you can now take your time to tap 't'
FNAV -> g -> t -> e = '>='
                 tap 'FNAV', quickly followed by a tap on 'g', you should now hold 't' and tap 'e' then
                 release 't'
*/

__attribute__((weak)) void execute_leader_action(uint8_t action, uint8_t mode, uint8_t count, uint8_t* leader_chain) {}
static int8_t              process_leader_chain(uint8_t count, uint8_t* keycodes, leader_config_t* config);

#define LEADER_TIMEOUT   (250)
#define LEADER_MAX_CHAIN (6)

static uint8_t  leader_active                  = 0;
static uint8_t  leader_mode                    = 0;
static uint16_t leader_timer                   = 0;
static uint8_t  leader_chain_recorded_pressed  = 0;
static uint8_t  leader_chain_recorded_released = 0;
static uint8_t  leader_chain[LEADER_MAX_CHAIN] = {0};

static void reset_leader(uint8_t active)
{
    leader_mode                    = 0;
    leader_active                  = active;
    leader_chain_recorded_pressed  = 0;
    leader_chain_recorded_released = 0;
    leader_timer                   = timer_read();
}

bool leader_is_active() { return (leader_active == 2) && timer_elapsed(leader_timer) < LEADER_TIMEOUT; }
void leader_disable() { reset_leader(0); }

bool process_record_leader(uint8_t keycode, keyrecord_t* record, leader_config_t* config0, leader_config_t* config1)
{
    if (leader_active == 2)
    {
        switch (keycode)
        {
            case CC_CTRL:
            case CC_SHFT:
            case CC_ALT:
            case CC_CMD:
            case CC_FNUM:
            case CC_FCAPS: return false;
        }
    }

    if (record->event.pressed)
    {
        if (keycode == CC_FNAV)
        {
            if (leader_chain_recorded_pressed > 0)
            {
                reset_leader(0);
            }
            else if (leader_active == 2 && timer_elapsed(leader_timer) < LEADER_TIMEOUT)
            {
                // we pressed FNAV twice in a very short time, this triggers a mode change
                leader_mode++;
            }
            else
            {
                reset_leader(1);
            }
        }
        else if (leader_active == 2)
        {
            // If KC_FSYM is tapped right after tapping KC_FNAV the mode changes into VIM mode
            if (keycode == CC_FSYM)
            {
                if ((leader_chain_recorded_pressed == 0) && (leader_mode == 0) && (timer_elapsed(leader_timer) < LEADER_TIMEOUT))
                {
                    // unused
                    reset_leader(0);
                }
                else
                {
                    reset_leader(0);
                }
            }
            else if ((leader_chain_recorded_pressed == 0) && (leader_mode == 0) && (timer_elapsed(leader_timer) >= LEADER_TIMEOUT))
            {
                reset_leader(0);
            }
            else
            {
                leader_chain[leader_chain_recorded_pressed++] = keycode;
                leader_timer                                  = timer_read();

                int8_t action;
                if (leader_mode == 1)
                {
                    action = process_leader_chain(leader_chain_recorded_pressed, leader_chain, config1);
                }
                else
                {
                    action = process_leader_chain(leader_chain_recorded_pressed, leader_chain, config0);
                }
                if (action == -2)
                {
                    reset_leader(0);
                    return false;
                }
                return true;
            }
        }
        else
        {
            leader_mode   = 0;
            leader_active = 0;
        }
    }
    else
    {
        if (keycode == CC_FNAV)
        {
            if (leader_active == 1)
                leader_active = 2;
            leader_timer = timer_read();
        }
        else if (keycode == CC_FSYM)
        {
            // nop
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
                int8_t leader_action;
                if (leader_mode == 1)
                {
                    leader_action = process_leader_chain(leader_chain_recorded_pressed, leader_chain, config1);
                }
                else
                {
                    leader_action = process_leader_chain(leader_chain_recorded_pressed, leader_chain, config0);
                }

                if (leader_action >= 0)
                {
                    execute_leader_action(leader_action, leader_mode, leader_chain_recorded_pressed, leader_chain);
                    reset_leader(0);
                }
            }
            return true;
        }
    }

    return false;
}

int8_t process_leader_chain(uint8_t count, uint8_t* keycodes, leader_config_t* config)
{
    if (count == 1)
    {
        if (config->leader1_array != NULL)
        {
            for (uint8_t i = 0; i < config->leader1_count; i++)
            {
                if (config->leader1_array[i].keycode1 == keycodes[0])
                {
                    return i;
                }
            }
        }
        if (config->leader2_array != NULL)
        {
            for (uint8_t i = 0; i < config->leader2_count; i++)
            {
                if (config->leader2_array[i].keycode1 == keycodes[0])
                {
                    return -1;
                }
            }
        }
        if (config->leader3_array != NULL)
        {
            for (uint8_t i = 0; i < config->leader3_count; i++)
            {
                if (config->leader3_array[i].keycode1 == keycodes[0])
                {
                    return -1;
                }
            }
        }
        if (config->leader4_array != NULL)
        {
            for (uint8_t i = 0; i < config->leader4_count; i++)
            {
                if (config->leader4_array[i].keycode1 == keycodes[0])
                {
                    return -1;
                }
            }
        }
    }
    else if (count == 2)
    {
        if (config->leader2_array != NULL)
        {
            for (uint8_t i = 0; i < config->leader2_count; i++)
            {
                if (config->leader2_array[i].keycode1 == keycodes[0] && config->leader2_array[i].keycode2 == keycodes[1])
                {
                    return i;
                }
            }
        }
        if (config->leader3_array != NULL)
        {
            for (uint8_t i = 0; i < config->leader3_count; i++)
            {
                if (config->leader3_array[i].keycode1 == keycodes[0] && config->leader3_array[i].keycode2 == keycodes[1])
                {
                    return -1;
                }
            }
        }
        if (config->leader4_array != NULL)
        {
            for (uint8_t i = 0; i < config->leader4_count; i++)
            {
                if (config->leader4_array[i].keycode1 == keycodes[0] && config->leader4_array[i].keycode2 == keycodes[1])
                {
                    return -1;
                }
            }
        }
    }
    else if (count == 3)
    {
        if (config->leader3_array != NULL)
        {
            for (uint8_t i = 0; i < config->leader3_count; i++)
            {
                if (config->leader3_array[i].keycode1 == keycodes[0] && config->leader3_array[i].keycode2 == keycodes[1] && config->leader3_array[i].keycode3 == keycodes[2])
                {
                    return i;
                }
            }
        }
        if (config->leader4_array != NULL)
        {
            for (uint8_t i = 0; i < config->leader4_count; i++)
            {
                if (config->leader4_array[i].keycode1 == keycodes[0] && config->leader4_array[i].keycode2 == keycodes[1] && config->leader4_array[i].keycode3 == keycodes[2])
                {
                    return -1;
                }
            }
        }
    }
    else if (count == 4)
    {
        if (config->leader4_array != NULL)
        {
            for (uint8_t i = 0; i < config->leader4_count; i++)
            {
                if (config->leader4_array[i].keycode1 == keycodes[0] && config->leader4_array[i].keycode2 == keycodes[1] && config->leader4_array[i].keycode3 == keycodes[2] && config->leader4_array[i].keycode4 == keycodes[3])
                {
                    return i;
                }
            }
        }
    }
    return -2;
}
