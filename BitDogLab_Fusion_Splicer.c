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
    int ref;
    uint8_t diff;
    uint16_t range = HIGHEST_AXIS_VALUE - LOWEST_AXIS_VALUE;

    led_color_scheme scheme_1 = {
        .fiber_1 = CYAN,
        .fiber_2 = BURGUNDY,
        .alignment = CHARTREUSE,
        .background = DARK};

    choose_random_position();
    loop_led_colors(pio, scheme_1);

    while (true)
    {
        joystick_position pos = read_joystick();


        if (selected_fiber == 1)
        {
            pos_fiber_1 = update_fiber_1(matrix, pos.x, pos.y);
            ref = get_reference_position(pos_fiber_1, 1);
            diff = get_diff_from_reference(ref, chosen_pos, 1);
            apply_led_and_buzzer_feedback(ref, diff);
            loop_led_colors(pio, scheme_1);
        }
        else if (selected_fiber == 2)
        {
            pos_fiber_2 = update_fiber_2(matrix, pos.x, pos.y);
            ref = get_reference_position(pos_fiber_2, 2);
            diff = get_diff_from_reference(ref, chosen_pos, 2);
            apply_led_and_buzzer_feedback(ref, diff);
            loop_led_colors(pio, scheme_1);
        }
        
        uint16_t x_position = roundf(NUM_LEDS_X * (float)(pos.x - LOWEST_AXIS_VALUE) / range);
        uint16_t y_position = roundf(NUM_LEDS_Y * (float)(pos.y - LOWEST_AXIS_VALUE) / range);
        update_display(x_position, y_position);
    }
}