#include "General.h"
#include "Buttons.h"
#include "Leds.h"
#include "Led_Matrix.h"
#include "Joystick.h"
#include "Display.h"

int main()
{
    init_system_config();

    pio = init_pio();
    int ref;
    uint8_t diff;
    uint16_t range = HIGHEST_AXIS_VALUE - LOWEST_AXIS_VALUE;

    init_color_schemes();
    choose_random_position();
    loop_led_colors(scheme_1);

    while (true)
    {
        joystick_position pos = read_joystick();

        if (selected_fiber == 1)
        {
            pos_fiber_1 = update_fiber_1(matrix, pos.x, pos.y);
            ref = get_reference_position(pos_fiber_1, 1);
            diff = get_diff_from_reference(ref, chosen_pos, 1);
            apply_led_and_buzzer_feedback(ref, diff);
            loop_led_colors(scheme_1);
        }
        else if (selected_fiber == 2)
        {
            pos_fiber_2 = update_fiber_2(matrix, pos.x, pos.y);
            ref = get_reference_position(pos_fiber_2, 2);
            diff = get_diff_from_reference(ref, chosen_pos, 2);
            apply_led_and_buzzer_feedback(ref, diff);
            loop_led_colors(scheme_1);
        }
        else if (selected_fiber == 0)
        {
            apply_led_and_buzzer_feedback(-1, -1);
        }
        else if (should_animate_fusion)
        {
            should_animate_fusion = false;
            apply_led_and_buzzer_feedback(-1, -1);
            animate_fiber_fusion();
        }
        else if (move_joined_fiber)
        {
            update_fibers_and_center_led(matrix, pos.x, pos.y);
            apply_led_and_buzzer_feedback(-1, -1);
            loop_led_colors(scheme_2);
        }

        uint16_t x_position = (NUM_LEDS_X * (int)(pos.x - LOWEST_AXIS_VALUE) / range);
        uint16_t y_position = (NUM_LEDS_Y * (int)(pos.y - LOWEST_AXIS_VALUE) / range);

        printf("%d; %d\n\n", x_position, y_position);
        update_display(x_position, y_position);
    }
}