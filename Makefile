PROJECT_NAME = app
BUILD_DIR = build
SOURCES = main.c

CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -O0 -g -std=c99
LDFLAGS = -Wl,--gc-sections

OBJS = $(SOURCES:%.c=$(BUILD_DIR)/%.o)
ELF = $(BUILD_DIR)/$(PROJECT_NAME).elf
HEX = $(BUILD_DIR)/$(PROJECT_NAME).hex

all: $(HEX)

$(HEX): $(ELF)
	arm-none-eabi-objcopy -O ihex $< $@

$(ELF): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

flash: $(HEX)
	nrfjprog --program $(HEX) --sectorerase --reset
