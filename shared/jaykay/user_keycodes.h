#pragma once

// -------------------------------------------------------------------------------------------------
#define xxxxx KC_NO

enum ecustomkeycodes
{
    CC_RANGE_START = SAFE_RANGE + 64,

    CC_FNAV        = CC_RANGE_START,
    CC_FSYM,

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

    // layouts
    CC_QWERTY,
    CC_RSTHD,
    CC_GRAPHITE,
    CC_ENGRAM2,
    CC_STURDY,

    // game
    CC_GAMEL,
    CC_GAMER,

    // magic sturdy
    CC_MAG_2,
    CC_MAG_3,
    MK_DUND,
    MG_ENT,
    MG_MENT,
    MG_ER,
    MG_ES,
    MG_UST,
    MG_ON,
    MG_ION,
    MG_OA,
    MG_UI,
    MG_SP_The,
    MG_SP_BUT,
    MG_SP_AND,
    MG_EFORE,
    MG_HICH,
    MG_COM,
    MG_QUOT_S,
    
    CC_RANGE_END,
};

