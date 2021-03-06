#pragma once

#define KYRIA_TO_HILLSIDE_LAYOUT( \
    L00, L01, L02, L03, L04, L05,                     R06, R07, R08, R09, R10, R11, \
    L12, L13, L14, L15, L16, L17,                     R18, R19, R20, R21, R22, R23, \
    L24, L25, L26, L27, L28, L29, L30, L31, R32, R33, R34, R35, R36, R37, R38, R39, \
                   L40, L41, L42, L43, L44, R45, R46, R47, R48, R49 \
) \
{ \
    { L00, L01, L02, L03, L04, L05 }, \
    { L12, L13, L14, L15, L16, L17 }, \
    { L24, L25, L26, L27, L28, L29 }, \
    { L40, L41, L42, L43, L44, L30 }, \
    { R11, R10, R09, R08, R07, R06 }, \
    { R23, R22, R21, R20, R19, R18 }, \
    { R39, R38, R37, R36, R35, R34 }, \
    { R49, R48, R47, R46, R45, R33 }  \
}


// This is a LAYOUT that maps a Kyria layout to a Hillside layout.
// I do this so that I can use the same keymap for both keyboards.
// Next step is to actually share this keymap between keyboards.
#ifdef KEYBOARD_HILLSIDE
#undef LAYOUT
#define LAYOUT KYRIA_TO_HILLSIDE_LAYOUT
#endif
