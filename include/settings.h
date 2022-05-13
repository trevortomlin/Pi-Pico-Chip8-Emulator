#ifndef SETTINGS_HEADER
#define SETTINGS_HEADER

#include "pico/stdlib.h"

static const uint KBD_ROW_PINS[4] = {15, 14, 13, 12};
static const uint KBD_COL_PINS[4] = {11, 10, 9, 8};

static const uint BUZZER_PIN = 16;
static const uint BUZZER_FREQ = 440;

static const uint DISPLAY_WIDTH = 128;
static const uint DISPLAY_HEIGHT = 64;

static const uint SPRITE_WIDTH = 8;

#endif
