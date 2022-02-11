# Disable unused features
VIA_ENABLE = no
NKRO_ENABLE = no
AUDIO_ENABLE = no
STENO_ENABLE = no
LEADER_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
TERMINAL_ENABLE = no
KEY_LOCK_ENABLE = no
BOOTMAGIC_ENABLE = no
SLEEP_LED_ENABLE = no
TAP_DANCE_ENABLE = no
VELOCIKEY_ENABLE = no
SWAP_HANDS_ENABLE = no
RGB_MATRIX_ENABLE = no
SPACE_CADET_ENABLE = no
KEY_OVERRIDE_ENABLE = no

UNICODE_ENABLE                  = no
WPM_ENABLE                      = no

ENCODER_ENABLE                  = yes # Ensure encoders are disabled unless set to true in a specific keymap
SWAP_HANDS_ENABLE               = yes

OLED_DRIVER_ENABLE              = yes  # Enables the use of OLED displays
RGBLIGHT_ENABLE                 = yes  # Enable keyboard RGB underglow

SRC += oled.c
SRC += smart.c
SRC += oneshot.c
SRC += cushi.c
SRC += cukey.c
