#ifndef CHIP8_HEADER
#define CHIP8_HEADER

#include "pico/stdlib.h"
#include "ssd1306.h"
#include "stdbool.h"

typedef struct Chip8 Chip8;
typedef unsigned char byte;
typedef unsigned short word;

const uint CHIP8_HEIGHT = 64;
const uint CHIP8_WIDTH = 32;

struct Chip8 {

    byte memory[4096];
    byte v[16];

    word i;
    byte vf;

    byte dt;
    byte st;

    word pc;
    byte sp;

    word stack[16];

    bool buffer[CHIP8_HEIGHT * CHIP8_WIDTH];

    bool kbd[16];

    ssd1306_t *disp;

    bool paused;
};

void chip8_init(Chip8 *comp);
void chip8_cycle(Chip8 *comp);
void chip8_render(Chip8 *comp, uint scale);

word fetch(Chip8 *comp);

void execute(Chip8 *comp, word opcode);

void cls(Chip8 *comp);
void ret(Chip8 *comp);
void jmp(Chip8 *comp, word nnn);
void callnnn(Chip8 *comp, word nnn);
void sevxnn(Chip8 *comp, byte x, byte y);
void snevxnn(Chip8 *comp, byte x, byte y);
void sevxvy(Chip8 *comp, byte x, byte y);
void ldvxnn(Chip8 *comp, byte x, byte y);
void addvxnn(Chip8 *comp, byte x, byte y);
void ldvxvy(Chip8 *comp, byte x, byte y);
void orvxvy(Chip8 *comp, byte x, byte y);
void andvxvy(Chip8 *comp, byte x, byte y);
void xorvxvy(Chip8 *comp, byte x, byte y);
void addvxvy(Chip8 *comp, byte x, byte y);
void subvxvy(Chip8 *comp, byte x, byte y);
void shrvxvy(Chip8 *comp, byte x, byte y);
void subnvxvy(Chip8 *comp, byte x, byte y);
void shlvxvy(Chip8 *comp, byte x, byte y);
void snevxvy(Chip8 *comp, byte x, byte y);
void ldinnn(Chip8 *comp, word nnn);
void jmpv0nnn(Chip8 *comp, word nnn);
void rndvxnn(Chip8 *comp, byte x, byte nn);
void drwvxvyn(Chip8 *comp, byte x, byte y, byte n);
void skpvx(Chip8 *comp, byte x);
void sknpvx(Chip8 *comp, byte x);
void ldvxdt(Chip8 *comp, byte x);
void ldvxk(Chip8 *comp, byte x);
void lddtvx(Chip8 *comp, byte x);
void ldstvx(Chip8 *comp, byte x);
void addivx(Chip8 *comp, byte x);
void ldfvx(Chip8 *comp, byte x);
void ldbvx(Chip8 *comp, byte x);
void ldivx(Chip8 *comp, byte x);
void ldvxi(Chip8 *comp, byte x);

#endif
