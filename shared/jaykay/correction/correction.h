#pragma once



/**
 * @brief handler for determining if autocorrect should process keypress
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @param typo_buffer_size passed along to allow resetting of autocorrect buffer
 * @param mods allow processing of mod status
 * @return true Allow autocorection
 * @return false Stop processing and escape from autocorrect.
 */
bool process_autocorrect_user(uint16_t *keycode, keyrecord_t *record, uint8_t *typo_buffer_size, uint8_t *mods);

/**
 * @brief Process handler for autocorrect feature
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @return true Continue processing keycodes, and send to host
 * @return false Stop processing keycodes, and don't send to host
 */
bool process_autocorrection(uint16_t keycode, keyrecord_t *record);

/**
 * @brief handling for when autocorrection has been triggered
 *
 * @param backspaces number of characters to remove
 * @param str pointer to PROGMEM string to replace mistyped seletion with
 * @return true apply correction
 * @return false user handled replacement
 */
bool apply_autocorrect(uint8_t backspaces, const char *str);


/**
 * @brief function for querying the enabled state of autocorrect
 *
 * @return true if enabled
 * @return false if disabled
 */
bool autocorrect_is_enabled(void);

/**
 * @brief Enables autocorrect and saves state to eeprom
 *
 */
void autocorrect_enable(void);

/**
 * @brief Disables autocorrect and saves state to eeprom
 *
 */
void autocorrect_disable(void);

/**
 * @brief Toggles autocorrect's status and save state to eeprom
 *
 */
void autocorrect_toggle(void);