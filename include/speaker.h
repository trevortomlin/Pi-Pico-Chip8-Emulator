#ifndef SPEAKER_GUARD
#define SPEAKER_GUARD

void speaker_init();
void speaker_eneable();
void speaker_disable();
void pwm_set_freq_duty(uint, uint, uint32_t);

#endif
