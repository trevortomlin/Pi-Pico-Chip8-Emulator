#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

#include "hardware/i2c.h"
#include "ssd1306.h"

const uint LED_PIN = 25;

const uint KBD_ROW_PINS[4] = {15, 14, 13, 12};
const uint KBD_COL_PINS[4] = {11, 10, 9, 8};
const char KBD_TO_CHAR[4][4] = {{'1', '2', '3', 'C'},
				{'4', '5', '6', 'D'},
				{'7', '8', '9', 'E'},
				{'A', '0', 'B', 'F'}};

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
    
    //ssd1306_draw_square(&display, 0, 0, 128, 64);


    while (1) {

	puts(" ");

	ssd1306_draw_char(&display, 64, 32, 1, get_key_pressed());
	ssd1306_show(&display);

    }
}

void init_kbd() {

    int row, col;

    for (row = 0; row < 4; row++) {
	
	gpio_init(KBD_ROW_PINS[row]);
	gpio_set_dir(KBD_ROW_PINS[row], GPIO_OUT);
    
    }

    for (col = 0; col < 4; col++) {
	
	gpio_init(KBD_COL_PINS[col]);
	gpio_set_dir(KBD_COL_PINS[col], GPIO_IN);
	gpio_pull_down(KBD_COL_PINS[col]);
	
    }

}

char get_key_pressed() {

    int row, row1, col;
    

    for (row = 0; row < 4; row++) {

	for (row1 = 0; row1 < 4; row1++) {

	    gpio_put(KBD_ROW_PINS[row1], 0);

	}

	gpio_put(KBD_ROW_PINS[row], 1);

	for (col = 0; col < 4; col++) {
	
	    if (gpio_get(KBD_COL_PINS[col])) {
			    
		return KBD_TO_CHAR[row][col];

	    }

	}

    }

    return NULL;

}
