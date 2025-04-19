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
    loop_colors_one_by_one(pio, color, 0);

    while (true)
    {
        // joystick_position pos = read_joystick();
        // printf("X: %d | Y: %d\n", pos.x, pos.y);
        // sleep_ms(500);
        loop_colors_one_by_one(pio, color, d_frame);
        sleep_ms(50);
    }
}