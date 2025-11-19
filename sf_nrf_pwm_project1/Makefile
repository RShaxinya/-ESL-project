PROJECT_NAME := pwm_project
OUTPUT_DIRECTORY := build

SDK_ROOT := $(HOME)/nRF5_SDK_17.1.0_ddde560
SRC_FILES := src/main.c
INCLUDE_PATHS := -I$(SDK_ROOT)/modules/nrfx/mdk \
                 -I$(SDK_ROOT)/modules/nrfx/drivers/include \
                 -I$(SDK_ROOT)/integration/nrfx/legacy \
                 -I$(SDK_ROOT)/components \
                 -I$(SDK_ROOT)/components/libraries/log \
                 -I$(SDK_ROOT)/components/libraries/timer \
                 -I$(SDK_ROOT)/components/drivers_nrf/pwm \
                 -I$(SDK_ROOT)/components/drivers_nrf/gpiote \
                 -I$(SDK_ROOT)/components/toolchain/cmsis/include

CFLAGS := -DBOARD_PCA10059 -DNRF52840_XXAA
$(shell mkdir -p $(OUTPUT_DIRECTORY))
all: $(OUTPUT_DIRECTORY)/$(PROJECT_NAME).hex
$(OUTPUT_DIRECTORY)/$(PROJECT_NAME).hex: $(SRC_FILES) | $(OUTPUT_DIRECTORY)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -g $(SRC_FILES) $(CFLAGS) $(INCLUDE_PATHS) -o $(OUTPUT_DIRECTORY)/$(PROJECT_NAME).out
	arm-none-eabi-objcopy -O ihex $(OUTPUT_DIRECTORY)/$(PROJECT_NAME).out $(OUTPUT_DIRECTORY)/$(PROJECT_NAME).hex
$(OUTPUT_DIRECTORY):
	mkdir -p $(OUTPUT_DIRECTORY)
clean:
	rm -rf $(OUTPUT_DIRECTORY)/*.out $(OUTPUT_DIRECTORY)/*.hex
dfu: $(OUTPUT_DIRECTORY)/$(PROJECT_NAME).hex
	nrfutil pkg generate --hw-version 52 --sd-req 0x00 --application-version 1 --application $< $(OUTPUT_DIRECTORY)/$(PROJECT_NAME)_dfu.zip
