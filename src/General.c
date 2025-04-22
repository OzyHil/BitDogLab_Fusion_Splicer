#include "General.h"
#include "Buttons.h"
#include "Leds.h"
#include "Joystick.h"
#include "Display.h"
#include "Buzzer.h"

// Função para inicializar a configuração do sistema
void init_system_config()
{
    // Inicializa a biblioteca de entrada/saída padrão (stdio), permitindo uso de printf/scanf
    stdio_init_all();

    // Inicializa o conversor analógico-digital (ADC), usado para ler valores analógicos
    adc_init();

    // Configura o relógio do sistema para 128 kHz (sistema de 32 bits com precisão de tempo)
    set_sys_clock_khz(128000, false);

    // Inicializa o gerador de números aleatórios com base no tempo atual em microssegundos
    srand(time_us_32());

    // Configura os botões, LEDs, joystick, display I2C e buzzer
    configure_buttons();
    configure_leds();
    configure_joystick();
    configure_i2c_display();
    configure_buzzer();
}

// Função para configurar o GPIO como entrada ou saída, com a opção de ativar o resistor de pull-up
void configure_gpio(uint gpio, bool is_input, bool use_pull_up)
{
    gpio_init(gpio); // Inicializa o GPIO especificado

    gpio_set_dir(gpio, is_input ? GPIO_IN : GPIO_OUT); // Define a direção do GPIO (entrada ou saída)

    // Se for uma entrada e o pull-up for necessário, ativa o pull-up no GPIO
    if (is_input && use_pull_up)
    {
        gpio_pull_up(gpio);
    }
}

// Função para inicializar a funcionalidade PWM em um pino GPIO
void init_pwm(uint gpio, uint wrap)
{
    gpio_set_function(gpio, GPIO_FUNC_PWM); // Define o pino GPIO para a função PWM

    uint slice = pwm_gpio_to_slice_num(gpio); // Obtém o número do slice PWM associado ao pino GPIO

    pwm_set_clkdiv(slice, 16.0); // Define o divisor de clock PWM (controla a velocidade do sinal PWM)

    pwm_set_wrap(slice, wrap); // Define o valor de "wrap", que determina o ciclo completo do PWM

    pwm_set_enabled(slice, true); // Habilita a geração do sinal PWM no slice
}

// Função para inicializar o ADC em um pino GPIO
void init_adc(uint gpio)
{
    // Inicializa o pino GPIO para ser usado com ADC (leitura analógica)
    adc_gpio_init(gpio);
}
