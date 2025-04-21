#ifndef LEDS_H
#define LEDS_H

#include "General.h"

#define GREEN_LED 11 
#define BLUE_LED 12  
#define RED_LED 13  
#define WRAP_PWM_LED 5  

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} led_color;

typedef struct {
    led_color fiber_1;
    led_color fiber_2;
    led_color alignment;
    led_color background;
} led_color_scheme;

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
int get_reference_position(led_positions fiber_pos, uint8_t fiber);
uint8_t get_diff_from_reference(int ref, uint8_t chosen_pos, uint8_t fiber);
void apply_led_and_buzzer_feedback(int ref, uint8_t diff);
#endif