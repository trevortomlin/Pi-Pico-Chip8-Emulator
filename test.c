#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

#include "hardware/i2c.h"
#include "ssd1306.h"

const uint LED_PIN = 25;

const uint SCL_PIN = 4;
const uint SDA_PIN = 5;

const uint KBD_ROW_PINS[4];
const uint KBD_COL_PINS[4];

const uint BUZZER_PIN = 16;

int main() {

    bi_decl(bi_program_description("This is a test binary."));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
 
    i2c_init(i2c_default, 400000);

    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);

    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);

    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    ssd1306_t display;

    display.external_vcc = false;

    bool b = ssd1306_init(&display, 128, 64, 0x3C, i2c_default);

    ssd1306_clear(&display);
    
    ssd1306_draw_square(&display, 0, 0, 50, 50);

    ssd1306_show(&display);

    while (1) {
	
	printf("%d\n", b);
	gpio_put(LED_PIN, 0);
	sleep_ms(250);
	gpio_put(LED_PIN, 1);
	puts("Hello World\n");
	sleep_ms(1000);
    }
}
