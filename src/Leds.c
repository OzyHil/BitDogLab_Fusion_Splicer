#include "Leds.h"

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

void check_and_light_led(led_positions fiber_pos, uint8_t chosen_pos, uint8_t fiber)
{
    int ref = -1;

    if (fiber == 1)
    {
        if (fiber_pos.pos_1 >= 0 && fiber_pos.pos_2 >= 0)
            ref = (fiber_pos.pos_1 > fiber_pos.pos_2) ? fiber_pos.pos_1 : fiber_pos.pos_2;
        else if (fiber_pos.pos_1 >= 0)
            ref = fiber_pos.pos_1;
        else if (fiber_pos.pos_2 >= 0)
            ref = fiber_pos.pos_2;
    }
    else if (fiber == 2)
    {
        if (fiber_pos.pos_1 >= 0 && fiber_pos.pos_2 >= 0)
            ref = (fiber_pos.pos_1 < fiber_pos.pos_2) ? fiber_pos.pos_1 : fiber_pos.pos_2;
        else if (fiber_pos.pos_1 >= 0)
            ref = fiber_pos.pos_1;
        else if (fiber_pos.pos_2 >= 0)
            ref = fiber_pos.pos_2;
    }

    if (ref < 0)
    {
        set_led_color(DARK);
        return;
    }

    uint8_t diff;
    if (fiber == 1)
        diff = chosen_pos - ref;
    else
        diff = ref - chosen_pos;

    if (diff == 1)
        set_led_color(GREEN);
    else if (diff == 2)
        set_led_color(YELLOW);
    else
        set_led_color(ORANGE);
}