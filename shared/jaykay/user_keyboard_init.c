#include QMK_KEYBOARD_H
#include "user_layers.h"

#ifdef RGB_MATRIX_ENABLE
__attribute__((weak)) void keyboard_init_rgb_matrix(void);
#endif
__attribute__((weak)) void keyboard_init_cukey(void);

void keyboard_post_init_user(void)
{
#ifdef RGB_MATRIX_ENABLE
    keyboard_init_rgb_matrix();
#endif
    keyboard_init_cukey();

#       ifdef CONSOLE_ENABLE
    debug_enable=true;
#       endif // CONSOLE_ENABLE

    user_layer_on(LAYER_BASE); // activate the base layer, QWERTY or RSTHD
}
