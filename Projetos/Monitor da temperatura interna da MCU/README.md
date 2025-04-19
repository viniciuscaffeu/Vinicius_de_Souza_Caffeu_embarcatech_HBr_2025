# 🖥️ Projeto: Leitura de Temperatura com Display OLED

Este projeto utiliza o microcontrolador **Raspberry Pi Pico W** para:

- Ler a **temperatura interna** via ADC (canal 4)
- Converter o valor para **graus Celsius**
- Exibir a temperatura em um **display OLED 128x64** via protocolo I2C
- Mostrar a leitura também no terminal serial via `printf`

---

## ⚙️ Hardware Utilizado

- Raspberry Pi Pico W
- Display OLED 128x64 (controlado via `ssd1306.h`)
- Conexões I2C:
  - SDA: GPIO 14
  - SCL: GPIO 15

---

## 🧰 Bibliotecas Utilizadas

```c
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include <string.h>
```

---

## 📐 Conversão da Temperatura

A leitura da temperatura é feita através do **sensor interno do RP2040**, acessado via ADC no canal 4.

O valor bruto do ADC é convertido para tensão (em volts), e então transformado em temperatura (°C) usando a equação oficial do datasheet:

```c
float voltage = adc_value * (3.3f / 4096);
float temperature = 27.0f - (voltage - 0.706f) / 0.001721f;
```

### Significado dos termos:
- `adc_value`: valor lido no canal ADC (12 bits)
- `3.3f`: tensão de referência da ADC
- `0.706f`: tensão típica do sensor de temperatura a 27°C
- `0.001721f`: variação da tensão por grau Celsius

Essa equação permite uma estimativa simples da temperatura ambiente no microcontrolador.

---

## 🔄 Fluxo do Programa

1. Inicialização do ADC e do sensor de temperatura interno
2. Configuração da comunicação I2C com o display
3. Inicialização do display OLED
4. Loop principal:
   - Leitura do valor ADC
   - Conversão para °C
   - Impressão no terminal serial
   - Exibição no display OLED

---

## 💤 Intervalo de Atualização

- As medições de temperatura são feitas a cada **1 segundo** com `sleep_ms(1000)`

---

## 📁 Estrutura do Projeto

```
display_oled/
├── CMakeLists.txt
├── display_oled.c
├── inc/
│   └── ssd1306.h
├── lib/
│   └── ssd1306.c
└── README.md
```

---

## ✅ Resultados Esperados

- A temperatura será exibida continuamente no display OLED
- A mesma leitura será impressa no terminal serial no formato:

```
Temperatura: 28.34 °C
```

---

## 📦 Compilação

Para compilar o projeto:

```bash
mkdir build
cd build
cmake ..
ninja
```

---

## 📌 Observações

- Certifique-se de que os arquivos `ssd1306.h` e `ssd1306.c` estão corretamente incluídos no projeto e adicionados ao CMake.
- Verifique se o caminho do SDK está configurado corretamente.

