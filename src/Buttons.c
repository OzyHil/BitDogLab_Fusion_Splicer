#include "Buttons.h"
#include "Leds.h"

uint32_t last_time_irq = 0;

void button_irq_callback(uint gpio, uint32_t events)
{
    uint32_t current_time = get_absolute_time();

    if ((current_time - last_time_irq) < 250000)
        return;

    last_time_irq = current_time;

    if (gpio == BUTTON_A)
    {
        set_led_color(ORANGE);
    }
    else if (gpio == BUTTON_B)
    {
        set_led_color(YELLOW);
    }
    else if (gpio == BUTTON_J)
    {
        set_led_color(GREEN);
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
