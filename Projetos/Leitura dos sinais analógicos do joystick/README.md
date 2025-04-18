# 📦 Leitura do Joystick da BitDogLab com Exibição no Terminal Serial

Este projeto em C utiliza o microcontrolador Raspberry Pi Pico da BitDogLab para ler os valores analógicos do joystick usando o conversor ADC (Analógico-Digital) e exibi-los no terminal serial. O projeto permite visualizar em tempo real a movimentação do joystick, tanto por meio de barras com bolinhas quanto pelos valores numéricos convertidos.

---

## 📁 Base do Projeto

O projeto original encontra-se no repositório oficial da BitDogLab, dentro do diretório de exemplos para o joystick.

**Repositório:** (https://github.com/BitDogLab/BitDogLab-C)  
**Diretório:** `joystick`

---

## ✏️ Modificações Realizadas

As seguintes alterações foram feitas no código original da BitDogLab:

- Adição da exibição dos **valores numéricos ADC brutos** para os eixos X e Y do joystick diretamente no terminal serial, juntamente com a representação visual por barras.

---

## 📷 Exemplo de Saída no Terminal

```text
X: [           o                    ]  Y: [              o              ]  | Valores: X=2034 Y=1945
X: [             o                  ]  Y: [               o             ]  | Valores: X=2200 Y=2050
X: [               o                ]  Y: [                 o           ]  | Valores: X=2405 Y=2190

