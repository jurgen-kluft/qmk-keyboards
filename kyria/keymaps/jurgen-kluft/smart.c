#include QMK_KEYBOARD_H
#include "smart.h"
#include "layers.h"
#include "cukey.h"

// ----------------------------------------------------------------------------------------------------

static uint8_t g_smart_status[SMART_FEATURES] = {0, 0, 0};
static uint8_t g_smart_count[SMART_FEATURES] = {0, 0, 0};

bool smart_feature_state(uint8_t f) { return (g_smart_status[f] != 0); }
void smart_feature_enable(uint8_t f, uint8_t layer) {
    g_smart_status[f] = layer;
    g_smart_count[f] = 0;
    layer_on(layer);
}

void smart_feature_disable(uint8_t f) {
    uint8_t layer = g_smart_status[f];
    if (layer > 0) {
        g_smart_status[f] = 0;
        g_smart_count[f] = 0;
        layer_off(layer);
    }
}

bool smart_feature_state_all() {
    for (uint8_t i = 0; i < SMART_FEATURES; i++) {
        if (g_smart_status[i] != 0)
            return true;
    }
    return false;
}

void smart_feature_disable_all_but(uint8_t f) {
    for (uint8_t i = 0; i < SMART_FEATURES; i++) {
        if (i != f) {
            uint8_t layer = g_smart_status[i];
            if (layer > 0) {
                g_smart_status[i] = 0;
                g_smart_count[f] = 0;
                layer_off(layer);
            }
        }
    }
}

void smart_feature_toggle(uint8_t f, uint8_t layer) {
    if (!smart_feature_state(f)) {
        g_smart_status[f] = layer;
        g_smart_count[f] = 0;
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
                case KC_SPACE:
                    smart_feature_disable(SMART_CAPSLOCK);
                    return;
            }
            g_smart_count[SMART_CAPSLOCK] |= 2;
            if (smart_feature_cancel_key(keycode, record)) {
                smart_feature_disable(SMART_CAPSLOCK);
            }
        } else {
            switch (keycode) {
                case KC_SCAPS:
                    g_smart_count[SMART_CAPSLOCK] |= 1;
                    if (g_smart_count[SMART_CAPSLOCK] == 3) {
                        smart_feature_disable(SMART_CAPSLOCK);
                    }
                    break;
            }
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
                case KC_LBRC:
                case KC_RBRC:
                case KC_LCBR:
                case KC_RCBR:
                case KC_PERC:
                case KC_QUOT:
                case KC_MINUS:
                case KC_PLUS:
                case KC_SLASH:
                case KC_DLR:
                case KC_TILD:
                case KC_UNDS:
                case KC_ASTR:
                case KC_EQUAL:
                case KC_GRV:
                case KC_LPRN:
                case KC_RPRN:
                case KC_DQUO:
                case KC_COLN:
                case KC_CIRC:
                case KC_QUES:
                case KC_EXLM:
                case KC_HASH:
                case KC_LABK:
                case KC_RABK:
                case KC_AMPR:
                case KC_PIPE:
                case KC_BSLASH:
                case KC_AT:
                case KC_COMMA:
                case KC_DOT:
                    g_smart_count[SMART_NUMBERS] |= 2;
                    return;

                 smart_feature_disable(SMART_NUMBERS);
            }
        } else {
            switch (keycode) {
                case KC_SNUM:
                    g_smart_count[SMART_NUMBERS] |= 1;
                    if (g_smart_count[SMART_NUMBERS] == 3) {
                        smart_feature_disable(SMART_NUMBERS);
                    }
                    break;
            }
        }
    }
}

// ----------------------------------------------------------------------------------------------------
// smart symbols

void smart_symbols_process(uint16_t keycode, keyrecord_t *record) {
    if (smart_feature_state(SMART_SYMBOLS)) {
        if (record->event.pressed) {
            g_smart_count[SMART_SYMBOLS] |= 2;
        } else {
            switch (keycode) {
                case KC_SSYM:
                    g_smart_count[SMART_SYMBOLS] |= 1;
                    break;
            }
            if (g_smart_count[SMART_SYMBOLS] == 3) {
                smart_feature_disable(SMART_SYMBOLS);
            }
        }
    }
}
