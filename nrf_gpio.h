#ifndef NRF_GPIO_H
#define NRF_GPIO_H

#include <stdint.h>
#include <stdbool.h>

#define NRF_GPIO_PIN_PULLUP 1

void nrf_gpio_cfg_output(uint32_t pin);
void nrf_gpio_cfg_input(uint32_t pin, uint32_t pull);
void nrf_gpio_pin_write(uint32_t pin, uint32_t value);
uint32_t nrf_gpio_pin_read(uint32_t pin);

#endif
