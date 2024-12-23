#pragma once

enum eOS
{
    OS_MAC     = 0,
    OS_WINDOWS = 1,
    OS_UBUNTU  = 2,
};

void    keyboard_set_os(uint8_t os);
uint8_t keyboard_get_os(void);
void    keyboard_set_layout(int8_t layout);
int8_t  keyboard_get_layout(void);

uint16_t process_cukey(uint16_t keycode);
