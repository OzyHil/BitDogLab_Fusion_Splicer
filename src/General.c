#include "General.h"

void configure_gpio(uint gpio, bool is_input, bool use_pull_up)
{
    gpio_init(gpio);
    gpio_set_dir(gpio, is_input ? GPIO_IN : GPIO_OUT);

    if (is_input && use_pull_up)
    {
        gpio_pull_up(gpio);
    }
}

void init_pwm(uint gpio)
{
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_wrap(slice_num, 255);
    pwm_set_enabled(slice_num, true);
}

void init_adc(uint gpio)
{
    adc_gpio_init(gpio);
}
