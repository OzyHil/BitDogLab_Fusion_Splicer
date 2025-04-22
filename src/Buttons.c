#include "Buttons.h"    // Header com definições relacionadas aos botões
#include "Led_Matrix.h" // Header com definições da matriz de LEDs

// Variáveis de controle para debounce (evitar múltiplos acionamentos)
uint32_t last_time_irq_A = 0;
uint32_t last_time_irq_B = 0;
uint32_t last_time_irq_J = 0;

// Variáveis de controle de estado
volatile int8_t selected_fiber = 0;          // Indica qual fibra está selecionada (0, 1, 2 ou 3 para combinada)
volatile bool move_joined_fiber = false;     // Indica se a fibra combinada deve ser movida
volatile bool alignment_locked = false;      // Indica se o alinhamento das fibras está travado
volatile bool should_animate_fusion = false; // Indica se a fusão deve ser animada

// Função de interrupção para os botões
void button_irq_callback(uint gpio, uint32_t events)
{
    uint32_t current_time = get_absolute_time(); // Pega o tempo atual (para debounce)

    if (gpio == BUTTON_A)
    {
        // Verifica debounce
        if ((current_time - last_time_irq_A) < debounce_delay)
            return;
        last_time_irq_A = current_time;

        // Alterna entre as fibras 0 e 1 se o alinhamento não estiver travado
        if (!alignment_locked)
        {
            if (selected_fiber == 0)
            {
                selected_fiber = 1;
                printf("=== Fibra 1 selecionada.\n");
            }
            else if (selected_fiber == 1)
            {
                selected_fiber = 0;
                printf("=== Fibra 1 desselecionada.\n");
            }
        }
    }
    else if (gpio == BUTTON_B)
    {
        // Verifica debounce e se o alinhamento está travado
        if ((current_time - last_time_irq_B) < debounce_delay || alignment_locked)
            return;
        last_time_irq_B = current_time;

        // Alterna entre as fibras 0 e 2 se o alinhamento não estiver travado
        if (!alignment_locked)
        {
            if (selected_fiber == 0)
            {
                selected_fiber = 2;
                printf("=== Fibra 2 selecionada.\n");
            }
            else if (selected_fiber == 2)
            {
                selected_fiber = 0;
                printf("=== Fibra 2 desselecionada.\n");
            }
        }
    }
    else if (gpio == BUTTON_J)
    {
        // Verifica debounce
        if ((current_time - last_time_irq_J) < debounce_delay)
            return;
        last_time_irq_J = current_time;

        // Ações quando as fibras estão alinhadas
        if (are_aligned())
        {
            alignment_locked = true; // Trava o alinhamento

            if (selected_fiber != 3 && !move_joined_fiber)
            {   
                printf("=== As fibras estão perfeitamente alinhadas...\n");
                // Inicia animação de fusão se ainda não foi feita
                should_animate_fusion = true;
                selected_fiber = 3; // Fibra combinada
            }
            else if (selected_fiber == 3 && !move_joined_fiber)
            {
                // Se a fibra combinada foi criada, pode ser movida
                move_joined_fiber = true;
                selected_fiber = -1; // Nenhuma selecionada
                printf("=== A fibra emendada pode ser movida.\n");
            }
            else if (move_joined_fiber)
            {
                // Após mover a fibra combinada, reinicia o processo
                choose_random_position();  // Escolhe nova posição aleatória
                loop_led_colors(scheme_1); // Mostra animação de cores
                move_joined_fiber = false; // Reseta o estado
                alignment_locked = false;
                selected_fiber = 0;
                printf("=== Esperando o alinhamento das fibras.\n");
            }
        }
    }
}

// Função para configurar os botões com interrupções
void configure_buttons()
{
    const uint buttons[] = {BUTTON_A, BUTTON_B, BUTTON_J}; // Lista dos botões utilizados

    for (int i = 0; i < 3; i++)
    {
        configure_gpio(buttons[i], true, true);                                                        // Configura cada botão com pull-up e direção de entrada
        gpio_set_irq_enabled_with_callback(buttons[i], GPIO_IRQ_EDGE_FALL, true, button_irq_callback); // Habilita interrupção por borda de descida
    }
}