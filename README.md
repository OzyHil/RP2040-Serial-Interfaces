# Projeto: Interfaces de Comunicação Serial com RP2040 - BitDogLab

## Vídeo de Demonstração
O vídeo de demonstração: https://youtu.be/kJ67gHHnHos.

## Descrição
Este projeto foi desenvolvido por mim, Hilquias Rodrigues de Oliveira, com o objetivo de consolidar os conceitos sobre interfaces de comunicação serial no RP2040 utilizando a placa de desenvolvimento BitDogLab. A implementação inclui comunicação UART e I2C, controle de LEDs WS2812 e RGB, e interação por meio de botões com tratamento de debounce e interrupção.

## Funcionalidades Implementadas
1. **Modificação da Biblioteca `font.h`**
   - Adição de caracteres minúsculos personalizados.
   
2. **Entrada de Caracteres via UART**
   - Digitação de caracteres pelo Serial Monitor do VS Code.
   - Exibição do caractere no display SSD1306 (I2C).
   - Exibição de números (0-9) na matriz de LEDs WS2812.

3. **Interação com os Botões**
   - **Botão A (GPIO 5):** Alterna o estado do LED RGB Verde.
     - Exibe uma mensagem no display SSD1306.
     - Envia informação ao Serial Monitor.
   - **Botão B (GPIO 6):** Alterna o estado do LED RGB Azul.
     - Exibe uma mensagem no display SSD1306.
     - Envia informação ao Serial Monitor.

## Componentes Utilizados
- **Matriz 5x5 de LEDs WS2812 (GPIO 7)**
- **LED RGB (GPIOs 11, 12, 13)**
- **Botão A (GPIO 5)**
- **Botão B (GPIO 6)**
- **Display OLED SSD1306 (I2C - GPIOs 14, 15)**

## Aspectos do Projeto
- Implementação de interrupções para os botões.
- Debouncing via software.
- Controle de LEDs comuns e LEDs endereçáveis WS2812.
- Código bem estruturado e comentado.

## Como Executar
### Pré-requisitos
Certifique-se de que você tem o ambiente configurado:
- **Pico SDK instalado**
- **Extensões Raspberry Pi Pico, CMake e C/C++**

### Passos
1. Clone este repositório:
   ```bash
   git clone https://github.com/seu-usuario/nome-do-repositorio.git
   ```
2. Abra a pasta do projeto no VS Code.
3. A extensão Pi Pico criará automaticamente a pasta `build`.
4. Clique em **Compile** na barra inferior do VS Code (ao lado esquerdo de "RUN | PICO SDK").
5. Verifique se o arquivo `.uf2` foi gerado corretamente na pasta `build`.
6. Conecte a placa BitDogLab via USB e coloque-a em modo BOOTSEL.
7. Arraste o arquivo `.uf2` gerado para dentro da unidade de armazenamento da placa.
8. O código será carregado e executado automaticamente.
9. O LED RGB piscará continuamente a cada 0.2 segundos (5Hz) e será mostrado o número `0` na matriz.
10. Interaja com o sistema pressionando os botões A e B para alterar o número exibido na matriz de LEDs.
