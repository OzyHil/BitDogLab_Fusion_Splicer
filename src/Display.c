#include "Display.h"

ssd1306_t ssd;

void configure_i2c_display()
{
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_init(&ssd, 128, 64, false, DISPLAY_ADDRESS, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);
}

void update_display(uint16_t x_position, uint16_t y_position)
{
    ssd1306_fill(&ssd, false);
    ssd1306_rect(&ssd, abs(NUM_LEDS_Y - y_position), x_position, 8, 8, true, true);
    // ssd1306_rect(&ssd, y_position, x_position, 8, 8, true, true);
    ssd1306_send_data(&ssd);
}