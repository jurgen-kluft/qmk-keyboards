#include QMK_KEYBOARD_H
#include "smart.h"
#include "layers.h"

// ----------------------------------------------------------------------------------------------------

static uint8_t g_smart_status[2] = { 0, 0 };

bool smart_feature_state(uint8_t f) { return (g_smart_status[f] != 0); }
void smart_feature_disable(uint8_t f) {
  uint8_t layer = g_smart_status[f];
  if (layer > 0)
  {
    g_smart_status[f] = 0;
    layer_off(layer);
  }
}

void smart_feature_toggle(uint8_t f, uint8_t layer) { 
  if (!smart_feature_state(f)) {
    smart_feature_disable(1-f); // hack: turning on one smart feature turns off the other
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

    switch (keycode) {
      case KC_SCLN:
      case SKC_A ... SKC_Z:
      case KC_BSPC:
      case KC_DEL:
      case KC_UNDS:
      case KC_AT:
      case KC_DOT:
      case KC_MINS:
        if (record->event.pressed && (get_mods() != 0)) {
          keycode = KC_NO;
        }
        break;
      default:
        if (record->event.pressed) {
          keycode = KC_NO;
        }
    }

    if (keycode == KC_NO) {
      smart_feature_disable(SMART_CAPSLOCK);
    }
  }
}


// ----------------------------------------------------------------------------------------------------
// smart numbers

void smart_numbers_process(uint16_t keycode, keyrecord_t *record) {

  if (smart_feature_state(SMART_NUMBERS)) {

    switch (keycode) {
      case KC_1...KC_0:
      case KC_RBRACKET:
      case KC_LBRACKET:
      case KC_LPRN:
      case KC_RPRN:
      case KC_BSPC:
      case KC_DEL:
      case KC_UNDS:
      case KC_MINS:
      case KC_PLUS:
      case KC_ASTR:
      case KC_EQL:
      case KC_SLSH:
      case KC_DOT:
      case KC_COMMA:
        break;
      default:
          if (record->event.pressed) {
              keycode = KC_NO;        
          }
          break;
    }

    if (keycode == KC_NO) {
      smart_feature_disable(SMART_NUMBERS);
    }
  }
}
