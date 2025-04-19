#include "Leds.h"

// const led_color GREEN = {.red = 0, .green = 35, .blue = 0};
// const led_color YELLOW = {.red = 35, .green = 35, .blue = 0};
// const led_color ORANGE = {.red = 35, .green = 12, .blue = 0};
// const led_color PURPLE = {.red = 35, .green = 0, .blue = 80};
// const led_color CYAN = {.red = 0, .green = 35, .blue = 35};
// const led_color DARK = {.red = 0, .green = 0, .blue = 0};

const led_color GREEN = {.red = 0, .green = 3, .blue = 0};
const led_color YELLOW = {.red = 3, .green = 3, .blue = 0};
const led_color ORANGE = {.red = 3, .green = 1, .blue = 0};
const led_color CHARTREUSE = {.red = 3, .green = 15, .blue = 0};
const led_color CYAN = {.red = 0, .green = 3, .blue = 3};
const led_color BURGUNDY = {.red = 3, .green = 0, .blue = 1};
const led_color DARK = {.red = 0, .green = 0, .blue = 0};

void configure_leds()
{
    const uint leds[] = {GREEN_LED, BLUE_LED, RED_LED};

    for (int i = 0; i < 3; i++)
    {
        init_pwm(leds[i]);
    }
}

void set_led_brightness(uint gpio, uint8_t level)
{
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), level);
}

void set_led_color(led_color color)
{
    set_led_brightness(RED_LED, color.red);
    set_led_brightness(GREEN_LED, color.green);
    set_led_brightness(BLUE_LED, color.blue);
}
