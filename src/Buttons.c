#include "Buttons.h"
#include "Led_Matrix.h"

uint32_t last_time_irq_A = 0;
uint32_t last_time_irq_B = 0;
uint32_t last_time_irq_J = 0;

volatile int8_t selected_fiber = 0;
volatile bool move_joined_fiber = false;
volatile bool alignment_locked = false;
volatile bool should_animate_fusion = false;

void button_irq_callback(uint gpio, uint32_t events)
{
    uint32_t current_time = get_absolute_time();

    if (gpio == BUTTON_A)
    {
        if ((current_time - last_time_irq_A) < debounce_delay)
            return;
        last_time_irq_A = current_time;

        if (!alignment_locked)
        {
            selected_fiber = (selected_fiber == 1) ? 0 : 1;
            printf("botao A");
        }
    }
    else if (gpio == BUTTON_B)
    {
        if ((current_time - last_time_irq_B) < debounce_delay || alignment_locked)
            return;
        last_time_irq_B = current_time;

        if (!alignment_locked)
        {
            selected_fiber = (selected_fiber == 2) ? 0 : 2;
            printf("botao B");
        }
    }
    else if (gpio == BUTTON_J)
    {
        if ((current_time - last_time_irq_J) < debounce_delay)
            return;
        last_time_irq_J = current_time;

        if (are_aligned())
        {
            alignment_locked = true;

            if (selected_fiber != 3 && !move_joined_fiber)
            {
                should_animate_fusion = true;
                selected_fiber = 3;
            }
            else if (selected_fiber == 3 && !move_joined_fiber)
            {
                move_joined_fiber = true;
                selected_fiber = -1;
            }
            else if (move_joined_fiber)
            {
                choose_random_position();
                loop_led_colors(scheme_1);
                move_joined_fiber = false;
                alignment_locked = false;
                selected_fiber = 0;
            }
        }
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
