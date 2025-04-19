#ifndef BUTTONS_H
#define BUTTONS_H

#include "Leds.h"

#define BUTTON_A 5   
#define BUTTON_B 6
#define BUTTON_J 22

#define debounce_delay 300000

extern volatile int8_t selected_fiber;

void button_irq_callback(uint gpio, uint32_t events);
void configure_buttons();

#endif