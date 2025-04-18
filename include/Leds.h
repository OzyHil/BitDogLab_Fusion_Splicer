#ifndef LEDS_H
#define LEDS_H

#include "General.h"

#define GREEN_LED 11 
#define BLUE_LED 12  
#define RED_LED 13  

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} led_color;

extern const led_color GREEN;
extern const led_color YELLOW;
extern const led_color ORANGE;

void configure_leds();
void set_led_brightness(uint gpio, uint8_t level);
void set_led_color(led_color color);

#endif