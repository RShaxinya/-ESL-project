#include "nrf_gpio.h"
#include "gpio_led.h"

void simple_delay(uint32_t milliseconds) {
    for (volatile uint32_t i = 0; i < milliseconds * 1000; i++);
}

int main(void) {
    gpio_led_init();
    
    while (1) {
        bool button_state = (nrf_gpio_pin_read(BUTTON_PIN) == 0);
        process_led_sequence(button_state);
        simple_delay(50);
    }
}
