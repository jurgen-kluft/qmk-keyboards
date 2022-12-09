
USE_ARM_CONFIG ?= no
ifeq ($(strip $(CONVERT_TO)), promicro_rp2040)
    USE_ARM_CONFIG = yes
endif

ifeq ($(strip $(USE_ARM_CONFIG)), yes)
    OLED_ENABLE    = yes  # Enable OLEDs
    WPM_ENABLE     = yes
    CORREX_ENABLE  = yes
endif
