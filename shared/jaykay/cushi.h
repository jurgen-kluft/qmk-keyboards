#pragma once

typedef struct
{
    bool replaced;
    uint16_t kc;
    uint8_t modmask;
} cushi_t;

cushi_t process_cushi_keys(uint16_t tc, keyrecord_t* record);