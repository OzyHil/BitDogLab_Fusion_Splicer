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
    loop_colors_one_by_one(pio, color);

    srand(time_us_32());
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (matrix[i] == 3)
            matrix[i] = 0;
    }

    int positions[] = {2, 7, 12, 17, 22};
    int index = rand() % 5;
    int chosen_pos = positions[index];

    matrix[chosen_pos] = 3;

    while (true)
    {
        // X = (16; 4082)
        // Y = (16; 4082)

        joystick_position pos = read_joystick();

        if (selected_fiber == 1)
            update_fiber_1(matrix, pos.x, pos.y);

        if (selected_fiber == 2)
            update_fiber_2(matrix, pos.x, pos.y);

        loop_colors_one_by_one(pio, color);

        sleep_ms(50);
    }
}