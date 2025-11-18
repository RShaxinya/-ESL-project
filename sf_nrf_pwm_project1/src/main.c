#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_drv_pwm.h"
#include "nrfx_gpiote.h"
#include "app_timer.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_drv_clock.h"
#include "boards.h"

#define BUTTON_PIN  BUTTON_1
#define LED_PIN     BSP_LED_0

static nrf_drv_pwm_t m_pwm0 = NRF_DRV_PWM_INSTANCE(0);

static nrf_pwm_values_common_t seq_values[1];
static nrf_drv_pwm_sequence_t const seq =
{
    .values.p_common = seq_values,
    .length          = 1,
    .repeats         = 0,
    .end_delay       = 0
};

static bool pwm_running = false;
static uint8_t duty_cycle = 0;
static bool increasing = true;

void button_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    static uint32_t last_time = 0;
    uint32_t current_time = app_timer_cnt_get() * 1000 / APP_TIMER_CLOCK_FREQ; // мс

    if(current_time - last_time < 200) // двойной клик
    {
        pwm_running = !pwm_running;
        if(pwm_running) NRF_LOG_INFO("PWM started");
        else             NRF_LOG_INFO("PWM stopped");
    }
    last_time = current_time;
}

void pwm_init(void)
{
    nrf_drv_pwm_config_t config = NRF_DRV_PWM_DEFAULT_CONFIG;
    config.output_pins[0] = LED_PIN;
    config.base_clock = NRF_PWM_CLK_1MHz;
    config.count_mode = NRF_PWM_MODE_UP;
    config.top_value = 1000; // 1kHz
    config.load_mode = NRF_PWM_LOAD_COMMON;
    config.step_mode = NRF_PWM_STEP_AUTO;

    nrf_drv_pwm_init(&m_pwm0, &config, NULL);
}

int main(void)
{
    nrf_drv_clock_init();
    nrf_drv_clock_lfclk_request(NULL);

    NRF_LOG_INIT(NULL);
    NRF_LOG_DEFAULT_BACKENDS_INIT();
    NRF_LOG_INFO("PWM Project started");

    if(!nrf_drv_gpiote_is_init())
        nrf_drv_gpiote_init();

    nrf_drv_gpiote_in_config_t button_config = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    button_config.pull = NRF_GPIO_PIN_PULLUP;
    nrf_drv_gpiote_in_init(BUTTON_PIN, &button_config, button_handler);
    nrf_drv_gpiote_in_event_enable(BUTTON_PIN, true);

    pwm_init();

    nrf_drv_pwm_simple_playback(&m_pwm0, &seq, 1, NRF_DRV_PWM_FLAG_LOOP);

    while(true)
    {
        if(pwm_running)
        {
            if(increasing) duty_cycle++;
            else           duty_cycle--;

            if(duty_cycle >= 100) increasing = false;
            if(duty_cycle <= 0)   increasing = true;

            seq_values[0] = duty_cycle * 10;
        }

        NRF_LOG_FLUSH();
        nrf_delay_ms(10);
    }
}
