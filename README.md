# Projeto: Interfaces de Comunicação Serial com RP2040 - BitDogLab

## Vídeo de Demonstração
Link do vídeo de demonstração: https://youtu.be/RPA3JRfhyio

## Descrição
Este projeto foi desenvolvido por **Hilquias Rodrigues de Oliveira** com o objetivo de consolidar os conceitos sobre interfaces de comunicação serial no RP2040 utilizando a placa de desenvolvimento **BitDogLab**. A implementação inclui comunicação **UART e I2C**, controle de **LEDs WS2812 e RGB**, e interação por meio de **botões com tratamento de debounce e interrupção**.

## Funcionalidades Implementadas

### 1. Modificação da Biblioteca `font.h`
- Adição de caracteres minúsculos personalizados.

### 2. Entrada de Caracteres via UART
- Digitação de caracteres pelo **Serial Monitor** do VS Code.
- Exibição do caractere no **display SSD1306 (I2C)**.
- Exibição de números (0-9) na matriz de LEDs WS2812.

### 3. Interação com os Botões
- **Botão A (GPIO 5):** Alterna o estado do LED RGB **Verde**.
  - Exibe uma mensagem no **display SSD1306**.
  - Envia informação ao **Serial Monitor**.
- **Botão B (GPIO 6):** Alterna o estado do LED RGB **Azul**.
  - Exibe uma mensagem no **display SSD1306**.
  - Envia informação ao **Serial Monitor**.

## Componentes Utilizados
- **Matriz 5x5 de LEDs WS2812** (GPIO 7)
- **LED RGB** (GPIOs 11, 12, 13)
- **Botão A** (GPIO 5)
- **Botão B** (GPIO 6)
- **Display OLED SSD1306** (I2C - GPIOs 14, 15)

## Aspectos do Projeto
- Implementação de **interrupções** para os botões.
- **Debouncing** via software.
- Controle de **LEDs comuns** e **LEDs endereçáveis WS2812**.
- **Código bem estruturado e comentado**.

## Como Executar

### **Pré-requisitos**
Certifique-se de que você tem o ambiente configurado corretamente:
- **Pico SDK** instalado
- **Extensões do Raspberry Pi Pico** no VS Code
- **CMake** e **compilador C/C++** instalados

### **Passos para Execução**
1. **Clone este repositório:**  
   ```sh
   git clone https://github.com/seu-usuario/nome-do-repositorio.git
   ```
2. **Abra a pasta do projeto** no VS Code.
3. **Compile o projeto**
   - Utilize a opção **Build** dentro da extensão do Pico SDK.
   - Verifique se o arquivo `.uf2` foi gerado corretamente na pasta `build`.
4. **Carregue o firmware na placa:**
   - Conecte a **BitDogLab** via USB.
   - Mantenha pressionado o botão **BOOTSEL** ao conectar a placa.
   - Arraste o arquivo `.uf2` gerado para a unidade de armazenamento da placa.
5. **Interaja com o sistema:**
   - **Digite caracteres** no Serial Monitor para que sejam exibidos no **display SSD1306**.
   - **Digite números (0-9)** para que sejam exibidos no **display** e na matriz **WS2812**.
   - **Pressione o Botão A** para alternar o LED **Verde** e ver a mensagem no **display e no Serial Monitor**.
   - **Pressione o Botão B** para alternar o LED **Azul** e ver a mensagem no **display e no Serial Monitor**.
