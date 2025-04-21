#include "General.h"
#include "Buttons.h"
#include "Leds.h"
#include "Joystick.h"
#include "Display.h"
#include "Buzzer.h"

void init_system_config()
{
    stdio_init_all();
    adc_init();
    set_sys_clock_khz(128000, false);
    srand(time_us_32());

    configure_buttons();
    configure_leds();
    configure_joystick();
    configure_i2c_display();
    configure_buzzer();
}

void configure_gpio(uint gpio, bool is_input, bool use_pull_up)
{
    gpio_init(gpio);
    gpio_set_dir(gpio, is_input ? GPIO_IN : GPIO_OUT);

    if (is_input && use_pull_up)
    {
        gpio_pull_up(gpio);
    }
}

void init_pwm(uint gpio, uint wrap)
{
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(gpio);
    pwm_set_clkdiv(slice, 16.0);
    pwm_set_wrap(slice, wrap);
    pwm_set_enabled(slice, true);
}

void init_adc(uint gpio)
{
    adc_gpio_init(gpio);
}
