#ifndef GENERAL_H
#define GENERAL_H

// Inclusão das bibliotecas padrão e específicas do hardware
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "pico/stdlib.h"    // Biblioteca principal para o Raspberry Pi Pico
#include "hardware/pwm.h"   // Controle de PWM (Pulse Width Modulation)
#include "hardware/adc.h"   // Controle de ADC (Analog to Digital Converter)
#include "hardware/pio.h"   // Programação de E/S PIO (Programmable I/O)
#include "pio_matrix.pio.h" // Programa específico para controle da matriz de LEDs
#include "hardware/clocks.h" // Controle de clocks
#include "hardware/i2c.h"   // Comunicação I2C
#include "math.h"           // Funções matemáticas

// Função para inicializar a configuração do sistema (clocks, I/O, etc.)
void init_system_config();

// Função para configurar o GPIO (entrada ou saída com pull-up opcional)
void configure_gpio(uint gpio, bool is_input, bool use_pull_up);

// Função para inicializar o PWM em um pino específico com um valor de wrap
void init_pwm(uint gpio, uint wrap);

// Função para inicializar o ADC em um pino específico
void init_adc(uint gpio);

#endif