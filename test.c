#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

#include "hardware/pwm.h"

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
void reset_kbd();
void pwm_set_freq_duty(uint slice_num, uint chan, uint32_t f, int d);

int main() {

    bi_decl(bi_program_description("This is a test binary."));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    i2c_init(i2c_default, 400000);

    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);

    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    init_kbd();

    ssd1306_t display;

    display.external_vcc = false;

    ssd1306_init(&display, 128, 64, 0x3C, i2c_default);

    ssd1306_clear(&display);
    
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    //pwm_set_wrap(slice_num, 2);
    //pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
    //pwm_set_chan_level(slice_num, PWM_CHAN_B, 2);
    //pwm_set_clkdiv(slice_num, 16);
    
    uint chan = pwm_gpio_to_channel(BUZZER_PIN);
    pwm_set_freq_duty(slice_num, chan, 440, 50);

    while (1) {

	char k = get_key_pressed();
	
	if (k != NULL) {
	    
	    pwm_set_enabled(slice_num, true);
	    puts("");
	    ssd1306_clear(&display);
	    ssd1306_draw_char(&display, 64, 32, 4, k);

	}

	else {


	    pwm_set_enabled(slice_num, false);

	}

	ssd1306_show(&display);

    }
}

void init_kbd() {

    int row, col;

    for (row = 0; row < 4; row++) {
	
	gpio_init(KBD_ROW_PINS[row]);
	gpio_set_dir(KBD_ROW_PINS[row], GPIO_OUT);
	gpio_pull_down(KBD_ROW_PINS[row]);
	gpio_put(KBD_ROW_PINS[row], 0);
    
    }

    for (col = 0; col < 4; col++) {
	
	gpio_init(KBD_COL_PINS[col]);
	gpio_set_dir(KBD_COL_PINS[col], GPIO_IN);
	gpio_pull_down(KBD_COL_PINS[col]);
	
    }

}

char get_key_pressed() {

    int row, col;
    
    for (row = 0; row < 4; row++) {

	reset_kbd();

	gpio_put(KBD_ROW_PINS[row], 1);

	sleep_us(100);

	for (col = 0; col < 4; col++) {

	    if (gpio_get(KBD_COL_PINS[col])) {
		return KBD_TO_CHAR[row][col];

	    }

	}
	
    }

    return NULL;

}

void reset_kbd() {

    int row, col;

    for (row = 0; row < 4; row++) {

	gpio_put(KBD_ROW_PINS[row], 0);

    }

    for (col = 0; col < 4; col++) {

	gpio_put(KBD_COL_PINS[col], 0);

    }

}

// 
void pwm_set_freq_duty(uint slice_num, uint chan, uint32_t f, int d) {

    uint32_t clock = 125000000;
    uint32_t divider16 = clock / f / 4096 + (clock % (f * 4096) != 0);

    if (divider16 / 16 == 0) divider16 = 16;

    uint32_t wrap = clock * 16 / divider16 / f - 1;

    pwm_set_clkdiv_int_frac(slice_num, divider16/16, divider16 & 0xF);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_chan_level(slice_num, chan, wrap * d / 100);

}
