#include "nrf_gpio.h"

#define LED_RED     23
#define LED_GREEN   24  
#define LED_BLUE    25
#define LED_YELLOW  26

// Простая функция задержки
void simple_delay(uint32_t milliseconds) {
    for (volatile uint32_t i = 0; i < milliseconds * 1000; i++) {
        // Пустой цикл
    }
}

void blink_single_led(uint32_t led_pin, int count) {
    for (int i = 0; i < count; i++) {
        nrf_gpio_pin_write(led_pin, 0);  // ВКЛ
        simple_delay(300);
        nrf_gpio_pin_write(led_pin, 1);  // ВЫКЛ
        simple_delay(300);
    }
}

int main(void) {
    nrf_gpio_cfg_output(LED_RED);
    nrf_gpio_cfg_output(LED_GREEN);
    nrf_gpio_cfg_output(LED_BLUE);
    nrf_gpio_cfg_output(LED_YELLOW);
    
    nrf_gpio_pin_write(LED_RED, 1);
    nrf_gpio_pin_write(LED_GREEN, 1);
    nrf_gpio_pin_write(LED_BLUE, 1);
    nrf_gpio_pin_write(LED_YELLOW, 1);

    while (true) {
        blink_single_led(LED_RED, 6);
        simple_delay(1000);  // Пауза 1 сек
        
        blink_single_led(LED_GREEN, 4);
        simple_delay(1000);  // Пауза 1 сек
        
        simple_delay(2000);  // Пауза 2 сек (вместо синего)
        
        blink_single_led(LED_YELLOW, 4);
        simple_delay(2000);  // Пауза 2 сек
    }
}