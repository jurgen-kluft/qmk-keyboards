#include QMK_KEYBOARD_H
#include "config.h"
#include "cukey.h"
#include "user_keycodes.h"

#define KC_MAC_UNDO  LGUI(KC_Z)
#define KC_MAC_REDO  LGUI(LSFT(KC_Z))
#define KC_MAC_CUT   LGUI(KC_X)
#define KC_MAC_COPY  LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_MAC_NDT   LCTL(KC_RIGHT)
#define KC_MAC_PDT   LCTL(KC_LEFT)
#define KC_MAC_CLOSE LGUI(KC_W)
#define KC_MAC_NAPP  LGUI(KC_GRV)
#define KC_MAC_PAPP  LGUI(S(KC_GRV))
#define KC_MAC_NDOC  C(KC_TAB)
#define KC_MAC_PDOC  C(S(KC_TAB))

#define KC_UBT_UNDO  LCTL(KC_W)
#define KC_UBT_REDO  LCTL(LSFT(KC_Z))
#define KC_UBT_CUT   LGUI(KC_X)
#define KC_UBT_COPY  LGUI(KC_C)
#define KC_UBT_PASTE LGUI(KC_V)
#define KC_UBT_NDT   LCTL(KC_RIGHT)
#define KC_UBT_PDT   LCTL(KC_LEFT)
#define KC_UBT_CLOSE LGUI(KC_W)
#define KC_UBT_NAPP  LGUI(KC_GRV)
#define KC_UBT_PAPP  LGUI(S(KC_GRV))
#define KC_UBT_NDOC  C(KC_TAB)
#define KC_UBT_PDOC  C(S(KC_TAB))

#define KC_WIN_UNDO  LCTL(KC_Z)
#define KC_WIN_REDO  LCTL(LSFT(KC_Z))
#define KC_WIN_CUT   LCTL(KC_X)
#define KC_WIN_COPY  LCTL(KC_C)
#define KC_WIN_PASTE LCTL(KC_V)
#define KC_WIN_NDT   LCTL(LGUI(KC_RIGHT))
#define KC_WIN_PDT   LCTL(LGUI(KC_LEFT))
#define KC_WIN_CLOSE LCTL(KC_W)
#define KC_WIN_NAPP  A(KC_TAB)
#define KC_WIN_PAPP  A(S(KC_TAB))
#define KC_WIN_NDOC  C(KC_TAB)
#define KC_WIN_PDOC  C(S(KC_TAB))

typedef union
{
    uint32_t raw;
    struct
    {
        uint8_t os;
        uint8_t layout;
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

void keyboard_set_layout(int8_t layout)
{
    user_config.layout = layout;
    eeconfig_update_user(user_config.raw);
}
int8_t keyboard_get_layout() { return user_config.layout; }

uint16_t const kc_os_win[] = {KC_WIN_UNDO, KC_WIN_REDO, KC_WIN_CUT, KC_WIN_COPY, KC_WIN_PASTE, KC_WIN_NDT, KC_WIN_PDT, KC_WIN_NAPP, KC_WIN_PAPP, KC_WIN_NDOC, KC_WIN_PDOC, KC_WIN_CLOSE};
uint16_t const kc_os_mac[] = {KC_MAC_UNDO, KC_MAC_REDO, KC_MAC_CUT, KC_MAC_COPY, KC_MAC_PASTE, KC_MAC_NDT, KC_MAC_PDT, KC_MAC_NAPP, KC_MAC_PAPP, KC_MAC_NDOC, KC_MAC_PDOC, KC_MAC_CLOSE};
uint16_t const kc_os_ubt[] = {KC_UBT_UNDO, KC_UBT_REDO, KC_UBT_CUT, KC_UBT_COPY, KC_UBT_PASTE, KC_UBT_NDT, KC_UBT_PDT, KC_UBT_NAPP, KC_UBT_PAPP, KC_UBT_NDOC, KC_UBT_PDOC, KC_UBT_CLOSE};

uint16_t process_cukey(uint8_t keycode)
{
    uint16_t kc = KC_NO;
    switch (keycode)
    {
        case CC_UNDO ... CC_CLOSE:
        {
            uint8_t i = (uint8_t)(keycode - CC_UNDO);
            switch (user_config.os)
            {
                case OS_WINDOWS: kc = (kc_os_win[i]); break;
                case OS_UBUNTU: kc = (kc_os_ubt[i]); break;
                case OS_MAC: kc = (kc_os_mac[i]); break;
                default:
                    kc = (kc_os_mac[i]);
                    keyboard_set_os(OS_MAC);
                    break;
            }
        }
        break;
    }
    return kc;
}
