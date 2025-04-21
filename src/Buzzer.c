#include "Buzzer.h"

void configure_buzzer()
{
    init_pwm(BUZZER_A, WRAP_PWM_BUZZER);
}

void set_buzzer_level(uint gpio, uint16_t level)
{
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), level);
}
