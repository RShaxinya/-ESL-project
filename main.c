#include <stdbool.h>
#include <stdint.h>

#define BUTTON_PIN ((1 << 5) | 6)
#define LED_RED    ((0 << 5) | 8)
#define LED_GREEN  ((1 << 5) | 9)
#define LED_BLUE   ((0 << 5) | 12)

void nrf_gpio_cfg_output(uint32_t pin) {}
void nrf_gpio_cfg_input(uint32_t pin, uint32_t pull) {}
void nrf_gpio_pin_write(uint32_t pin, uint32_t value) {}
uint32_t nrf_gpio_pin_read(uint32_t pin) { return 1; }

void simple_delay(uint32_t ms) {
    for(volatile uint32_t i = 0; i < ms * 10000; i++);
}

void set_rgb_color(bool r, bool g, bool b) {
    nrf_gpio_pin_write(LED_RED, !r);
    nrf_gpio_pin_write(LED_GREEN, !g);
    nrf_gpio_pin_write(LED_BLUE, !b);
}

void gpio_led_init(void) {
    nrf_gpio_cfg_input(BUTTON_PIN, 1);
    nrf_gpio_cfg_output(LED_RED);
    nrf_gpio_cfg_output(LED_GREEN);
    nrf_gpio_cfg_output(LED_BLUE);
    set_rgb_color(0, 0, 0);
}

void process_led_sequence(bool btn) {
    static int state = 0;
    static int counter = 0;
    
    if (btn) {
        switch(state) {
            case 0: set_rgb_color(1, 0, 0); break;
            case 1: set_rgb_color(0, 1, 0); break;
            case 2: set_rgb_color(0, 0, 1); break;
            case 3: set_rgb_color(1, 1, 0); break;
            case 4: set_rgb_color(0, 1, 1); break;
            case 5: set_rgb_color(1, 0, 1); break;
        }
        state = (state + 1) % 6;
    } else {
        switch(counter % 6) {
            case 0: set_rgb_color(1, 0, 0); break;
            case 1: set_rgb_color(0, 1, 0); break;
            case 2: set_rgb_color(0, 0, 1); break;
            case 3: set_rgb_color(1, 1, 0); break;
            case 4: set_rgb_color(0, 1, 1); break;
            case 5: set_rgb_color(1, 0, 1); break;
        }
        counter++;
    }
}

int main(void) {
    gpio_led_init();
    while (1) {
        bool btn = (nrf_gpio_pin_read(BUTTON_PIN) == 0);
        process_led_sequence(btn);
        simple_delay(500);
    }
}
