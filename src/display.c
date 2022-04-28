void display_render(ssd1306_t *disp, bool buffer, uint scale) {

    ssd1306_clear(disp);

    int i, j;

    uint b_len = CHIP8_HEIGHT * CHIP8_WIDTH;

    for (i = 0; i < b_len; i+=scale) {

	for (j = i; j < scale; j++) {

	    disp->buffer[j] = buffer[i];

	}

    }

    ssd1306_show(disp);

}
