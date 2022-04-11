# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
AUDIO_ENABLE = no          # Audio output
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
WEBUSB_ENABLE = yes
ORYX_ENABLE = no
TAP_DANCE_ENABLE = no

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC += rgb_lighting.c
endif
