#include "Buttons.h"

uint32_t last_time_irq_A = 0;
uint32_t last_time_irq_B = 0;
uint32_t last_time_irq_J = 0;

volatile int8_t selected_fiber = 0;

void button_irq_callback(uint gpio, uint32_t events)
{
    uint32_t current_time = get_absolute_time();

    if (gpio == BUTTON_A)
    {
        if ((current_time - last_time_irq_A) < debounce_delay)
            return;
        last_time_irq_A = current_time;
        selected_fiber = (selected_fiber == 1) ? 0 : 1;
    }
    else if (gpio == BUTTON_B)
    {
        if ((current_time - last_time_irq_B) < debounce_delay)
            return;
        last_time_irq_B = current_time;
        selected_fiber = (selected_fiber == 2) ? 0 : 2;
    }
    else if (gpio == BUTTON_J)
    {
        if ((current_time - last_time_irq_J) < debounce_delay)
            return;
        last_time_irq_J = current_time;
        selected_fiber = 0;
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
