#include QMK_KEYBOARD_H
#include "layers.h"

// Layer-specific encoder knob functions
bool encoder_update_user(uint8_t index, bool clockwise)
{
    uint16_t layers = (layer_state | default_layer_state);
    if (index == 0)
    { // left knob
        switch (get_highest_layer(layers))
        {
            case _MOUS: // Underglow color
#ifdef RGBLIGHT_ENABLE
                if (clockwise)
                {
                    rgblight_increase_hue();
                }
                else
                {
                    rgblight_decrease_hue();
                }
#endif
                break;
            default: // Volume Up/Down
                if (clockwise)
                {
                    tap_code(KC_VOLD);
                }
                else
                {
                    tap_code(KC_VOLU);
                }
                break;
        }
    }
    else if (index == 1)
    { // right knob
        switch (get_highest_layer(layers))
        {
            case _NAV:
                if (clockwise)
                {
                    tap_code(KC_MS_WH_DOWN);
                }
                else
                {
                    tap_code(KC_MS_WH_UP);
                }
                break;
            case _MOUS: // Underglow brightness
#ifdef RGBLIGHT_ENABLE
                if (clockwise)
                {
                    rgblight_increase_val();
                }
                else
                {
                    rgblight_decrease_val();
                }
#endif
                break;
            default:
                if (clockwise)
                {
                    tap_code(KC_BRIU);
                }
                else
                {
                    tap_code(KC_BRID);
                }
                break;
        }
    }
    return false;
}
