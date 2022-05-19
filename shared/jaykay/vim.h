#pragma once
#include "config.h"

enum evim_mode
{
    VIM_MODE_NORMAL = 0,
    VIM_MODE_INSERT = 1,
};

void      vim_mode_toggle(void);
int8_t    vim_mode(void);
bool      vim_raise(void);

bool process_vim(uint8_t keycode, keyrecord_t* record);
