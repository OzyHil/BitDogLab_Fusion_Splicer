#ifndef DRAWINGS_H
#define DRAWINGS_H

#include "General.h"
#include "Leds.h"

#define NUM_PIXELS 25
#define MAX_FRAMES 50

led_positions update_fiber_1(int *matrix, int vrx, int vry);
led_positions update_fiber_2(int *matrix, int vrx, int vry);

#endif
