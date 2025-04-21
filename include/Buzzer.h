#ifndef BUZZER_H
#define BUZZER_H

#include "General.h"

#define BUZZER_A 21  
#define WRAP_PWM_BUZZER 30000

void configure_buzzer();
void set_buzzer_level(uint gpio, uint16_t level);

#endif