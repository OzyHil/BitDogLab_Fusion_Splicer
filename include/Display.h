#ifndef DISPLAY_H
#define DISPLAY_H

// Inclusão das bibliotecas necessárias
#include "General.h"     // Definições gerais do sistema
#include "ssd1306.h"     // Controle do display OLED

// Definição de pinos e endereço do display I2C
#define I2C_PORT i2c1            // Porta I2C para comunicação
#define I2C_SDA 14               // Pino SDA para I2C
#define I2C_SCL 15               // Pino SCL para I2C
#define DISPLAY_ADDRESS 0x3C     // Endereço do display OLED

// Definição de valores para os eixos X e Y e limites de movimento
#define LOWEST_AXIS_VALUE 16     // Valor mínimo para o eixo
#define HIGHEST_AXIS_VALUE 4082  // Valor máximo para o eixo
#define NUM_LEDS_X 119           // Número de LEDs no eixo X
#define NUM_LEDS_Y 55            // Número de LEDs no eixo Y

// Função para configurar o display I2C
void configure_i2c_display();

// Função para atualizar a posição no display
void update_display(uint16_t x_position, uint16_t y_position);

#endif
