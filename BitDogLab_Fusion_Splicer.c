#include "General.h"
#include "Buttons.h"
#include "Leds.h"
#include "Led_Matrix.h"
#include "Joystick.h"

int main()
{
    init_system_config();

    refs pio = init_pio();
    led_color color = CHARTREUSE;

    uint8_t chosen_pos = choose_random_position(matrix);

    loop_led_colors(pio, color);

    led_positions positions_fiber_1;
    led_positions positions_fiber_2;

    while (true)
    {
        joystick_position pos = read_joystick();

        if (selected_fiber == 1)
        {
            positions_fiber_1 = update_fiber_1(matrix, pos.x, pos.y);
            check_and_light_led(positions_fiber_1, chosen_pos, 1);
            loop_led_colors(pio, color);
        }
        else if (selected_fiber == 2)
        {
            positions_fiber_2 = update_fiber_2(matrix, pos.x, pos.y);
            check_and_light_led(positions_fiber_2, chosen_pos, 2);
            loop_led_colors(pio, color);
        }
        sleep_ms(10);
    }
}