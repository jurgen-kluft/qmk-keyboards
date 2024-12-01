#pragma once

// ------ feature processing ----------
bool process_feature_key(uint16_t tc, keyrecord_t* record);

// ------ smart num feature ----------
void enable_smart_numbers(void);
void disable_smart_numbers(uint8_t layer_to_activate);
