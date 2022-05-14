#include QMK_KEYBOARD_H
#include "user_layers.h"

// Layer-specific encoder knob functions
bool encoder_update_user(uint8_t index, bool clockwise)
{
    uint16_t layer = user_current_layer();
    if (index == 0)
    { // left knob
        switch (layer)
        {
#ifdef RGBLIGHT_ENABLE
            case LAYER_MOUS: // Underglow color
                if (clockwise)
                {
                    rgblight_increase_hue();
                }
                else
                {
                    rgblight_decrease_hue();
                }
                break;
#endif
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
        switch (layer)
        {
            case LAYER_NAVIGATION:
                if (clockwise)
                {
                    tap_code(KC_MS_WH_DOWN);
                }
                else
                {
                    tap_code(KC_MS_WH_UP);
                }
                break;
#ifdef RGBLIGHT_ENABLE
            case LAYER_MOUS: // Underglow brightness
                if (clockwise)
                {
                    rgblight_increase_val();
                }
                else
                {
                    rgblight_decrease_val();
                }
                break;
#endif
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
