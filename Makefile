PROJECT_NAME := pwm_project
OUTPUT_DIRECTORY := build
SDK_ROOT := /home/vboxuser/nRF5_SDK_17.1.0_ddde560

SRC_FILES := \
    src/main.c \
    $(SDK_ROOT)/modules/nrfx/mdk/gcc_startup_nrf52.S

INC_FOLDERS := \
    src

CFLAGS := -DBOARD_PCA10059 -DNRF52840_XXAA -D__CORTEX_M4

HEX_FILE := $(OUTPUT_DIRECTORY)/$(PROJECT_NAME).hex
DFU_PACKAGE := $(OUTPUT_DIRECTORY)/$(PROJECT_NAME)_dfu.zip

all: $(DFU_PACKAGE)

$(HEX_FILE): $(SRC_FILES) | $(OUTPUT_DIRECTORY)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 \
	-O0 -g3 -fdata-sections -ffunction-sections \
	$(CFLAGS) $(addprefix -I,$(INC_FOLDERS)) \
	-Wl,-Map=$(OUTPUT_DIRECTORY)/$(PROJECT_NAME).map \
	-specs=nano.specs -specs=nosys.specs \
	-L$(SDK_ROOT)/modules/nrfx/mdk \
	-Wl,--gc-sections \
	-o $(OUTPUT_DIRECTORY)/$(PROJECT_NAME).elf \
	$(SRC_FILES)
	arm-none-eabi-objcopy -O ihex $(OUTPUT_DIRECTORY)/$(PROJECT_NAME).elf $(HEX_FILE)
	arm-none-eabi-size $(OUTPUT_DIRECTORY)/$(PROJECT_NAME).elf

$(DFU_PACKAGE): $(HEX_FILE)
	nrfutil pkg generate --hw-version 52 --sd-req 0x00 --application $(HEX_FILE) --application-version 1 $(DFU_PACKAGE)

$(OUTPUT_DIRECTORY):
	mkdir -p $(OUTPUT_DIRECTORY)

flash: $(DFU_PACKAGE)
	nrfutil dfu usb-serial -pkg $(DFU_PACKAGE) -p /dev/ttyACM0

flash_jlink: $(HEX_FILE)
	nrfjprog -f nrf52 --program $(HEX_FILE) --sectorerase
	nrfjprog -f nrf52 --reset

clean:
	rm -rf $(OUTPUT_DIRECTORY)

.PHONY: all flash flash_jlink clean

dfu:
	nrfutil dfu usb-serial -pkg $(DFU_PACKAGE) -p /dev/ttyACM0

.PHONY: dfu
