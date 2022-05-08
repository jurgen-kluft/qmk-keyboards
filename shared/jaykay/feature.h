#pragma once

#include "user_keycode_ranges.h"

enum efeature_keys
{
    KC_FCAPS = FEATURE_KEYCODES_START,
    KC_FNUM,
    KC_FSYM,
    KC_FNAV,
    FEATURE_SAFE_RANGE_END
};

#if ((FEATURE_SAFE_RANGE_END-1) > FEATURE_KEYCODES_END)
#error "Not enough space for FEATURE keycodes"
#endif

void enable_smart_capslock(void);
void enable_smart_camelcase(void);

// ------ feature processing ----------
bool process_feature_key(uint16_t keycode, keyrecord_t* record);
