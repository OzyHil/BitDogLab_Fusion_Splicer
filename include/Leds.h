#ifndef LEDS_H
#define LEDS_H

#include "General.h"

// Definições dos pinos conectados aos LEDs
#define GREEN_LED 11 
#define BLUE_LED 12  
#define RED_LED 13  
#define WRAP_PWM_LED 5  // PWM para controle de brilho

// Estrutura para representar uma cor RGB
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} led_color;

// Esquema de cores para diferentes partes do sistema
typedef struct {
    led_color fiber_1;
    led_color fiber_2;
    led_color alignment;
    led_color background;
} led_color_scheme;

// Posições ocupadas por uma fibra na matriz
typedef struct {
    int pos_1;
    int pos_2;
} led_positions;

// Cores pré-definidas (extern para serem definidas em outro arquivo)
extern const led_color GREEN;
extern const led_color YELLOW;
extern const led_color ORANGE;
extern const led_color CHARTREUSE;
extern const led_color CYAN;
extern const led_color BURGUNDY;
extern const led_color DARK;
extern const led_color BLUE;
extern const led_color PURPLE;
extern const led_color RED;
extern const led_color WHITE;

// Inicializa os pinos dos LEDs
void configure_leds();

// Ajusta o brilho de um LED via PWM
void set_led_brightness(uint gpio, uint8_t level);

// Define a cor de saída RGB no LED RGB
void set_led_color(led_color color);

// Obtém a posição de referência da fibra
int get_reference_position(led_positions fiber_pos, uint8_t fiber);

// Calcula a diferença entre posição atual e a posição escolhida
uint8_t get_diff_from_reference(int ref, uint8_t chosen_pos, uint8_t fiber);

// Aplica feedback com LED e buzzer conforme alinhamento
void apply_led_and_buzzer_feedback(int ref, uint8_t diff, uint8_t status);

#endif
