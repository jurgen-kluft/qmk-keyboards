#pragma once

// Note: when changing the order please change the code/data for OLED
//       to display the correct active layer.
enum layers
{
    _QWERTY = 0,
    _RSTHD,
    _QWERTY_CAPS,
    _RSTHD_CAPS,
    _NUM,
    _MOUS,
    _SYM,
    _NAV,
    _RAISE,
    _NUM_LAYERS
};

#if MAX_LAYER < _NUM_LAYERS
#error "MAX_LAYER must be at least _NUM_LAYERS"
#endif
