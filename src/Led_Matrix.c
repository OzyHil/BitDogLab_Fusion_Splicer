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

void loop_colors_one_by_one(refs pio, led_color color)
{
    int d_snake[NUM_PIXELS];

    convert_to_snake_rows(matrix, d_snake);

    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        switch (d_snake[i])
        {
        case 3:
            pio_sm_put_blocking(pio.ref, pio.state_machine, rgb_matrix(color));
            break;
        case 1:
            pio_sm_put_blocking(pio.ref, pio.state_machine, rgb_matrix(CYAN));
            break;
        case 2:
            pio_sm_put_blocking(pio.ref, pio.state_machine, rgb_matrix(BURGUNDY));
            break;
        default:
            pio_sm_put_blocking(pio.ref, pio.state_machine, rgb_matrix(DARK));
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