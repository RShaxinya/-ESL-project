#ifndef GPIO_LED_H
#define GPIO_LED_H

#include "nrf_gpio.h"  

#define LED_SEQUENCE "RRGGGB"
#define SEQUENCE_LEN 6

#define LED_RED     23
#define LED_GREEN   24
#define LED_BLUE    25
#define BUTTON_PIN  28

typedef enum {
    LED_RED_COLOR,
    LED_GREEN_COLOR, 
    LED_BLUE_COLOR,
    LED_OFF
} led_color_t;

void gpio_led_init(void);
void set_led_color(led_color_t color);
void process_led_sequence(bool button_pressed);

#endif
