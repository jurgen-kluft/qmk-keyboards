#pragma once

#define xxxxx KC_NO

enum ecustomkeycodes
{
    CC_RANGE_START = SAFE_RANGE,

    CC_FNUM        = CC_RANGE_START,
    CC_FCAPS,
    CC_FNAV,
    CC_FSYM,
    CC_FCNT,

    // oneshot
    CC_CTRL,
    CC_SHFT,
    CC_ALT,
    CC_CMD,
    
    // cukey-start
    CC_UNDO,
    CC_REDO,
    CC_CUT,
    CC_COPY,
    CC_PASTE,
    CC_NDT,
    CC_PDT,
    CC_NAPP,
    CC_PAPP,
    CC_NDOC,
    CC_PDOC,
    CC_CLOSE,
    // cukey-end

    CC_PGUP,
    CC_PGDOWN,

    // secrets
    CC_SECRET_1,
    CC_SECRET_2,
    CC_SECRET_3,
    CC_SECRET_4,
    CC_SECRET_5,
    CC_SECRET_6,
    CC_SECRET_7,
    CC_SECRET_8,
    // space+shift
    CC_SPIFT,
    // layout
    CC_QWERTY,
    CC_RSTHD,

    CC_GAMEL,
    CC_GAMER,

    CC_RANGE_END,
};

