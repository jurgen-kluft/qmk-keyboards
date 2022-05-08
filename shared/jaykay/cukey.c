#include QMK_KEYBOARD_H
#include "cukey.h"

#define KC_MAC_UNDO  LGUI(KC_Z)
#define KC_MAC_REDO  LGUI(LSFT(KC_Z))
#define KC_MAC_CUT   LGUI(KC_X)
#define KC_MAC_COPY  LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_MAC_NDT   LCTL(KC_RIGHT)
#define KC_MAC_PDT   LCTL(KC_LEFT)
#define KC_MAC_CLOSE LGUI(KC_W)

#define KC_UBT_UNDO  LCTL(KC_W)
#define KC_UBT_REDO  LCTL(LSFT(KC_Z))
#define KC_UBT_CUT   LGUI(KC_X)
#define KC_UBT_COPY  LGUI(KC_C)
#define KC_UBT_PASTE LGUI(KC_V)
#define KC_UBT_NDT   LCTL(KC_RIGHT)
#define KC_UBT_PDT   LCTL(KC_LEFT)
#define KC_UBT_CLOSE LGUI(KC_W)

#define KC_PC_UNDO  LCTL(KC_Z)
#define KC_PC_REDO  LCTL(LSFT(KC_Z))
#define KC_PC_CUT   LCTL(KC_X)
#define KC_PC_COPY  LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define KC_PC_NDT   LCTL(LGUI(KC_RIGHT))
#define KC_PC_PDT   LCTL(LGUI(KC_LEFT))
#define KC_PC_CLOSE LCTL(KC_W)

typedef union
{
    uint32_t raw;
    struct
    {
        uint8_t os;
    };
} user_config_t;

user_config_t user_config;

void keyboard_init_cukey(void)
{ // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
}
void eeconfig_init_user(void)
{ // EEPROM is getting reset!
    user_config.raw = 0;
    eeconfig_update_user(user_config.raw);
}
void keyboard_set_os(uint8_t os)
{
    user_config.os = os;
    eeconfig_update_user(user_config.raw);
}
uint8_t keyboard_get_os(void) { return user_config.os; }

uint16_t const kc_os_win[] = {KC_PC_UNDO, KC_PC_REDO, KC_PC_CUT, KC_PC_COPY, KC_PC_PASTE, KC_PC_NDT, KC_PC_PDT, KC_PC_CLOSE};
uint16_t const kc_os_mac[] = {KC_MAC_UNDO, KC_MAC_REDO, KC_MAC_CUT, KC_MAC_COPY, KC_MAC_PASTE, KC_MAC_NDT, KC_MAC_PDT, KC_MAC_CLOSE};
uint16_t const kc_os_ubt[] = {KC_UBT_UNDO, KC_UBT_REDO, KC_UBT_CUT, KC_UBT_COPY, KC_UBT_PASTE, KC_UBT_NDT, KC_UBT_PDT, KC_UBT_CLOSE};

uint16_t process_cukey(uint16_t keycode)
{
    switch (keycode)
    {
        case KC_OS_UNDO:
        case KC_OS_REDO:
        case KC_OS_CUT:
        case KC_OS_COPY:
        case KC_OS_PASTE:
        case KC_OS_NDT:
        case KC_OS_PDT:
        case KC_OS_CLOSE:
        {
            uint8_t i = (uint8_t)(keycode - KC_OS_UNDO);
            switch (user_config.os)
            {
                case OS_WINDOWS: keycode = (kc_os_win[i]); break;
                case OS_UBUNTU: keycode = (kc_os_ubt[i]); break;
                case OS_MAC: keycode = (kc_os_mac[i]); break;
                default:
                    keycode = (kc_os_mac[i]);
                    keyboard_set_os(OS_MAC);
                    break;
            }
        }
        break;
    }
    return keycode;
}