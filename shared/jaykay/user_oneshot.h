#pragma once

#include "user_keycode_ranges.h"

enum eoneshot_keycodes
{
    OS_CTRL = ONESHOT_KEYCODES_START,
    OS_SHFT,
    OS_ALT,
    OS_CMD,
    ONESHOT_SAFE_RANGE_END
};

#if ((ONESHOT_SAFE_RANGE_END-1) > ONESHOT_KEYCODES_END)
#error "Not enough space for ONESHOT keycodes"
#endif
