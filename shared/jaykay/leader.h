#pragma once
#include "config.h"

typedef struct
{
    uint8_t keycode1;
} leader1_t;

typedef struct
{
    uint8_t keycode1;
    uint8_t keycode2;
} leader2_t;

typedef struct
{
    uint8_t keycode1;
    uint8_t keycode2;
    uint8_t keycode3;
} leader3_t;

typedef struct
{
    uint8_t keycode1;
    uint8_t keycode2;
    uint8_t keycode3;
    uint8_t keycode4;
} leader4_t;

typedef struct
{
    uint8_t               leader1_count;
    const leader1_t*      leader1_array;
    uint8_t               leader2_count;
    const leader2_t*      leader2_array;
    uint8_t               leader3_count;
    const leader3_t*      leader3_array;
    uint8_t               leader4_count;
    const leader4_t*      leader4_array;
} leader_config_t;

// leader feature
bool leader_is_active(void);
void leader_disable(void);
bool process_record_leader(uint8_t keycode, keyrecord_t* record, leader_config_t * config);
