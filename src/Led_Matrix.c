#include <Led_Matrix.h>

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

void loop_colors_one_by_one(refs pio, led_color color, uint16_t d_frame)
{
    int *d = drawing(d_frame);
    int d_snake[NUM_PIXELS];
    convert_to_snake_rows(d, d_snake);

    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        if (d_snake[i] == 3)
        {
            pio_sm_put_blocking(pio.ref, pio.state_machine, rgb_matrix(color));
        }
        else if (d_snake[i] == 1)
        {
            pio_sm_put_blocking(pio.ref, pio.state_machine, rgb_matrix(CYAN));
        }
        else if (d_snake[i] == 2)
        {
            pio_sm_put_blocking(pio.ref, pio.state_machine, rgb_matrix(BURGUNDY));
        }
        else
        {
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

int *drawing(uint16_t d)
{
    static int d0[NUM_PIXELS] = {
        0, 0, 0, 0, 0,
        0, 0, 3, 0, 0,
        0, 0, 3, 0, 0,
        0, 0, 3, 0, 0,
        0, 0, 0, 0, 0};

    static int d1[NUM_PIXELS] = {
        1, 0, 0, 0, 0,
        1, 0, 3, 0, 0,
        1, 0, 3, 0, 0,
        0, 0, 3, 0, 0,
        0, 0, 0, 0, 0};

    static int d2[NUM_PIXELS] = {
        0, 0, 0, 0, 0,
        1, 0, 3, 0, 0,
        1, 0, 3, 0, 0,
        1, 0, 3, 0, 0,
        0, 0, 0, 0, 0};

    static int d3[NUM_PIXELS] = {
        0, 0, 0, 0, 0,
        0, 0, 3, 0, 0,
        1, 0, 3, 0, 0,
        1, 0, 3, 0, 0,
        1, 0, 0, 0, 0};

    static int d4[NUM_PIXELS] = {
        1, 1, 0, 0, 0,
        1, 1, 3, 0, 0,
        1, 1, 3, 0, 0,
        0, 0, 3, 0, 0,
        0, 0, 0, 0, 0};

    static int d5[NUM_PIXELS] = {
        0, 0, 0, 0, 0,
        1, 1, 3, 0, 0,
        1, 1, 3, 0, 0,
        1, 1, 3, 0, 0,
        0, 0, 0, 0, 0};

    static int d6[NUM_PIXELS] = {
        0, 0, 0, 0, 0,
        0, 0, 3, 0, 0,
        1, 1, 3, 0, 0,
        1, 1, 3, 0, 0,
        1, 1, 0, 0, 0};

    static int d7[NUM_PIXELS] = {
        0, 0, 0, 0, 2,
        0, 0, 3, 0, 2,
        1, 1, 3, 0, 2,
        1, 1, 3, 0, 0,
        1, 1, 0, 0, 0};

    static int d8[NUM_PIXELS] = {
        0, 0, 0, 0, 0,
        0, 0, 3, 0, 2,
        1, 1, 3, 0, 2,
        1, 1, 3, 0, 2,
        1, 1, 0, 0, 0};

    switch (d)
    {
    case 1:
        return d1;
    case 2:
        return d2;
    case 3:
        return d3;
    case 4:
        return d4;
    case 5:
        return d5;
    case 6:
        return d6;
    case 7:
        return d7;
    case 8:
        return d8;
    default:
        return d0;
    }
}

// #define MAX_FRAMES 50
// #define NUM_PIXELS 25

// static int frame0[NUM_PIXELS] = { /* ... */ };
// static int frame1[NUM_PIXELS] = { /* ... */ };
// static int frame2[NUM_PIXELS] = { /* ... */ };
// // ...

// static int* frames[MAX_FRAMES] = {
//     frame0, frame1, frame2 /*, ... até frame49 */
// };

// int* drawing(int d)
// {
//     if (d >= 0 && d < MAX_FRAMES)
//         return frames[d];
//     else
//         return NULL; // ou um frame vazio
// }
