#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include "pico/stdlib.h"
#include <stdlib.h>
#include <math.h>
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "pio_matrix.pio.h"
#include "hardware/i2c.h"

#define BUTTON_A 5   // Pino do Botão A
#define BUTTON_B 6   // Pino do Botão B
#define GREEN_LED 11 // Pino do LED verde
#define BLUE_LED 12  // Pino do LED azul
#define RED_LED 13   // Pino do LED vermelho
#define LED_MATRIX 7 // Pino da matriz de LEDs WS2812
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define ADRESS 0x3C

// Struct para manipulação da PIO
typedef struct PIORefs
{
    PIO ref;
    uint offset;
    uint stateMachine;
} refs;

// Struct para manipulação das cores dos LEDs
typedef struct RGB
{
    int8_t red;
    int8_t green;
    int8_t blue;
} RGB;

// Funções de configuração
refs InitConf();
refs InitPIO();
void SetInput(int);
void SetOutput(int);

#endif