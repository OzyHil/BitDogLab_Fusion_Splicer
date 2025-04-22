#include "Joystick.h" // Inclusão da biblioteca para controlar o joystick

// Função para configurar o joystick, inicializando os pinos de entrada analógica
void configure_joystick()
{
    // Inicializa o pino analógico para o eixo X do joystick (VRX_PIN)
    adc_gpio_init(VRX_PIN);
    
    // Inicializa o pino analógico para o eixo Y do joystick (VRY_PIN)
    adc_gpio_init(VRY_PIN);
}

// Função para ler a posição do joystick e retornar os valores dos eixos X e Y
joystick_position read_joystick() {
    joystick_position pos;

    adc_select_input(1); // Seleciona o canal 1 do ADC para ler o valor do eixo X
    pos.x = adc_read(); // Lê o valor do eixo X e armazena

    adc_select_input(0); // Seleciona o canal 0 do ADC para ler o valor do eixo Y
    pos.y = adc_read(); // Lê o valor do eixo Y e armazena

    // Retorna a posição do joystick com os valores lidos para X e Y
    return pos;
}
