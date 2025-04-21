#ifndef DISPLAY_H
#define DISPLAY_H

#include "General.h"
#include "ssd1306.h"

#define I2C_PORT i2c1            
#define I2C_SDA 14               
#define I2C_SCL 15               
#define DISPLAY_ADDRESS 0x3C     
#define LOWEST_AXIS_VALUE 16     
#define HIGHEST_AXIS_VALUE 4082  
#define NUM_LEDS_X 119
#define NUM_LEDS_Y 55  

void configure_i2c_display();
void update_display(uint16_t x_position, uint16_t y_position);

#endif