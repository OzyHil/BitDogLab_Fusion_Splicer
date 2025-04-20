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

typedef struct {
    int pos_1;
    int pos_2;
} led_positions;

extern const led_color GREEN;
extern const led_color YELLOW;
extern const led_color ORANGE;
extern const led_color CHARTREUSE;
extern const led_color CYAN;
extern const led_color BURGUNDY;
extern const led_color DARK;

void configure_leds();
void set_led_brightness(uint gpio, uint8_t level);
void set_led_color(led_color color);
void check_and_light_led(led_positions fiber_pos, uint8_t chosen_pos, uint8_t fiber);

#endif