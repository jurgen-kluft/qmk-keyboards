#pragma once

typedef struct
{
    bool replaced;
    uint8_t tc;
    uint8_t modmask;
} cushi_t;

cushi_t process_cushi_keys(uint8_t ti, uint8_t tc, keyrecord_t* record);