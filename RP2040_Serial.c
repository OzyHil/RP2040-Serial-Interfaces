#include "General.h"
#include "Leds.h"

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
void UpdateLed(uint gpio, volatile uint32_t *lastTime); // Atualiza o desenho com base no botão pressionado
bool BlinkLedCallback(struct repeating_timer *t);       // Função de callback para fazer o LED piscar
void LedInformationMessage(uint gpio, bool ledStatus);

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

    // Loop principal que mantém o sistema funcionando
    while (true)
    {
        sleep_ms(1); // Coloca o processador em modo de baixo consumo
    }
}

// Função para configurar a interrupção no pino do botão
void SetInterruption(int pin)
{
    gpio_set_irq_enabled_with_callback(pin, GPIO_IRQ_EDGE_FALL, 1, &HandleInterruption);
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