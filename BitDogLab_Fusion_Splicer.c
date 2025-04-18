#include "General.h"
#include "Buttons.h"
#include "Leds.h"
#include "Joystick.h"

int main()
{
    stdio_init_all();
    adc_init();

    configure_buttons();
    configure_leds();
    configure_joystick();

    while (true)
    {
        joystick_position pos = read_joystick();
        printf("X: %d | Y: %d\n", pos.x, pos.y);
        sleep_ms(500);
    }
}