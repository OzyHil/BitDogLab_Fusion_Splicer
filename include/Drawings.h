#ifndef DRAWINGS_H
#define DRAWINGS_H

// Inclusão das bibliotecas necessárias
#include "General.h"  // Definições gerais do sistema
#include "Leds.h"     // Controle dos LEDs e cores

// Definição de constantes para o número de pixels da matriz e o máximo de quadros
#define NUM_PIXELS 25
#define MAX_FRAMES 50

// Função para atualizar a posição da fibra 1 com base nos valores VRX e VRY
led_positions update_fiber_1(int *matrix, int vrx, int vry);

// Função para atualizar a posição da fibra 2 com base nos valores VRX e VRY
led_positions update_fiber_2(int *matrix, int vrx, int vry);

// Função para atualizar as fibras e o LED central com base nos valores VRX e VRY
void update_fibers_and_center_led(int *matrix, int vrx, int vry);

#endif
