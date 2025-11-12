# Workshop 3: GPIO LED Control

## Task
Implement GPIO HAL functions to control LED sequence with button:
- Play sequence only when button pressed
- Continue from previous position  
- Optional: LED stays on when released

## Files
- `main.c` - Main application with button handling
- `gpio_led.h/c` - LED sequence control functions
- `nrf_gpio.h` - GPIO HAL functions
- ## Сборка и запуск:
make
./rgb_app

## Features
- Custom GPIO implementation (no boards.h)
- Button-controlled playback
- State memory between presses
- Modular code structure
