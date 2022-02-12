#pragma once

// Note: when changing the order please change the code/data for OLED
//       to display the correct active layer.
enum layers {
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

#define LA_SYM   MO(_SYM)
#define LA_NAV   MO(_NAV)
#define LA_NUM   MO(_NUM)
#define LT_MOS   TG(_MOUS)
