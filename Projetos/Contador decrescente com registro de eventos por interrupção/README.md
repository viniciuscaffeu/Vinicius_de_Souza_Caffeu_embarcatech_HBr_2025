# 🧮 Contador Decrescente com OLED 

Este projeto apresenta um contador decrescente de 9 a 0 utilizando o Raspberry Pi Pico W e um display OLED conectado via I2C. A proposta visa demonstrar o uso de periféricos em sistemas embarcados, incorporando também a interação com dois botões físicos: um para iniciar a contagem e outro para contabilizar cliques durante a execução.

Ao energizar o sistema, o display exibe a mensagem **"Pressione A"**, sinalizando que o dispositivo está pronto para começar. Ao pressionar o **Botão A** (GPIO5), a contagem decrescente inicia, com decremento de 1 em 1 segundo. Durante esse processo, cada clique no **Botão B** (GPIO6) é registrado e exibido em tempo real no display. Ao final da contagem, o sistema exibe **"FIM!"** e o total de cliques, incentivando nova interação.

O display OLED se comunica por meio do barramento I2C, utilizando os pinos **GPIO14 (SDA)** e **GPIO15 (SCL)** da placa Pico W. Os botões utilizam resistores de pull-up ativados por software.

Além da interface visual, o programa também imprime mensagens no terminal serial para facilitar a depuração e o acompanhamento em tempo real. O código-fonte está dividido em:

- `main.c`: responsável pela lógica principal do programa e controle de eventos.
- `ssd1306.h`: biblioteca para comunicação com o display OLED via I2C.

## 🔧 Requisitos de Hardware

- Raspberry Pi Pico W  
- Display OLED (I2C, 128x64)  
- 2 botões táteis  

## 🚀 Execução

1. Compile o projeto usando o SDK da Raspberry Pi Pico.
2. Gere o arquivo `.uf2` e transfira para o Pico em modo boot.
3. Pressione o botão A para iniciar a contagem.
4. Pressione o botão B durante a contagem para registrar cliques.

## 🎓 Aplicação

Este projeto faz parte da disciplina de Sistemas Embarcados do **EMBARCATECH 2025**, com foco na integração de periféricos, controle de tempo, interrupções e interação homem-máquina.

## 📄 Licença

Distribuído sob a Licença MIT.
