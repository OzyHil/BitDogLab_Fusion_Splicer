#include "General.h"
#include "Buttons.h"
#include "Leds.h"
#include "Led_Matrix.h"
#include "Joystick.h"
#include "Display.h"

int main()
{
    init_system_config();

    refs pio = init_pio();

    led_color_scheme scheme_1 = {
        .fiber_1 = CYAN,
        .fiber_2 = BURGUNDY,
        .alignment = CHARTREUSE,
        .background = DARK};

    uint8_t chosen_pos = choose_random_position(matrix);

    loop_led_colors(pio, scheme_1);

    led_positions pos_fiber_1;
    led_positions pos_fiber_2;

    uint16_t range = HIGHEST_AXIS_VALUE - LOWEST_AXIS_VALUE;

    while (true)
    {
        joystick_position pos = read_joystick();

        if (selected_fiber == 1)
        {
            pos_fiber_1 = update_fiber_1(matrix, pos.x, pos.y);
            check_and_light_led(pos_fiber_1, chosen_pos, 1);
            loop_led_colors(pio, scheme_1);
        }
        else if (selected_fiber == 2)
        {
            pos_fiber_2 = update_fiber_2(matrix, pos.x, pos.y);
            check_and_light_led(pos_fiber_2, chosen_pos, 2);
            loop_led_colors(pio, scheme_1);
        }
        
        uint16_t x_position = roundf(NUM_LEDS_X * (float)(pos.x - LOWEST_AXIS_VALUE) / range);
        uint16_t y_position = roundf(NUM_LEDS_Y * (float)(pos.y - LOWEST_AXIS_VALUE) / range);
        update_display(x_position, y_position);
        
    }

}