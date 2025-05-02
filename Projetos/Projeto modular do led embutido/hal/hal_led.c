#include "hal_led.h"
#include "led_embutido.h"

static bool estado_led = false;

void hal_led_init() {
    led_embutido_init();
}

void hal_led_toggle() {
    estado_led = !estado_led;
    led_embutido_set(estado_led);
}
