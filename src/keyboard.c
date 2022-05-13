#include "settings.h"
#include "pico/stdlib.h"
#include "keyboard.h"
#include <stddef.h>
#include <stdbool.h>

void kbd_init() {

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

char kbd_wait_input() {

    int row, col;

    for (row = 0; row < 4; row++) {

	kbd_reset();

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


void kbd_get_keys(bool kbd[]) {

    int row, col;

    for (row = 0; row < 4; row++) {

	kbd_reset();

	gpio_put(KBD_ROW_PINS[row], 1);

	sleep_us(100);

	for (col = 0; col < 4; col++) {

	    if (gpio_get(KBD_COL_PINS[col])) {
		
		kbd[row * 4 + col] = true;
	    
	    }

	    else {

		kbd[row * 4 + col] = false;

	    }

	}

    }

}

void kbd_reset() {

    int row, col;

    for (row = 0; row < 4; row++) {

	gpio_put(KBD_ROW_PINS[row], 0);

    }

    for (col = 0; col < 4; col++) {

	gpio_put(KBD_COL_PINS[col], 0);

    }

}
