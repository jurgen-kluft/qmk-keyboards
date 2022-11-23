// Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pointing/pointing.h"
#include "user_layers.h"
#include "user_keycodes.h"

static uint16_t mouse_debounce_timer  = 0;
bool            enable_acceleration = false;

#ifdef TAPPING_TERM_PER_KEY
#    define TAP_CHECK get_tapping_term(KC_BTN1, NULL)
#else
#    ifndef TAPPING_TERM
#        define TAPPING_TERM 200
#    endif
#    define TAP_CHECK TAPPING_TERM
#endif

__attribute__((weak)) report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report) {
    return mouse_report;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    mouse_xy_report_t x = mouse_report.x, y = mouse_report.y;
    mouse_report.x = 0;
    mouse_report.y = 0;

    if (x != 0 && y != 0) {
#ifdef OLED_ENABLE
        oled_timer_reset();
#endif
        if (timer_elapsed(mouse_debounce_timer) > TAP_CHECK) {
            if (enable_acceleration) {
                x = (mouse_xy_report_t)(x > 0 ? x * x / 16 + x : -x * x / 16 + x);
                y = (mouse_xy_report_t)(y > 0 ? y * y / 16 + y : -y * y / 16 + y);
            }
            mouse_report.x = x;
            mouse_report.y = y;
            if (!layer_state_is(LAYER_MOUSE)) {
                layer_on(LAYER_MOUSE);
            }
        }
    }

    return pointing_device_task_keymap(mouse_report);
}

bool process_record_pointing(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case CC_FNAV:
            if (record->event.pressed) {
                if (layer_state_is(LAYER_MOUSE)) {
                    layer_off(LAYER_MOUSE);
                }
            }
            break;
#if defined(KEYBOARD_bastardkb_dilemma_3x5_2_assembled)
        case SAFE_RANGE ... (DILEMMA_SAFE_RANGE-1):
#endif
        case KC_MS_UP ... KC_MS_WH_RIGHT:
            break;
        case CC_ACCEL:
            enable_acceleration = record->event.pressed;
            break;
#if 0
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            break;
#endif
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            if (record->event.pressed || !record->tap.count) {
                break;
            }
        default:
            if (IS_NOEVENT(record->event)) break;
            mouse_debounce_timer  = timer_read();
            break;
    }
    return true;
}

layer_state_t layer_state_set_pointing(layer_state_t state) {
    return state;
}
