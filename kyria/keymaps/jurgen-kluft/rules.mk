# Disable unused features
BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration
COMBO_ENABLE = yes      # Key combo support
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = no  	# Console for debug
COMMAND_ENABLE = no     # Commands for debug and configuration
NKRO_ENABLE = no		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
MIDI_ENABLE = no 		# MIDI controls
UNICODE_ENABLE = no 	# Unicode
BLUETOOTH_ENABLE = no   # Enable Bluetooth with the Adafruit EZ-Key HID
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches

VIA_ENABLE = no
AUDIO_ENABLE = no
STENO_ENABLE = no
LEADER_ENABLE = no
TERMINAL_ENABLE = no
KEY_LOCK_ENABLE = no
SLEEP_LED_ENABLE = no
TAP_DANCE_ENABLE = no
VELOCIKEY_ENABLE = no
RGB_MATRIX_ENABLE = no
SPACE_CADET_ENABLE = no
KEY_OVERRIDE_ENABLE = no
GRAVE_ESC_ENABLE = no
AUTO_SHIFT_ENABLE = no

WPM_ENABLE                      = no

ENCODER_ENABLE                  = yes # Ensure encoders are disabled unless set to true in a specific keymap
SWAP_HANDS_ENABLE               = yes

OLED_DRIVER_ENABLE              = no  # Enables the use of OLED displays
RGBLIGHT_ENABLE                 = no  # Enable keyboard RGB underglow

SRC += oled.c
SRC += oneshot.c
SRC += cushi.c
SRC += cukey.c
SRC += feature.c
