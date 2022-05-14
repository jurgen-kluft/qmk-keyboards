SRC += $(USER_PATH)/oneshot.c
SRC += $(USER_PATH)/cushi.c
SRC += $(USER_PATH)/cukey.c
SRC += $(USER_PATH)/feature.c
SRC += $(USER_PATH)/leader.c
SRC += $(USER_PATH)/vim.c

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


