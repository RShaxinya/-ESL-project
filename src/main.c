#include <stdint.h>


#define NRF_P0_BASE 0x50000000
#define NRF_P1_BASE 0x50000300
#define GPIO_OUTSET_OFFSET 0x508
#define GPIO_OUTCLR_OFFSET 0x50C
#define GPIO_DIRSET_OFFSET 0x518
#define GPIO_IN_OFFSET 0x510
#define GPIO_PIN_CNF_OFFSET 0x700


#define LED_RED    (0 * 32 + 6)   
#define LED_GREEN  (0 * 32 + 8)    
#define LED_BLUE   (1 * 32 + 9)   
#define BUTTON_PIN (1 * 32 + 6)   

void SystemInit(void) {}


void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 5000; i++) {
        __asm__ volatile ("nop");
    }
}
void gpio_pin_set(uint32_t pin) {
    uint32_t port = pin / 32;
    uint32_t pin_num = pin % 32;
    volatile uint32_t* outset = (volatile uint32_t*)((port == 0 ? NRF_P0_BASE : NRF_P1_BASE) + GPIO_OUTSET_OFFSET);
    *outset = (1 << pin_num);
}

void gpio_pin_clear(uint32_t pin) {
    uint32_t port = pin / 32;
    uint32_t pin_num = pin % 32;
    volatile uint32_t* outclr = (volatile uint32_t*)((port == 0 ? NRF_P0_BASE : NRF_P1_BASE) + GPIO_OUTCLR_OFFSET);
    *outclr = (1 << pin_num);
}

uint32_t gpio_pin_read(uint32_t pin) {
    uint32_t port = pin / 32;
    uint32_t pin_num = pin % 32;
    volatile uint32_t* in_reg = (volatile uint32_t*)((port == 0 ? NRF_P0_BASE : NRF_P1_BASE) + GPIO_IN_OFFSET);
    return (*in_reg & (1 << pin_num));
}

int main(void) {
    
    volatile uint32_t* dirset0 = (volatile uint32_t*)(NRF_P0_BASE + GPIO_DIRSET_OFFSET);
    volatile uint32_t* dirset1 = (volatile uint32_t*)(NRF_P1_BASE + GPIO_DIRSET_OFFSET);
    *dirset0 = (1 << 6) | (1 << 8);  
    *dirset1 = (1 << 9);             
    
    
    volatile uint32_t* button_cnf = (volatile uint32_t*)(NRF_P1_BASE + GPIO_PIN_CNF_OFFSET + 6 * 4);
    *button_cnf = (3 << 2);  
    
    
    gpio_pin_set(LED_RED);
    gpio_pin_set(LED_GREEN);
    gpio_pin_set(LED_BLUE);
    
    
    uint16_t pwm_counter = 0;
    uint16_t duty_cycle = 0;
    uint8_t increasing = 1;
    uint8_t current_led_index = 0;
    uint8_t blinking_enabled = 1;
    
    
    const uint8_t led_sequence[] = {LED_RED, LED_GREEN, LED_BLUE, LED_RED};
    
    
    uint32_t last_press_time = 0;
    uint8_t click_count = 0;
    uint32_t time_counter = 0;
    
    while (1) {
        time_counter++;
        
        if (blinking_enabled) {
            
uint8_t current_led = led_sequence[current_led_index];
            
            
            gpio_pin_set(LED_RED);
            gpio_pin_set(LED_GREEN);
            gpio_pin_set(LED_BLUE);
            
            
            if (pwm_counter < duty_cycle) {
                gpio_pin_clear(current_led);
            }
            
            pwm_counter++;
            if (pwm_counter >= 1000) {
                pwm_counter = 0;
                
                
                if (increasing) {
                    duty_cycle += 5;
                    if (duty_cycle >= 1000) {
                        duty_cycle = 1000;
                        increasing = 0;
                    }
                } else {
                    duty_cycle -= 5;
                    if (duty_cycle <= 0) {
                        duty_cycle = 0;
                        increasing = 1;
                        
                        current_led_index = (current_led_index + 1) % 4;
                    }
                }
            }
        }
        
        
        if (!gpio_pin_read(BUTTON_PIN)) {
            delay_ms(50);  
            if (!gpio_pin_read(BUTTON_PIN)) {
                uint32_t current_time = time_counter;
                
                
                if (current_time - last_press_time < 300) {
                    
                    blinking_enabled = !blinking_enabled;
                    click_count = 0;
                } else {
                    click_count = 1;
                }
                last_press_time = current_time;
                
                
                while (!gpio_pin_read(BUTTON_PIN)) {
                    delay_ms(10);
                }
                delay_ms(50);
            }
        }
        
        delay_ms(1);  
    }
    
    return 0;
}
