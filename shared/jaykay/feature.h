#pragma once

void enable_smart_capslock(void);
void enable_smart_camelcase(void);

// ------ feature processing ----------
bool process_feature_key(uint8_t keycode, keyrecord_t* record);
