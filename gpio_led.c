#include "gpio_led.h"

static int sequence_position = 0;
static bool was_button_pressed = false;
static int button_press_time = 0;
static bool led_paused = false;
static led_color_t current_led_color = LED_OFF;

void gpio_led_init(void) {
    nrf_gpio_cfg_output(LED_RED);
    nrf_gpio_cfg_output(LED_GREEN);
    nrf_gpio_cfg_output(LED_BLUE);
    nrf_gpio_cfg_input(BUTTON_PIN, NRF_GPIO_PIN_PULLUP);
    set_led_color(LED_OFF);
}

void set_led_color(led_color_t color) {
    nrf_gpio_pin_write(LED_RED, 1);
    nrf_gpio_pin_write(LED_GREEN, 1);
    nrf_gpio_pin_write(LED_BLUE, 1);
    
    current_led_color = color;
    
    switch (color) {
        case LED_RED_COLOR: nrf_gpio_pin_write(LED_RED, 0); break;
        case LED_GREEN_COLOR: nrf_gpio_pin_write(LED_GREEN, 0); break;
        case LED_BLUE_COLOR: nrf_gpio_pin_write(LED_BLUE, 0); break;
        case LED_OFF: break;
    }
}

led_color_t char_to_led_color(char c) {
    switch (c) {
        case 'R': return LED_RED_COLOR;
        case 'G': return LED_GREEN_COLOR;
        case 'B': return LED_BLUE_COLOR;
        default: return LED_OFF;
    }
}

void process_led_sequence(bool button_pressed) {
    const int led_duration_ms = 500;
    static int time_counter = 0;
    
    if (button_pressed && !was_button_pressed) {
        button_press_time = time_counter;
        was_button_pressed = true;
        led_paused = false;
    }
    else if (!button_pressed && was_button_pressed) {
        was_button_pressed = false;
        if (current_led_color != LED_OFF) {
            led_paused = true;
        }
    }
    
    if (button_pressed) {
        int press_duration = time_counter - button_press_time;
        
        if (!led_paused) {
            int led_index = (press_duration / led_duration_ms) % SEQUENCE_LEN;
            led_color_t new_color = char_to_led_color(LED_SEQUENCE[led_index]);
            set_led_color(new_color);
            sequence_position = (led_index + 1) % SEQUENCE_LEN;
        }
    }
    else if (!led_paused) {
        set_led_color(LED_OFF);
    }
    
    time_counter++;
}
