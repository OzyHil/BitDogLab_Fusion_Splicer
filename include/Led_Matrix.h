#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include "General.h"
#include "Leds.h"
#include "Drawings.h"

// Total de LEDs na matriz (5x5)
#define NUM_PIXELS 25

// Pino conectado à matriz de LEDs
#define LED_MATRIX 7

// Estado atual da matriz de LEDs
extern int matrix[NUM_PIXELS];

// Posições das fibras na matriz
extern volatile led_positions pos_fiber_1;
extern volatile led_positions pos_fiber_2;
extern volatile led_positions pos_fiber;

// Posição central escolhida para alinhamento
extern volatile uint8_t chosen_pos;

// Esquemas de cores utilizados
extern led_color_scheme scheme_1;
extern led_color_scheme scheme_2;

// Estrutura para armazenar referências do PIO
typedef struct
{
    PIO ref;              // Referência ao PIO (pio0 ou pio1)
    uint offset;          // Offset do programa carregado
    uint state_machine;   // Máquina de estado usada
} refs;

// Referência PIO global
extern refs pio;

// Inicializa o PIO com o programa da matriz
refs init_pio();

// Converte uma cor RGB para o formato aceito pela matriz
uint32_t rgb_matrix(led_color color);

// Exibe as cores da matriz de acordo com o esquema fornecido
void loop_led_colors(led_color_scheme colors);

// Converte a matriz para o formato zig-zag usado pela fita de LEDs
void convert_to_snake_rows(int *input, int *output);

// Retorna um desenho com base no ID do padrão
int *drawing(uint16_t pattern_Id);

// Escolhe uma posição aleatória para o alinhamento
void choose_random_position();

// Verifica se as fibras estão alinhadas corretamente
bool are_aligned();

// Inicializa os esquemas de cores
void init_color_schemes();

// Anima o processo de fusão das fibras com efeitos de LED
void animate_fiber_fusion();

#endif
