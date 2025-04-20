#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "General.h"

#define VRX_PIN 26
#define VRY_PIN 27      
#define LOWEST_AXIS_VALUE 16   
#define HIGHEST_AXIS_VALUE 4082  
typedef struct {
    uint32_t x;
    uint32_t y;
} joystick_position;


void configure_joystick();
joystick_position read_joystick();

#endif