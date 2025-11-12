#include <stdbool.h>
#include <stdint.h>


#define BUTTON_PIN ((1 << 5) | 6)   
#define LED_RED    ((0 << 5) | 8)   
#define LED_GREEN  ((1 << 5) | 9)  
#define LED_BLUE   ((0 << 5) | 12)  


void nrf_gpio_cfg_output(uint32_t pin) {
    
}

void nrf_gpio_cfg_input(uint32_t pin, uint32_t pull) {
    
}

void nrf_gpio_pin_write(uint32_t pin, uint32_t value) {
    
}

uint32_t nrf_gpio_pin_read(uint32_t pin) {
    
    static int counter = 0;
    counter++;
    return (counter % 20 == 0) ? 0 : 1;
}


void simple_delay(uint32_t milliseconds) {
    for (volatile uint32_t i = 0; i < milliseconds * 1000; i++);
}


void set_rgb_color(bool red, bool green, bool blue) {
    nrf_gpio_pin_write(LED_RED, !red);
    nrf_gpio_pin_write(LED_GREEN, !green); 
    nrf_gpio_pin_write(LED_BLUE, !blue);
}


void gpio_led_init(void) {
    
    nrf_gpio_cfg_input(BUTTON_PIN, 1); 
    
    
    nrf_gpio_cfg_output(LED_RED);
    nrf_gpio_cfg_output(LED_GREEN);
    nrf_gpio_cfg_output(LED_BLUE);
    
    
    nrf_gpio_pin_write(LED_RED, 1);
    nrf_gpio_pin_write(LED_GREEN, 1);
    nrf_gpio_pin_write(LED_BLUE, 1);
}


void process_led_sequence(bool button_state) {
    static int color_state = 0;
    static int counter = 0;
    
    if (button_state) {
        
        switch(color_state) {
            case 0: set_rgb_color(1, 0, 0); break; 
            case 1: set_rgb_color(0, 1, 0); break; 
            case 2: set_rgb_color(0, 0, 1); break; 
            case 3: set_rgb_color(1, 1, 0); break; 
            case 4: set_rgb_color(0, 1, 1); break;
            case 5: set_rgb_color(1, 0, 1); break; 
        }
        color_state = (color_state + 1) % 6;
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
        bool button_state = (nrf_gpio_pin_read(BUTTON_PIN) == 0);
        process_led_sequence(button_state);
        simple_delay(500); 
    }
}
