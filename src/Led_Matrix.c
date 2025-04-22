#include "Led_Matrix.h" // Inclusão da biblioteca para controlar a matriz de LEDs

// Inicializa a matriz com todos os LEDs apagados
int matrix[NUM_PIXELS] = {0};

// Variáveis compartilhadas (podem ser acessadas por interrupções)
volatile led_positions pos_fiber_1;
volatile led_positions pos_fiber_2;
volatile led_positions pos_fiber;
volatile uint8_t chosen_pos; // Posição escolhida aleatoriamente para fusão

// Estrutura contendo referências do PIO (programável de I/O)
refs pio;

// Dois esquemas de cores: um padrão e um especial para animação
led_color_scheme scheme_1;
led_color_scheme scheme_2;

// Função para inicializar o PIO e configurar a máquina de estado com o programa da matriz de LEDs
refs init_pio()
{
    refs pio;
    pio.ref = pio0; // Usa o PIO 0

    pio.state_machine = pio_claim_unused_sm(pio.ref, true); // Obtém uma máquina de estado livre
    pio.offset = pio_add_program(pio.ref, &pio_matrix_program); // Adiciona o programa da matriz

    pio_matrix_program_init(pio.ref, pio.state_machine, pio.offset, LED_MATRIX); // Inicializa o programa
    return pio;
}

// Converte uma estrutura de cor RGB para um valor 32 bits conforme o protocolo da matriz
uint32_t rgb_matrix(led_color color)
{
    return (color.green << 24) | (color.red << 16) | (color.blue << 8);
}

// Envia os dados da matriz para a PIO de acordo com o esquema de cores e o conteúdo da matriz
void loop_led_colors(led_color_scheme colors)
{
    int d_snake[NUM_PIXELS];

    convert_to_snake_rows(matrix, d_snake); // Converte para o formato "snake" da matriz física

    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        // Envia a cor correspondente para cada valor da matriz
        switch (d_snake[i])
        {
        case 3:
            pio_sm_put_blocking(pio.ref, pio.state_machine, rgb_matrix(colors.alignment));
            break;
        case 1:
            pio_sm_put_blocking(pio.ref, pio.state_machine, rgb_matrix(colors.fiber_1));
            break;
        case 2:
            pio_sm_put_blocking(pio.ref, pio.state_machine, rgb_matrix(colors.fiber_2));
            break;
        default:
            pio_sm_put_blocking(pio.ref, pio.state_machine, rgb_matrix(colors.background));
        }
    }
}

// Converte a matriz de 5x5 para o padrão "snake" (ziguezague) usado pela matriz física
void convert_to_snake_rows(int *input, int *output)
{
    int index = 0;
    for (int row = 4; row >= 0; row--)
    {
        if ((4 - row) % 2 == 0)
        {
            // Linha invertida (da direita para a esquerda)
            for (int col = 4; col >= 0; col--)
            {
                output[index++] = input[row * 5 + col];
            }
        }
        else
        {
            // Linha normal (da esquerda para a direita)
            for (int col = 0; col < 5; col++)
            {
                output[index++] = input[row * 5 + col];
            }
        }
    }
}

// Escolhe aleatoriamente uma posição central para a fusão das fibras
void choose_random_position()
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        matrix[i] = 0; // Zera a matriz
    }

    // Posições centrais possíveis
    int positions[] = {2, 7, 12, 17, 22};

    // Sorteia uma posição
    int index = rand() % 5;
    chosen_pos = positions[index];

    // Marca a posição sorteada com o valor 3 (alinhamento)
    matrix[chosen_pos] = 3;
}

// Verifica se as fibras estão alinhadas com a posição central escolhida
bool are_aligned()
{
    return ((chosen_pos - 1 == pos_fiber_1.pos_2) && (chosen_pos - 2 == pos_fiber_1.pos_1)) &&
           ((chosen_pos + 1 == pos_fiber_2.pos_1) && (chosen_pos + 2 == pos_fiber_2.pos_2));
}

// Inicializa os esquemas de cores utilizados
void init_color_schemes()
{
    scheme_1.fiber_1 = CYAN;
    scheme_1.fiber_2 = BURGUNDY;
    scheme_1.alignment = CHARTREUSE;
    scheme_1.background = DARK;

    scheme_2.fiber_1 = PURPLE;
    scheme_2.fiber_2 = PURPLE;
    scheme_2.alignment = PURPLE;
    scheme_2.background = DARK;
}

// Função de animação de fusão das fibras ópticas
void animate_fiber_fusion()
{
    // Guarda o estado atual da matriz
    int original_matrix[NUM_PIXELS];
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        original_matrix[i] = matrix[i];
    }

    // Define as posições envolvidas na fusão
    int center_pos = chosen_pos;
    int left_pos_1 = center_pos - 1;
    int left_pos_2 = center_pos - 2;
    int right_pos_1 = center_pos + 1;
    int right_pos_2 = center_pos + 2;

    // Define uma paleta de cores variadas para a animação
    led_color available_colors[] = {
        CYAN, BURGUNDY, CHARTREUSE, GREEN, YELLOW,
        ORANGE, BLUE, PURPLE, RED, WHITE
    };

    // Cria esquemas de cores dinâmicos para a animação (efeito de arco-íris)
    led_color_scheme fusion_colors[10];
    for (int i = 0; i < 10; i++)
    {
        fusion_colors[i].alignment = available_colors[i % 10];
        fusion_colors[i].fiber_1 = available_colors[(i + 3) % 10];
        fusion_colors[i].fiber_2 = available_colors[(i + 6) % 10];
        fusion_colors[i].background = DARK;
    }

    // Loop de animação com 10 frames
    for (int i = 0; i < 10; i++)
    {
        // Limpa a matriz
        for (int j = 0; j < NUM_PIXELS; j++) matrix[j] = 0;

        // Redesenha as fibras com a posição central
        matrix[center_pos] = 3;
        if (left_pos_1 >= 0) matrix[left_pos_1] = 1;
        if (left_pos_2 >= 0) matrix[left_pos_2] = 1;
        if (right_pos_1 < NUM_PIXELS) matrix[right_pos_1] = 2;
        if (right_pos_2 < NUM_PIXELS) matrix[right_pos_2] = 2;

        // Aplica esquema de cor animado atual
        loop_led_colors(fusion_colors[i]);

        // Feedback: LED verde + buzzer (rápido)
        apply_led_and_buzzer_feedback(i, 1);
        sleep_ms(60);
        apply_led_and_buzzer_feedback(-1, -1);

        sleep_ms(140); // Totaliza 200ms por frame
    }

    // Restaura o estado anterior da matriz
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        matrix[i] = original_matrix[i];
    }

    // Mostra a fusão final com cor unificada (todos os LEDs envolvidos em "3")
    matrix[center_pos] = 3;
    if (left_pos_1 >= 0) matrix[left_pos_1] = 3;
    if (left_pos_2 >= 0) matrix[left_pos_2] = 3;
    if (right_pos_1 < NUM_PIXELS) matrix[right_pos_1] = 3;
    if (right_pos_2 < NUM_PIXELS) matrix[right_pos_2] = 3;

    loop_led_colors(scheme_2); // Aplica esquema final

    // Garante que o LED e o buzzer estejam desligados
    apply_led_and_buzzer_feedback(-1, -1);
}
