#include <Leds.h>

// Converte uma cor RGB para um formato de 32 bits para a matriz de LEDs
uint32_t RGBMatrix(RGB color)
{
    unsigned char R, G, B;
    R = color.red;
    G = color.green;
    B = color.blue;
    return (G << 24) | (R << 16) | (B << 8);
}

// Desenha um padrão na matriz de LEDs com a cor especificada
void Draw(double *drawing, uint32_t valorLed, refs pio, RGB color)
{
    // Estrutura de cor temporária para cada LED
    RGB finalColor;

    for (int16_t i = (NUM_PIXELS)-1; i >= 0; i--)
    {
        // Define a cor com base no desenho
        if (drawing[i])
        {
            finalColor = color; // Usa diretamente a cor fornecida
        }
        else
        {
            // Mantém o LED apagado
            finalColor.red = 0;
            finalColor.green = 0;
            finalColor.blue = 0;
        }

        // Converte a cor para formato 32 bits e envia ao PIO
        valorLed = RGBMatrix(finalColor);
        pio_sm_put_blocking(pio.ref, pio.stateMachine, valorLed);
    }
}

// Retorna um ponteiro para um array de pixels representando um número de 0 a 9
double *Drawing(int drawing)
{
    // Matrizes que representam os números de 0 a 9
    static double drawing0[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    static double drawing1[] = {
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0};

    static double drawing2[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    static double drawing3[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    static double drawing4[] = {
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0};

    static double drawing5[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    static double drawing6[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    static double drawing7[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0};

    static double drawing8[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    static double drawing9[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    // Retorna o desenho correspondente ao número solicitado
    switch (drawing)
    {
    case 1: return drawing1;
    case 2: return drawing2;
    case 3: return drawing3;
    case 4: return drawing4;
    case 5: return drawing5;
    case 6: return drawing6;
    case 7: return drawing7;
    case 8: return drawing8;
    case 9: return drawing9;
    default: return drawing0;
    }
}