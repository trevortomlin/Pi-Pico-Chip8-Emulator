#include "settings.h"

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
	gpio_put(KBD_COL_PINS[col], 0);
    
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
