#include "General.h"
#include "Leds.h"
#include "include/ssd1306.h"
#include "include/font.h"

// Variáveis globais

refs pio;                               // Referência do PIO
uint32_t valorLed;                      // Valor do LED a ser enviado
RGB color;                              // Cor do LED (RGB)
double *drawing;                        // Desenho (sequência de LEDs acesos)
volatile uint8_t count = 0;             // Contador do número mostrado
static volatile uint32_t lastTimeA = 0; // Tempo de última interrupção do botão A
static volatile uint32_t lastTimeB = 0; // Tempo de última interrupção do botão B

void SetInterruption(int pin);                          // Configura a interrupção para o botão
void HandleInterruption(uint gpio, uint32_t events);    // Função que lida com a interrupção dos botões
void UpdateLed(uint gpio, volatile uint32_t *lastTime); // Atualiza o LED com base no botão pressionado
bool BlinkLedCallback(struct repeating_timer *t);       // Função de callback para fazer o LED piscar
void LedInformationMessage(uint gpio, bool ledStatus);
void UpdateDrawing(uint gpio, volatile uint32_t *lastTime, int number);

int main()
{
    // Inicializa o PIO
    pio = InitPIO();

    // Configura botões A e B e atribui interrupções
    SetInput(BUTTON_A);
    SetInterruption(BUTTON_A);
    SetInput(BUTTON_B);
    SetInterruption(BUTTON_B);

    // Configura os LED verde e azul
    SetOutput(GREEN_LED);
    SetOutput(BLUE_LED);

    // Define a cor dos LEDs da matriz
    color.red = 2;
    color.green = 4;
    color.blue = 8;

    // Inicializa o desenho com o número 0 e exibe na matriz
    drawing = Drawing(0);
    Draw(drawing, valorLed, pio, color);

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);                  // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);                  // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA);                                      // Pull up the data line
    gpio_pull_up(I2C_SCL);                                      // Pull up the clock line
    ssd1306_t ssd;                                              // Inicializa a estrutura do display
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ADRESS, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd);                                       // Configura o display
    ssd1306_send_data(&ssd);                                    // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    bool cor = true;

    // Loop principal que mantém o sistema funcionando
    while (true)
    {
        cor = !cor;
        // Atualiza o conteúdo do display com animações
        ssd1306_fill(&ssd, !cor);                           // Limpa o display
        ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor);       // Desenha um retângulo
        ssd1306_draw_string(&ssd, "CEPEDI   TIC37", 8, 10); // Desenha uma string
        ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 30);   // Desenha uma string
        ssd1306_draw_string(&ssd, "PROF WILTON", 15, 48);   // Desenha uma string
        ssd1306_send_data(&ssd);                            // Atualiza o display

        sleep_ms(1000);
        // if (stdio_usb_connected())
        // { // Certifica-se de que o USB está conectado
        //     char c;
        //     scanf("%c", &c);

        //     sleep_ms(40);
        // }
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
        *lastTime = currentTime;
        gpio_put(gpio, !gpio_get(gpio));

        bool ledStatus = gpio_get(gpio);

        LedInformationMessage(gpio, ledStatus);
    }
}

void LedInformationMessage(uint gpio, bool ledStatus)
{
    if (gpio == GREEN_LED)
    {
        if (ledStatus)
        {
            printf("Led Verde ligado");
            // O led verde foi ligado
        }
        else
        {
            printf("Led Verde desligado");
            // O LED verde foi desligado
        }
    }
    else if (gpio == BLUE_LED)
    {
        if (ledStatus)
        {
            printf("Led Azul ligado");
            // O LED azul foi ligado
        }
        else
        {
            printf("Led Azul desligado");
            // O LED azul foi desligado
        }
    }
}

void UpdateDrawing(uint gpio, volatile uint32_t *lastTime, int number)
{
    // Atualiza o desenho de acordo com o valor
    drawing = Drawing(number);
    Draw(drawing, valorLed, pio, color);
}