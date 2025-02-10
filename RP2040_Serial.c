#include "General.h"
#include "Leds.h"
#include "ssd1306.h"
#include "Font.h"

// Variáveis globais
refs pio;                               // Referência do PIO
uint32_t valorLed;                      // Valor do LED a ser enviado
RGB color;                              // Cor do LED (RGB)
double *drawing;                        // Desenho (sequência de LEDs acesos)
static volatile uint32_t lastTimeA = 0; // Tempo de última interrupção do botão A
static volatile uint32_t lastTimeB = 0; // Tempo de última interrupção do botão B
ssd1306_t ssd;

// Declaração das funções
void SetInterruption(int pin);                          // Configura a interrupção para o botão
void HandleInterruption(uint gpio, uint32_t events);    // Função que lida com a interrupção dos botões
void UpdateLed(uint gpio, volatile uint32_t *lastTime); // Atualiza o LED com base no botão pressionado
void LedInformationMessage(uint gpio, bool ledStatus);
void UpdateDrawing(int number);
void HandleInput(char c);
void UpdateDisplay(char c, uint8_t x, uint8_t y);

int main()
{
    // Inicializa o PIO (Peripheral Input/Output) para controlar a matriz de LEDs
    pio = InitPIO();

    // Configura botões A e B e atribui interrupções
    SetInput(BUTTON_A);
    SetInterruption(BUTTON_A);
    SetInput(BUTTON_B);
    SetInterruption(BUTTON_B);

    // Configura os LED verde e azul como saída
    SetOutput(GREEN_LED);
    SetOutput(BLUE_LED);

    // Define a cor inicial dos LEDs da matriz RGB
    color.red = 2;
    color.green = 4;
    color.blue = 8;

    // Inicializa o desenho com o número 0 e exibe na matriz
    drawing = Drawing(0);
    Draw(drawing, valorLed, pio, color);

    // Inicializa comunicação I2C com o display OLED a 400kHz
    i2c_init(I2C_PORT, 400 * 1000);

    // Configuração dos pinos de SDA e SCL para comunicação I2C
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);                  // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);                  // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA);                                      // Pull up the data line
    gpio_pull_up(I2C_SCL);                                      // Pull up the clock line

    // Inicializa o display OLED
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ADRESS, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd);                                       // Configura o display
    ssd1306_send_data(&ssd);                                    // Envia os dados para o display

    // Atualiza o display para inciar com o desenho padrão
    UpdateDisplay(' ', 0, 0);

    // Loop principal que mantém o sistema funcionando
    while (true)
    {

        if (stdio_usb_connected())
        { // Certifica-se de que o USB está conectado

            char c;
            scanf("%c", &c);// Lê um caractere da entrada

            HandleInput(c);// Processa a entrada do usuário

            sleep_ms(500);// Aguarda 500ms para evitar leituras consecutivas rápidas
        }
    }
}

// Função para configurar a interrupção no pino do botão
void SetInterruption(int pin)
{
    gpio_set_irq_enabled(pin, GPIO_IRQ_EDGE_FALL, true); // Ativa interrupção para o pino
    gpio_set_irq_callback(&HandleInterruption);          // Registra a função de callback uma vez
    irq_set_enabled(IO_IRQ_BANK0, true);                 // Ativa interrupções no banco de GPIOs
}

// Função que é chamada quando ocorre uma interrupção de botão
void HandleInterruption(uint gpio, uint32_t events)
{
    // Verifica se o botão A foi pressionado
    if (gpio == 5)
    {
        UpdateLed(GREEN_LED, &lastTimeA); // Alterar o estado do LED verde
    }
    // Verifica se o botão B foi pressionado
    else if (gpio == 6)
    {
        UpdateLed(BLUE_LED, &lastTimeB); // Alterar o estado do LED azul
    }
}

// Função que atualiza o desenho com base no botão pressionado
void UpdateLed(uint gpio, volatile uint32_t *lastTime)
{
    uint32_t currentTime = to_us_since_boot(get_absolute_time());

    // Verifica se o tempo de debouncing passou (250ms)
    if (currentTime - *lastTime > 250000)
    {
        *lastTime = currentTime; // Atualiza o tempo da última interrupção
        gpio_put(gpio, !gpio_get(gpio)); // Obtém estado atual do LED

        bool ledStatus = gpio_get(gpio); // Obtém estado atual do LED

        LedInformationMessage(gpio, ledStatus); // Exibe mensagem no display
    }
}

void LedInformationMessage(uint gpio, bool ledStatus)
{

    if (gpio == GREEN_LED)
    {
        if (ledStatus)
        {
            printf("Led Verde ligado\n");
            UpdateDisplay(' ', 0, 0);

            ssd1306_draw_string(&ssd, "LED VERDE ON", 8, 46); // Desenha uma string
            ssd1306_send_data(&ssd);                          // Atualiza o display
        }
        else
        {
            printf("Led Verde desligado\n");
            UpdateDisplay(' ', 0, 0);

            ssd1306_draw_string(&ssd, "LED VERDE OFF", 8, 46); // Desenha uma string
            ssd1306_send_data(&ssd);                           // Atualiza o display
        }
    }
    else if (gpio == BLUE_LED)
    {
        if (ledStatus)
        {
            printf("Led Azul ligado\n");
            UpdateDisplay(' ', 0, 0);

            ssd1306_draw_string(&ssd, "LED AZUL ON", 8, 46); // Desenha uma string
            ssd1306_send_data(&ssd);                         // Atualiza o display
        }
        else
        {
            printf("Led Azul desligado\n");
            UpdateDisplay(' ', 0, 0);

            ssd1306_draw_string(&ssd, "LED AZUL OFF", 8, 46); // Desenha uma string
            ssd1306_send_data(&ssd);                         // Atualiza o display
        }
    }
}

void UpdateDrawing(int number)
{
    // Atualiza o desenho de acordo com o valor
    drawing = Drawing(number);
    Draw(drawing, valorLed, pio, color);
}

void UpdateDisplay(char c, uint8_t x, uint8_t y)
{
    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    ssd1306_rect(&ssd, 3, 3, 122, 58, true, false);     // Desenha um retângulo
    ssd1306_draw_string(&ssd, "CEPEDI   TIC37", 8, 10); // Desenha uma string
    ssd1306_draw_char(&ssd, c, x, y); // Exibe caractere recebido
    ssd1306_send_data(&ssd); // Atualiza o display
}

void HandleInput(char c)
{
    if (c >= '0' && c <= '9') // Verifica se é um número de 0 a 9
    {
        UpdateDisplay(c, 8, 28);
        UpdateDrawing(c - '0'); // Converte caractere para número e atualiza a matriz
    }else
    {
        UpdateDisplay(c, 8, 28); // Apenas exibe no display OLED
    }
    
}
