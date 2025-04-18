/*
*EMBARCATECH 2025
 * Contador Decrescente com Display OLED - Raspberry Pi Pico W
 * Autor: Vinicius de Souza Caffeu
 * 
 * Este projeto implementa um contador decrescente de 9 a 0 com:
 * - Botão A para iniciar/reiniciar contagem
 * - Botão B para registrar cliques durante a contagem
 * - Display OLED I2C para visualização
 * - Saída serial para debug
 */

 #include <stdio.h>
 #include <string.h>
 #include "pico/stdlib.h"
 #include "hardware/gpio.h"
 #include "hardware/irq.h"
 #include "hardware/timer.h"
 #include "hardware/i2c.h"
 #include "inc/ssd1306.h"  // Biblioteca customizada para OLED
 
 // ========== CONFIGURAÇÃO DE HARDWARE ==========
 #define BOTAO_A 5      // GPIO para botão de início/reset
 #define BOTAO_B 6      // GPIO para botão de contagem
 #define INTERVALO_US 1000000  // Intervalo de 1s para o timer
 #define I2C_SDA 14     // GPIO para I2C (OLED)
 #define I2C_SCL 15     // GPIO para I2C (OLED)
 
 // ========== VARIÁVEIS GLOBAIS ==========
 volatile int contador = 0;      // Valor atual do contador
 volatile int cliques_b = 0;     // Contagem de cliques no botão B
 volatile bool contando = false; // Flag de contagem ativa
 volatile bool terminou = false; // Flag de contagem finalizada
 
 // Estrutura para controle do display OLED
 struct render_area frame_area = {
     start_column : 0,          // Coluna inicial
     end_column : ssd1306_width - 1, // Coluna final
     start_page : 0,            // Página inicial
     end_page : ssd1306_n_pages - 1  // Página final
 };
 uint8_t ssd[ssd1306_buffer_length]; // Buffer para o display
 
 // ========== FUNÇÕES DO DISPLAY OLED ==========
 /**
  * Inicializa o display OLED via I2C
  * Configura pinos, interface e limpa a tela
  */
 void init_display() {
     // Configura I2C a 400kHz
     i2c_init(i2c1, ssd1306_i2c_clock * 1000);
     
     // Configura pinos I2C
     gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
     gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
     gpio_pull_up(I2C_SDA);  // Habilita pull-up
     gpio_pull_up(I2C_SCL);
     
     // Inicializa display
     ssd1306_init();
     calculate_render_area_buffer_length(&frame_area);
     memset(ssd, 0, ssd1306_buffer_length);  // Limpa buffer
     render_on_display(ssd, &frame_area);     // Atualiza display
 }
 
 /**
  * Atualiza o conteúdo do display OLED
  * Mostra três linhas com:
  * 1. Estado da contagem
  * 2. Cliques no botão B
  * 3. Instruções para o usuário
  */
 void update_display() {
     memset(ssd, 0, ssd1306_buffer_length);  // Limpa buffer
     
     // Linha 1: Estado da contagem
     char linha1[20];
     if (contando) {
         snprintf(linha1, sizeof(linha1), "Contagem: %d", contador);
     } else if (terminou) {
         snprintf(linha1, sizeof(linha1), "FIM!");
     } else {
         snprintf(linha1, sizeof(linha1), "Aguardando...");
     }
     
     // Linha 2: Contagem de cliques
     char linha2[20];
     snprintf(linha2, sizeof(linha2), "Cliques B: %d", cliques_b);
     
     // Linha 3: Mensagem de status
     char linha3[20];
     if (!contando && !terminou) {
         snprintf(linha3, sizeof(linha3), "Pressione A");
     } else if (terminou) {
         snprintf(linha3, sizeof(linha3), "Total: %d", cliques_b);
     } else {
         snprintf(linha3, sizeof(linha3), "Pressione B");
     }
     
     // Desenha strings no buffer
     ssd1306_draw_string(ssd, 5, 0, linha1);   // Linha 1 (Y=0)
     ssd1306_draw_string(ssd, 5, 16, linha2);  // Linha 2 (Y=16)
     ssd1306_draw_string(ssd, 5, 32, linha3);   // Linha 3 (Y=32)
     
     render_on_display(ssd, &frame_area);  // Atualiza display físico
 }
 
 // ========== MANIPULAÇÃO DE INTERRUPÇÕES ==========
 /**
  * Handler de interrupção do timer
  * Decrementa o contador a cada 1s e atualiza o display
  */
 void timer_irq() {
     hw_clear_bits(&timer_hw->intr, 1u << 0);  // Limpa flag de interrupção
 
     if (contando && contador > 0) {
         contador--;  // Decrementa contador
         printf("Contador: %d\n", contador);
         update_display();
 
         if (contador == 0) {  // Contagem finalizada
             contando = false;
             terminou = true;
             printf("Fim da contagem. Cliques: %d\n", cliques_b);
             update_display();
         }
     }
 
     // Reagenda próximo alarme
     uint64_t agora = timer_hw->timerawl;
     timer_hw->alarm[0] = (uint32_t)(agora + INTERVALO_US);
 }
 
 /**
  * Handler de interrupção dos botões
  * Botão A: Inicia/reinicia contagem
  * Botão B: Registra cliques durante a contagem
  */
 void gpio_callback(uint gpio, uint32_t events) {
     if (gpio == BOTAO_A && (events & GPIO_IRQ_EDGE_FALL)) {
         // Reinicia contagem
         contador = 9;
         cliques_b = 0;
         contando = true;
         terminou = false;
         printf("Contagem iniciada: %d\n", contador);
         update_display();
     }
 
     if (gpio == BOTAO_B && (events & GPIO_IRQ_EDGE_FALL)) {
         if (contando) {  // Só conta se a contagem estiver ativa
             cliques_b++;
             printf("Botão B pressionado - Total: %d\n", cliques_b);
             update_display();
         }
     }
 }
 
 // ========== CONFIGURAÇÃO INICIAL ==========
 /**
  * Configura GPIOs e interrupções dos botões
  */
 void setup_gpio() {
     // Botão A
     gpio_init(BOTAO_A);
     gpio_set_dir(BOTAO_A, GPIO_IN);
     gpio_pull_up(BOTAO_A);  // Habilita resistor pull-up
     gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
 
     // Botão B
     gpio_init(BOTAO_B);
     gpio_set_dir(BOTAO_B, GPIO_IN);
     gpio_pull_up(BOTAO_B);
     gpio_set_irq_enabled(BOTAO_B, GPIO_IRQ_EDGE_FALL, true);
 }
 
 /**
  * Configura timer com interrupção periódica
  */
 void setup_timer_irq() {
     // Agenda primeiro alarme
     uint64_t agora = timer_hw->timerawl;
     timer_hw->alarm[0] = (uint32_t)(agora + INTERVALO_US);
     
     // Habilita interrupção
     hw_set_bits(&timer_hw->inte, 1u << 0);
     irq_set_exclusive_handler(TIMER_IRQ_0, timer_irq);
     irq_set_enabled(TIMER_IRQ_0, true);
 }
 
 // ========== FUNÇÃO PRINCIPAL ==========
 int main() {
     stdio_init_all();  // Inicializa comunicação serial
     sleep_ms(2000);    // Espera estabilização
     
     init_display();    // Inicializa OLED
     setup_gpio();      // Configura botões
     setup_timer_irq(); // Configura timer
     
     update_display();  // Mostra tela inicial
     
     while (1) {
         tight_loop_contents();  // Loop principal vazio (tudo por interrupção)
     }
 }