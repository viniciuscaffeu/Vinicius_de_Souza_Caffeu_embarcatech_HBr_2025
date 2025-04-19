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
- Pasta para arquivos de cabeçalho (se necessário)
- `README.md` com descrição específica do projeto

---

## Projetos desenvolvidos

# 1. Contador_decrescente 
  Exibe uma contagem decrescente de 9 a 0 usando Raspberry Pi Pico W e display OLED via I2C, com interação de dois botões físicos: um para iniciar a contagem e outro para contabilizar cliques (interrupção).

# 2. Joystick 
  Lê valores analógicos do joystick da BitDogLab e os exibe via terminal serial.

# 3. Temperatura/display_oled 
  Lê a temperatura interna do RP2040 usando o ADC e exibe o valor em um display OLED via protocolo I2C.

---


