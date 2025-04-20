#include <Led_Matrix.h>

int matrix[NUM_PIXELS] = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 3, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

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

void loop_led_colors(refs pio, led_color_scheme colors)
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

uint8_t choose_random_position()
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {         
        matrix[i] = 0;
    }

    int positions[] = {2, 7, 12, 17, 22};
    
    int index = rand() % 5;
    int chosen_pos = positions[index];

    matrix[chosen_pos] = 3;

    return chosen_pos;
}
