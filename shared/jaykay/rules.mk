SRC += $(USER_PATH)/oneshot.c
SRC += $(USER_PATH)/cushi.c
SRC += $(USER_PATH)/cukey.c
SRC += $(USER_PATH)/feature.c
SRC += $(USER_PATH)/leader.c

# All the user implementations are below
ifeq ($(strip $(ENCODER_ENABLE)), yes)
    SRC += $(USER_PATH)/user_encoder_update.c
endif
SRC += $(USER_PATH)/user_keyboard_init.c
SRC += $(USER_PATH)/user_oneshot.c
SRC += $(USER_PATH)/user_process_record.c
SRC += $(USER_PATH)/user_leader.c
SRC += $(USER_PATH)/user_keycodes.c
SRC += $(USER_PATH)/user_layers.c

ifeq ($(strip $(REPEAT_KEY_ENABLE)), yes)
SRC += $(USER_PATH)/user_magic_sturdy.c
endif

CUSTOM_POINTING_DEVICE ?= no
ifeq ($(strip $(POINTING_DEVICE_ENABLE)), yes)
    ifeq ($(strip $(CUSTOM_POINTING_DEVICE)), yes)
        SRC += $(USER_PATH)/pointing/pointing.c
        OPT_DEFS += -DCUSTOM_POINTING_DEVICE
    endif
endif