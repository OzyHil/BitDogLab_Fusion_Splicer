#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include "General.h"
#include "Leds.h"
#include "Drawings.h"

#define NUM_PIXELS 25
#define LED_MATRIX 7

extern int matrix[NUM_PIXELS];
typedef struct pio_refs
{
    PIO ref;
    uint offset;
    uint state_machine;
} refs;

refs init_pio();
uint32_t rgb_matrix(led_color color);
void loop_colors_one_by_one(refs pio, led_color color);
void convert_to_snake_rows(int *input, int *output);
int* drawing(uint16_t pattern_Id);

#endif