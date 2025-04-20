#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/pio.h"
#include "pio_matrix.pio.h"
#include "hardware/clocks.h"
#include "hardware/i2c.h"
#include "math.h"

void init_system_config();
void configure_gpio(uint gpio, bool is_input, bool use_pull_up);
void init_pwm(uint gpio);
void init_adc(uint gpio);

#endif