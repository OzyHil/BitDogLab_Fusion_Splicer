#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include "General.h"
#include "Leds.h"
#include "Drawings.h"

#define NUM_PIXELS 25
#define LED_MATRIX 7

extern int matrix[NUM_PIXELS];
extern volatile led_positions pos_fiber_1;
extern volatile led_positions pos_fiber_2;
extern volatile led_positions pos_fiber;
extern volatile uint8_t chosen_pos;

extern led_color_scheme scheme_1;
extern led_color_scheme scheme_2;

typedef struct
{
    PIO ref;
    uint offset;
    uint state_machine;
} refs;

extern refs pio;

refs init_pio();
uint32_t rgb_matrix(led_color color);
void loop_led_colors(led_color_scheme colors);
void convert_to_snake_rows(int *input, int *output);
int *drawing(uint16_t pattern_Id);
void choose_random_position();
bool are_aligned();
void init_color_schemes();
void animate_fiber_fusion();

#endif