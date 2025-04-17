#include <stdio.h>
#include "pico/stdlib.h"

#define BUTTON_A 5
#define BUTTON_B 6
#define BUTTON_J 22

uint32_t last_time = 0;

void button_irq_callback(uint gpio, uint32_t events);
void configure_gpio(uint gpio, bool is_input, bool use_pull_up);
void configure_buttons();

int main()
{
    stdio_init_all();

    configure_buttons();

    while (true)
    {
        sleep_ms(10);
    }
}

void button_irq_callback(uint gpio, uint32_t events)
{
    uint32_t current_time = get_absolute_time();

    if ((current_time - last_time) < 250000)
        return;

    last_time = current_time;

    if (gpio == BUTTON_A)
    {
        printf("Button A is pressed\n");
    }
    else if (gpio == BUTTON_B)
    {
        printf("Button B is pressed\n");
    }
    else if (gpio == BUTTON_J)
    {
        printf("Button J is pressed\n");
    }
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

void configure_buttons()
{
    const uint buttons[] = {BUTTON_A, BUTTON_B, BUTTON_J};

    for (int i = 0; i < 3; i++)
    {
        configure_gpio(buttons[i], true, true);
        gpio_set_irq_enabled_with_callback(buttons[i], GPIO_IRQ_EDGE_FALL, true, button_irq_callback);
    }
}