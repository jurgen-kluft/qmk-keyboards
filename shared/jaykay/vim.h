#pragma once
#include "config.h"

void vim_enable(void);
void vim_disable(void);
bool vim_is_active(void);

void process_vim(uint8_t keycode, keyrecord_t* record);
