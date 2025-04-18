#include "Joystick.h"

void configure_joystick()
{
    adc_gpio_init(VRX_PIN);
    adc_gpio_init(VRY_PIN);
}

joystick_position read_joystick() {
    joystick_position pos;

    adc_select_input(1);
    pos.x = adc_read();

    adc_select_input(0);
    pos.y = adc_read();

    return pos;
}