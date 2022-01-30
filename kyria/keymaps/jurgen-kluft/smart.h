#pragma once

#include "layers.h"

enum {
  SMART_CAPSLOCK = 0,
  SMART_NUMBERS = 1
};

// ------ smart state -----------
bool smart_feature_state(uint8_t f);
bool smart_feature_state_all(void);

void smart_feature_toggle(uint8_t f, uint8_t layer);
void smart_feature_enable(uint8_t f, uint8_t layer);
void smart_feature_disable(uint8_t f);
void smart_feature_disable_all(void);

bool smart_feature_cancel_key(uint16_t keycode, keyrecord_t *record);

// ------ smart capital letters ----------
void smart_capslock_process(uint16_t keycode, keyrecord_t *record);

// ------ smart numbers ----------
void smart_numbers_process(uint16_t keycode, keyrecord_t *record);

