#include "nrf_gpio.h"

static int button_counter = 0;

void nrf_gpio_cfg_output(uint32_t pin) {
    
}

void nrf_gpio_cfg_input(uint32_t pin, uint32_t pull) {
    
}

void nrf_gpio_pin_write(uint32_t pin, uint32_t value) {
    
}

uint32_t nrf_gpio_pin_read(uint32_t pin) {
    button_counter++;
    if (button_counter % 1000 == 0) {
        return 0; 
    }
    return 1; 
}
