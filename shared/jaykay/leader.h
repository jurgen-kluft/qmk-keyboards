#pragma once

typedef struct
{
    uint16_t start;
    uint16_t end;
} leader_range_t;

typedef struct
{
    uint16_t keycode1;
} leader1_t;

typedef struct
{
    uint16_t keycode1;
    uint16_t keycode2;
} leader2_t;

typedef struct
{
    uint16_t keycode1;
    uint16_t keycode2;
    uint16_t keycode3;
} leader3_t;

typedef struct
{
    uint8_t               leader_range_count;
    const leader_range_t* leader_range_array;
    uint8_t               leader1_count;
    const leader1_t*      leader1_array;
    uint8_t               leader2_count;
    const leader2_t*      leader2_array;
    uint8_t               leader3_count;
    const leader3_t*      leader3_array;
} leader_config_t;

// leader feature
bool process_record_leader(uint16_t keycode, keyrecord_t* record, leader_config_t* leader_config);
