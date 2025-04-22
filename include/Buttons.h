#ifndef BUTTONS_H
#define BUTTONS_H

// Inclusão da biblioteca geral do sistema
#include "General.h"

// Definição dos pinos dos botões
#define BUTTON_A 5    // Botão A
#define BUTTON_B 6    // Botão B
#define BUTTON_J 22   // Botão J (Joystick)

// Definição do delay para debounce (evitar múltiplos acionamentos)
#define debounce_delay 300000

// Variáveis globais para controle do estado dos botões
extern volatile int8_t selected_fiber;       // Fibra selecionada
extern volatile bool move_joined_fiber;     // Flag para mover fibra unida
extern volatile bool should_animate_fusion;  // Flag para animação de fusão

// Função de callback para interrupção de botões
void button_irq_callback(uint gpio, uint32_t events);

// Função para configurar os botões
void configure_buttons();

#endif
