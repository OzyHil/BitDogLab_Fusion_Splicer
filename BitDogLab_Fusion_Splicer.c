#include "General.h"       // Inclusão do cabeçalho para funções gerais
#include "Buttons.h"       // Inclusão do cabeçalho para controle dos botões
#include "Leds.h"          // Inclusão do cabeçalho para controle dos LEDs
#include "Led_Matrix.h"    // Inclusão do cabeçalho para controle da matriz de LEDs
#include "Joystick.h"      // Inclusão do cabeçalho para contorle do joystick
#include "Display.h"       // Inclusão do cabeçalho para controle do display

// Função principal do programa
int main()
{
    // Inicializa as configurações do sistema
    init_system_config();

    // Inicializa o PIO (Programmable Input/Output), necessário para o controle da matriz de LEDs
    pio = init_pio();

    // Declara variáveis auxiliares para referência e diferença
    int ref;
    uint8_t diff;

    // Definindo o intervalo de leitura do joystick, a diferença entre o valor máximo e mínimo dos eixos
    uint16_t range = HIGHEST_AXIS_VALUE - LOWEST_AXIS_VALUE;

    // Inicializa os esquemas de cores dos LEDs
    init_color_schemes();

    // Escolhe uma posição aleatória inicial para o ponto de alinhamento da fibra
    choose_random_position();

    // Inicia a animação dos LEDs com o esquema de cores 1
    loop_led_colors(scheme_1);

    // Loop principal que irá executar continuamente
    while (true)
    {
        // Lê a posição do joystick (eixos x e y)
        joystick_position pos = read_joystick();

        // Verifica se a fibra 1 está selecionada
        if (selected_fiber == 1)
        {
            pos_fiber_1 = update_fiber_1(matrix, pos.x, pos.y); // Atualiza a posição da fibra 1 na matriz e calcula a referência
            ref = get_reference_position(pos_fiber_1, 1); // Obtém a posição de referência para a fibra 1
            diff = get_diff_from_reference(ref, chosen_pos, 1); // Calcula a diferença entre a posição de alinhamento e a referência
            apply_led_and_buzzer_feedback(ref, diff); // Aplica feedback visual e sonoro
            loop_led_colors(scheme_1); // Executa a animação dos LEDs com o esquema de cores 1
        }

        // Verifica se a fibra 2 está selecionada
        else if (selected_fiber == 2)
        {
            // Similar ao caso da fibra 1, mas para a fibra 2
            pos_fiber_2 = update_fiber_2(matrix, pos.x, pos.y);
            ref = get_reference_position(pos_fiber_2, 2);
            diff = get_diff_from_reference(ref, chosen_pos, 2);
            apply_led_and_buzzer_feedback(ref, diff);
            loop_led_colors(scheme_1);
        }

        // Caso nenhuma fibra esteja selecionada, o feedback visual e sonoro é desativado
        else if (selected_fiber == 0)
        {
            apply_led_and_buzzer_feedback(-1, -1);
        }

        // Caso a fusão de fibras deva ser animada, ela é realizada
        else if (should_animate_fusion)
        {
            should_animate_fusion = false; // Desativa a animação de fusão após ser executada
            apply_led_and_buzzer_feedback(-1, -1);
            animate_fiber_fusion(); // Função que realiza a animação da fusão das fibras
        }

        // Caso as fibras unidas estejam se movendo, o movimento é atualizado
        else if (move_joined_fiber)
        {
            update_fibers_and_center_led(matrix, pos.x, pos.y); // Atualiza as fibras unidas e o LED central
            apply_led_and_buzzer_feedback(-1, -1);
            loop_led_colors(scheme_2); // Executa a animação dos LEDs com o esquema de cores 2
        }

        // Normaliza a posição do joystick para a dimensão da matriz de LEDs
        uint16_t x_position = (NUM_LEDS_X * (int)(pos.x - LOWEST_AXIS_VALUE) / range);
        uint16_t y_position = (NUM_LEDS_Y * (int)(pos.y - LOWEST_AXIS_VALUE) / range);

        // Atualiza o display com uma quadrado 8x8 com base na nova posição calculada
        update_display(x_position, y_position);
    }
}