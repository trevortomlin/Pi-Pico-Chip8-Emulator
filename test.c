#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

#include "hardware/i2c.h"
#include "ssd1306.h"

const uint LED_PIN = 25;

const uint KBD_ROW_PINS[4] = {15, 14, 13, 12};
const uint KBD_COL_PINS[4] = {11, 10, 9, 8};

const uint BUZZER_PIN = 16;

char get_key_pressed();
void init_kbd();

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

    init_kbd();

    ssd1306_t display;

    display.external_vcc = false;

    ssd1306_init(&display, 128, 64, 0x3C, i2c_default);

    ssd1306_clear(&display);
    
    ssd1306_draw_square(&display, 0, 0, 128, 64);

    ssd1306_show(&display);

    while (1) {
	
	get_key_pressed();
	gpio_put(LED_PIN, 0);
	sleep_ms(250);
	gpio_put(LED_PIN, 1);
	puts("Hello World\n");
	sleep_ms(1000);
    }
}

void init_kbd() {

    int row, col;

    for (row = 0; row < 4; row++) {
    
	gpio_set_dir(KBD_ROW_PINS[row], GPIO_OUT);
    
    }

    for (col = 0; col < 4; col++) {

	gpio_set_dir(KBD_COL_PINS[col], GPIO_IN);

    }

}

char get_key_pressed() {

    int row;
    int col;

    for (row = 0; row < 4; row++) {

	gpio_put(KBD_ROW_PINS[row], 0);	
	
	for (col = 0; col < 4; col++) {

	    gpio_put(KBD_COL_PINS[col], 0);

	}

	gpio_put(KBD_ROW_PINS[row], 1);

	for (col = 0; col < 4; col++) {
	
	    if (gpio_get(KBD_COL_PINS[col])) {
	    
		printf("row: %d, col: %d\n", row, col);
		return 'A';

	    }

	}

	gpio_put(KBD_ROW_PINS[row], 0);

    }

    printf("not detected", row, col);

    return "F";

}
