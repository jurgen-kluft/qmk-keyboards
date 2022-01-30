#include QMK_KEYBOARD_H
#include "smart.h"
#include "layers.h"

// ----------------------------------------------------------------------------------------------------

static uint8_t g_smart_status[2] = {0, 0};

bool smart_feature_state(uint8_t f) { return (g_smart_status[f] != 0); }
void smart_feature_enable(uint8_t f, uint8_t layer) {
    smart_feature_disable(1 - f);  // hack: turning on one smart feature turns off the other
    g_smart_status[f] = layer;
    layer_on(layer);
}

void smart_feature_disable(uint8_t f) {
    uint8_t layer = g_smart_status[f];
    if (layer > 0) {
        g_smart_status[f] = 0;
        layer_off(layer);
    }
}

bool smart_feature_state_all() { return (g_smart_status[0] != 0) || (g_smart_status[1] != 0); }
void smart_feature_disable_all() {
    for (uint8_t f = 0; f < 2; f++) {
        uint8_t layer = g_smart_status[f];
        if (layer > 0) {
            g_smart_status[f] = 0;
            layer_off(layer);
        }
    }
}

void smart_feature_toggle(uint8_t f, uint8_t layer) {
    if (!smart_feature_state(f)) {
        smart_feature_disable(1 - f);  // hack: turning on one smart feature turns off the other
        g_smart_status[f] = layer;
        layer_on(layer);
    } else {
        smart_feature_disable(f);
    }
}

// ----------------------------------------------------------------------------------------------------
// smart capslock

#define SKC_A S(KC_A)
#define SKC_Z S(KC_Z)

void smart_capslock_process(uint16_t keycode, keyrecord_t *record) {
    if (smart_feature_state(SMART_CAPSLOCK)) {
        if (record->event.pressed) {
            switch (keycode) {
                case KC_SCLN:
                case SKC_A ... SKC_Z:
                case KC_BSPC:
                case KC_DEL:
                case KC_UNDS:
                case KC_AT:
                case KC_DOT:
                case KC_MINS:
                    if (get_mods() == 0) {
                        return;
                    }
            }

            smart_feature_disable(SMART_CAPSLOCK);
        }
    }
}

// ----------------------------------------------------------------------------------------------------
// smart numbers

void smart_numbers_process(uint16_t keycode, keyrecord_t *record) {
    if (smart_feature_state(SMART_NUMBERS)) {
        if (record->event.pressed) {
            switch (keycode) {
                case KC_1 ... KC_0:
                case KC_RBRACKET:
                case KC_LBRACKET:
                case KC_LPRN:
                case KC_RPRN:
                case KC_BSPC:
                case KC_UNDS:
                case KC_MINS:
                case KC_PLUS:
                case KC_ASTR:
                case KC_EQL:
                case KC_SLSH:
                case KC_DOT:
                case KC_COMMA:
                    return;
            }

            smart_feature_disable(SMART_NUMBERS);
        }
    }
}
