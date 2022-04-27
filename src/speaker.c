void speaker_init() {

    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    uint chan = pwm_gpio_to_channel(BUZZER_PIN);
    pwm_set_freq_duty(slice_num, chan, BUZZER_FREQ, 50);

}

void speaker_enable() {

    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_set_enabled(slice_num, true);

}

void speaker_disable() {

    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_set_enabled(slice_num, false);

}

// Explains how to get desired frequency using PWM on the PICO
// https://www.i-programmer.info/programming/hardware/14849-the-pico-in-c-basic-pwm.html?start=2#:~:text=The%20PWM%20counter%20is%2016,PWM%20frequency%20at%201.9kHz.
void pwm_set_freq_duty(uint slice_num, uint chan, uint32_t f, int d) {

    uint32_t clock = 125000000;
    uint32_t divider16 = clock / f / 4096 + (clock % (f * 4096) != 0);

    if (divider16 / 16 == 0) divider16 = 16;

    uint32_t wrap = clock * 16 / divider16 / f - 1;

    pwm_set_clkdiv_int_frac(slice_num, divider16/16, divider16 & 0xF);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_chan_level(slice_num, chan, wrap * d / 100);

}
