#include "drawings.h"
// X = (16; 4082)
// Y = (16; 4082)

// X0 < 2300 < X1 | X2 > 3600
// Y0 < 2300 < Y1 | Y2 > 3600
/*

int matrix[NUM_PIXELS] = {
    0,  1,  2,  3,  4,
    5,  6,  7,  8,  9,
    10, 11, 12, 13, 14,
    15, 16, 17, 18, 19,
    20, 21, 22, 23, 24
    }
*/

/* fiber_1 =
    (x > 3600; y > 3300) => 0,1;
    (x > 3600; y > 2500) => 5,6;
    (x > 3600; y > 1700) => 10,11;
    (x > 3600; y > 900) => 15,16;
    (x > 3600; y > 0) => 20,21;

    (x > 2700; y > 3300) => 0;
    (x > 2700; y > 2500) => 5;
    (x > 2700; y > 1700) => 10;
    (x > 2700; y > 900) => 15;
    (x > 2700; y > 0) => 20;

   fiber_2 =
    (x < 900; y > 3300) => 3,4;
    (x < 900; y > 2500) => 8,9;
    (x < 900; y > 1700) => 14,15;
    (x < 900; y > 900) => 18,19;
    (x < 900; y > 0) => 23,24;

    (x < 1700; y > 3300) => 4;
    (x < 1700; y > 2500) => 9;
    (x < 1700; y > 1700) => 15;
    (x < 1700; y > 900) => 19;
    (x < 1700; y > 0) => 24;
*/

// x = (0,1; 5,6; 10,11, 15,16; 20,21)
// c = (2; 7; 12; 17; 22)
// y = (3,4; 8,9; 14,15, 18,19; 23,24)

led_positions update_fiber_1(int *matrix, int vrx, int vry)
{
    led_positions positions;

    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (matrix[i] == 1)
            matrix[i] = 0;
    }

    int linha = -1;

    if (vry > 3300)
        linha = 0;
    else if (vry > 2500)
        linha = 1;
    else if (vry > 1700)
        linha = 2;
    else if (vry > 900)
        linha = 3;
    else if (vry >= 0)
        linha = 4;

    if (linha >= 0)
    {
        int base = linha * 5;

        if (vrx > 3600)
        {
            matrix[base] = 1;
            matrix[base + 1] = 1;

            positions.pos_1 = base;
            positions.pos_2 = base + 1;
        }

        else if (vrx > 2700)
        {
            matrix[base] = 1;
            positions.pos_1 = base;
            positions.pos_2 = -1;
        }
        else
        {
            positions.pos_1 = -1;
            positions.pos_2 = -1;
        }
    }
    return positions;
}

led_positions update_fiber_2(int *matrix, int vrx, int vry)
{
    led_positions positions;

    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (matrix[i] == 2)
            matrix[i] = 0;
    }

    int linha = -1;

    if (vry > 3300)
        linha = 0;
    else if (vry > 2500)
        linha = 1;
    else if (vry > 1700)
        linha = 2;
    else if (vry > 900)
        linha = 3;
    else if (vry >= 0)
        linha = 4;

    if (linha >= 0)
    {
        int base = linha * 5;

        if (vrx < 900)
        {
            matrix[base + 3] = 2;
            matrix[base + 4] = 2;

            positions.pos_1 = base + 3;
            positions.pos_2 = base + 4;
        }

        else if (vrx < 1700)
        {
            matrix[base + 4] = 2;
            positions.pos_1 = base + 4;
            positions.pos_2 = -1;
        }
        else
        {
            positions.pos_1 = -1;
            positions.pos_2 = -1;
        }
    }
    return positions;
}

void update_fibers_and_center_led(int *matrix, int vrx, int vry)
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (matrix[i] == 1 || matrix[i] == 2 || matrix[i] == 3)
            matrix[i] = 0;
    }

    int linha = -1;
    if (vry > 3300)
        linha = 0;
    else if (vry > 2500)
        linha = 1;
    else if (vry > 1700)
        linha = 2;
    else if (vry > 900)
        linha = 3;
    else if (vry >= 0)
        linha = 4;

    if (linha >= 0 && linha < 5)
    {
        int base = linha * 5;

        matrix[base + 0] = 1;
        matrix[base + 1] = 1;

        matrix[base + 2] = 3;

        matrix[base + 3] = 2;
        matrix[base + 4] = 2;
    }
}
