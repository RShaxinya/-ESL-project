#include "nrf_delay.h"
#include "nrf.h"

void nrf_delay_ms(uint32_t ms)
{
    while (ms--)
    {
        nrf_delay_us(1000);
    }
}

void nrf_delay_us(uint32_t us)
{
    for (uint32_t i = 0; i < us * 4; i++)
    {
        __ASM volatile ("nop");
    }
}
