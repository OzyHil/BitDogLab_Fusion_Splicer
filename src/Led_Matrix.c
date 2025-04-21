#include <Led_Matrix.h>

int matrix[NUM_PIXELS] = {0};

volatile led_positions pos_fiber_1;
volatile led_positions pos_fiber_2;
volatile led_positions pos_fiber;
volatile uint8_t chosen_pos;
refs pio;
led_color_scheme scheme_1;
led_color_scheme scheme_2;

refs init_pio()
{
    refs pio;
    pio.ref = pio0;

    pio.state_machine = pio_claim_unused_sm(pio.ref, true);
    pio.offset = pio_add_program(pio.ref, &pio_matrix_program);

    pio_matrix_program_init(pio.ref, pio.state_machine, pio.offset, LED_MATRIX);
    return pio;
}

uint32_t rgb_matrix(led_color color)
{
    return (color.green << 24) | (color.red << 16) | (color.blue << 8);
}

void loop_led_colors(led_color_scheme colors)
{
    int d_snake[NUM_PIXELS];

    convert_to_snake_rows(matrix, d_snake);

    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
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

void convert_to_snake_rows(int *input, int *output)
{
    int index = 0;
    for (int row = 4; row >= 0; row--)
    {
        if ((4 - row) % 2 == 0)
        {
            for (int col = 4; col >= 0; col--)
            {
                output[index++] = input[row * 5 + col];
            }
        }
        else
        {
            for (int col = 0; col < 5; col++)
            {
                output[index++] = input[row * 5 + col];
            }
        }
    }
}

void choose_random_position()
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        matrix[i] = 0;
    }

    int positions[] = {2, 7, 12, 17, 22};

    int index = rand() % 5;
    chosen_pos = positions[index];

    matrix[chosen_pos] = 3;
}

bool are_aligned()
{
    return ((chosen_pos - 1 == pos_fiber_1.pos_2) && (chosen_pos - 2 == pos_fiber_1.pos_1)) &&
           ((chosen_pos + 1 == pos_fiber_2.pos_1) && (chosen_pos + 2 == pos_fiber_2.pos_2));
}

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

// void animate_fiber_fusion()
// {
//     int original_matrix[NUM_PIXELS];
//     for (int i = 0; i < NUM_PIXELS; i++)
//     {
//         original_matrix[i] = matrix[i];
//     }

//     int center_pos = chosen_pos;
//     int left_pos_1 = center_pos - 1;
//     int left_pos_2 = center_pos - 2;
//     int right_pos_1 = center_pos + 1;
//     int right_pos_2 = center_pos + 2;

//     led_color available_colors[] = {
//         CYAN, BURGUNDY, CHARTREUSE, GREEN, YELLOW,
//         ORANGE, BLUE, PURPLE, RED, WHITE};

//     led_color_scheme fusion_colors[10];
//     for (int i = 0; i < 10; i++)
//     {
//         fusion_colors[i].alignment = available_colors[i % 10];
//         fusion_colors[i].fiber_1 = available_colors[(i + 3) % 10];
//         fusion_colors[i].fiber_2 = available_colors[(i + 6) % 10];
//         fusion_colors[i].background = DARK;
//     }

//     for (int frame = 0; frame < 20; frame++)
//     {
//         if (frame < 10)
//         {
//             for (int i = 0; i < NUM_PIXELS; i++)
//             {
//                 matrix[i] = 0;
//             }

//             matrix[center_pos] = 3;

//             if (frame < 8 && left_pos_1 >= 0)
//                 matrix[left_pos_1] = 1;
//             if (frame < 5 && left_pos_2 >= 0)
//                 matrix[left_pos_2] = 1;
//             if (frame < 8 && right_pos_1 < NUM_PIXELS)
//                 matrix[right_pos_1] = 2;
//             if (frame < 5 && right_pos_2 < NUM_PIXELS)
//                 matrix[right_pos_2] = 2;

//             loop_led_colors(fusion_colors[frame % 10]);

//             // Aplicando feedback do LED e buzzer
//             if (frame < 8)
//                 apply_led_and_buzzer_feedback(frame, 1); // Para frames iniciais, luz verde e som baixo
//             else
//                 apply_led_and_buzzer_feedback(frame, 2); // Para frames mais avançados, luz amarela e som médio
//         }
//         else
//         {
//             int explosion_frame = frame - 10;

//             for (int i = 0; i < NUM_PIXELS; i++)
//             {
//                 matrix[i] = 0;
//             }

//             matrix[center_pos] = 3;

//             if (explosion_frame >= 1 && left_pos_1 >= 0)
//                 matrix[left_pos_1] = 3;
//             if (explosion_frame >= 1 && right_pos_1 < NUM_PIXELS)
//                 matrix[right_pos_1] = 3;

//             if (explosion_frame >= 2 && left_pos_2 >= 0)
//                 matrix[left_pos_2] = 3;
//             if (explosion_frame >= 2 && right_pos_2 < NUM_PIXELS)
//                 matrix[right_pos_2] = 3;

//             if (explosion_frame >= 7 && left_pos_2 >= 0)
//                 matrix[left_pos_2] = 0;
//             if (explosion_frame >= 7 && right_pos_2 < NUM_PIXELS)
//                 matrix[right_pos_2] = 0;

//             if (explosion_frame >= 8 && left_pos_1 >= 0)
//                 matrix[left_pos_1] = 0;
//             if (explosion_frame >= 8 && right_pos_1 < NUM_PIXELS)
//                 matrix[right_pos_1] = 0;

//             if (explosion_frame >= 9)
//                 matrix[center_pos] = 3;

//             loop_led_colors(fusion_colors[explosion_frame % 10]);

//             // Aplicando feedback do LED e buzzer durante a explosão
//             if (explosion_frame < 5)
//                 apply_led_and_buzzer_feedback(frame, 1); // Som leve e luz verde
//             else if (explosion_frame < 8)
//                 apply_led_and_buzzer_feedback(frame, 2); // Som médio e luz amarela
//             else
//                 apply_led_and_buzzer_feedback(frame, 3); // Som mais forte e luz laranja
//         }

//         sleep_ms(120);
//     }

//     for (int i = 0; i < NUM_PIXELS; i++)
//     {
//         matrix[i] = original_matrix[i];
//     }

//     matrix[center_pos] = 3;
//     if (left_pos_1 >= 0)
//         matrix[left_pos_1] = 3;
//     if (left_pos_2 >= 0)
//         matrix[left_pos_2] = 3;
//     if (right_pos_1 < NUM_PIXELS)
//         matrix[right_pos_1] = 3;
//     if (right_pos_2 < NUM_PIXELS)
//         matrix[right_pos_2] = 3;

//     loop_led_colors(scheme_2);

//     // Após a animação, desliga o buzzer e o LED
//     apply_led_and_buzzer_feedback(-1, -1); 
// }

void animate_fiber_fusion()
{
    int original_matrix[NUM_PIXELS];
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        original_matrix[i] = matrix[i];
    }

    int center_pos = chosen_pos;
    int left_pos_1 = center_pos - 1;
    int left_pos_2 = center_pos - 2;
    int right_pos_1 = center_pos + 1;
    int right_pos_2 = center_pos + 2;

    led_color available_colors[] = {
        CYAN, BURGUNDY, CHARTREUSE, GREEN, YELLOW,
        ORANGE, BLUE, PURPLE, RED, WHITE
    };

    led_color_scheme fusion_colors[10];
    for (int i = 0; i < 10; i++)
    {
        fusion_colors[i].alignment = available_colors[i % 10];
        fusion_colors[i].fiber_1 = available_colors[(i + 3) % 10];
        fusion_colors[i].fiber_2 = available_colors[(i + 6) % 10];
        fusion_colors[i].background = DARK;
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < NUM_PIXELS; j++) matrix[j] = 0;

        matrix[center_pos] = 3;
        if (left_pos_1 >= 0) matrix[left_pos_1] = 1;
        if (left_pos_2 >= 0) matrix[left_pos_2] = 1;
        if (right_pos_1 < NUM_PIXELS) matrix[right_pos_1] = 2;
        if (right_pos_2 < NUM_PIXELS) matrix[right_pos_2] = 2;

        loop_led_colors(fusion_colors[i]);

        // Piscar LED verde e apitar o buzzer rapidamente
        apply_led_and_buzzer_feedback(i, 1); // liga LED verde + som leve
        sleep_ms(60);                         // tempo de pulso
        apply_led_and_buzzer_feedback(-1, -1); // desliga ambos

        sleep_ms(140); // tempo restante do frame (total: 200ms)
    }

    for (int i = 0; i < NUM_PIXELS; i++)
    {
        matrix[i] = original_matrix[i];
    }

    matrix[center_pos] = 3;
    if (left_pos_1 >= 0) matrix[left_pos_1] = 3;
    if (left_pos_2 >= 0) matrix[left_pos_2] = 3;
    if (right_pos_1 < NUM_PIXELS) matrix[right_pos_1] = 3;
    if (right_pos_2 < NUM_PIXELS) matrix[right_pos_2] = 3;

    loop_led_colors(scheme_2);

    // Garante que tudo está desligado no fim
    apply_led_and_buzzer_feedback(-1, -1);
}
