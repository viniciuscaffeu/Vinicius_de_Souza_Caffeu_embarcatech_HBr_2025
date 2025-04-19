# Projetos de Sistemas Embarcados - EmbarcaTech 2025

**Autor:** Vinicius de Souza Caffeu  

**Curso:** Residência Tecnológica em Sistemas Embarcados  

**Instituição:** EmbarcaTech - HBr  

**Local:** Campinas, março de 2025

---

## Sobre este repositório

Este repositório reúne os projetos desenvolvidos durante a residência em Sistemas Embarcados, utilizando o microcontrolador Raspberry Pi Pico (RP2040) e a plataforma BitDogLab.

Cada projeto está em sua própria pasta, contendo:

- Código-fonte em C
- Arquivo `CMakeLists.txt` para build
- Pasta `inc/` para arquivos de cabeçalho (se necessário)
- `README.md` com descrição específica do projeto

---

## Projetos desenvolvidos

- `contador_decrescente/`  
  Exibe uma contagem regressiva usando a matriz de LEDs RGB da BitDogLab.

- `joystick/`  
  Lê valores analógicos do joystick da BitDogLab e os exibe via terminal serial.

- `temperatura/display_oled/`  
  Lê a temperatura interna do RP2040 usando o ADC e exibe o valor em um display OLED via protocolo I2C.

---

## Organização das pastas

