#include QMK_KEYBOARD_H

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
}
