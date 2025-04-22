#include "Leds.h"      // Header para controle de LEDs via PWM
#include "Buzzer.h"    // Header para controle do buzzer via PWM

// Definições de cores utilizando níveis PWM para cada canal RGB
const led_color GREEN      = {.red = 0, .green = 3, .blue = 0};
const led_color YELLOW     = {.red = 3, .green = 3, .blue = 0};
const led_color ORANGE     = {.red = 3, .green = 1, .blue = 0};
const led_color CHARTREUSE = {.red = 3, .green = 15, .blue = 0};
const led_color CYAN       = {.red = 0, .green = 3, .blue = 3};
const led_color BURGUNDY   = {.red = 3, .green = 0, .blue = 1};
const led_color DARK       = {.red = 0, .green = 0, .blue = 0};  // Cor "apagado"
const led_color BLUE       = {.red = 0, .green = 0, .blue = 3};    
const led_color PURPLE     = {.red = 2, .green = 0, .blue = 3};  
const led_color RED        = {.red = 3, .green = 0, .blue = 0};     
const led_color WHITE      = {.red = 2, .green = 2, .blue = 2}; 
const led_color GRAY       = {.red = 1, .green = 1, .blue = 1};   

// Inicializa os pinos dos LEDs RGB como PWM
void configure_leds()
{
    const uint leds[] = {GREEN_LED, BLUE_LED, RED_LED};

    for (int i = 0; i < 3; i++)
    {
        init_pwm(leds[i], WRAP_PWM_LED); // Configura PWM com o "wrap" definido para LEDs
    }
}

// Define o brilho de um LED individual baseado em PWM
void set_led_brightness(uint gpio, uint8_t level)
{
    uint slice_num = pwm_gpio_to_slice_num(gpio);                       // Obtém slice PWM
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), level);   // Define nível do canal
}

// Define uma cor no LED RGB usando struct `led_color`
void set_led_color(led_color color)
{
    set_led_brightness(RED_LED, color.red);
    set_led_brightness(GREEN_LED, color.green);
    set_led_brightness(BLUE_LED, color.blue);
}

// Calcula posição de referência com base em duas posições da fibra
int get_reference_position(led_positions fiber_pos, uint8_t fiber)
{
    if (fiber == 1)
    {
        // Referência é o maior valor entre pos_1 e pos_2
        if (fiber_pos.pos_1 >= 0 && fiber_pos.pos_2 >= 0)
            return (fiber_pos.pos_1 > fiber_pos.pos_2) ? fiber_pos.pos_1 : fiber_pos.pos_2;
        else if (fiber_pos.pos_1 >= 0)
            return fiber_pos.pos_1;
        else if (fiber_pos.pos_2 >= 0)
            return fiber_pos.pos_2;
    }
    else if (fiber == 2)
    {
        // Referência é o menor valor entre pos_1 e pos_2
        if (fiber_pos.pos_1 >= 0 && fiber_pos.pos_2 >= 0)
            return (fiber_pos.pos_1 < fiber_pos.pos_2) ? fiber_pos.pos_1 : fiber_pos.pos_2;
        else if (fiber_pos.pos_1 >= 0)
            return fiber_pos.pos_1;
        else if (fiber_pos.pos_2 >= 0)
            return fiber_pos.pos_2;
    }

    return -1; // Valor inválido se nenhuma posição for válida
}

// Calcula diferença entre a posição escolhida e a posição de referência
uint8_t get_diff_from_reference(int ref, uint8_t chosen_pos, uint8_t fiber)
{
    if (ref < 0) return 0xFF; // Erro se referência for inválida
    return (fiber == 1) ? (chosen_pos - ref) : (ref - chosen_pos);
}

// Define feedback visual (LEDs) e sonoro (buzzer) com base na diferença da posição
void apply_led_and_buzzer_feedback(int ref, uint8_t diff)
{
    if (ref < 0 || diff == 0xFF) // Erro: desliga tudo
    {
        set_led_color(DARK);
        set_buzzer_level(BUZZER_A, 0);
        return;
    }

    if (diff == 1)
    {
        set_led_color(GREEN);                            // Alinhamento quase perfeito
        set_buzzer_level(BUZZER_A, WRAP_PWM_BUZZER / 5); // Tom mais alto
    }
    else if (diff == 2)
    {
        set_led_color(YELLOW);                           // Aproximado
        set_buzzer_level(BUZZER_A, WRAP_PWM_BUZZER / 50);
    }
    else
    {
        set_led_color(ORANGE);                           // Desalinhado
        set_buzzer_level(BUZZER_A, WRAP_PWM_BUZZER / 100);
    }
}
