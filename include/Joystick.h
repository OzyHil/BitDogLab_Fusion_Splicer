#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "General.h"

// Definição dos pinos conectados aos eixos do joystick
#define VRX_PIN 26   // Eixo X
#define VRY_PIN 27   // Eixo Y

// Limites de leitura dos eixos do joystick
#define LOWEST_AXIS_VALUE 16   // Valor mínimo do eixo
#define HIGHEST_AXIS_VALUE 4082 // Valor máximo do eixo

// Estrutura que armazena a posição (X, Y) do joystick
typedef struct {
    uint32_t x; // Posição no eixo X
    uint32_t y; // Posição no eixo Y
} joystick_position;

// Função para configurar o joystick
void configure_joystick();

// Função para ler a posição atual do joystick
joystick_position read_joystick();

#endif
