#ifndef CHIP8_HEADER
#define CHIP8_HEADER

typedef struct Chip8 Chip8;
typedef unsigned char byte;
typedef unsigned short word;

const uint CHIP8_HEIGHT = 64;
const uint CHIP8_WIDTH = 32;

struct Chip8 {

    byte ram[4096];
    byte v[16];

    word i;
    byte vf;

    byte dt;
    byte st;

    word pc;
    byte sp;

    word stack[16];

    byte buffer[CHIP8_HEIGHT * CHIP8_WIDTH];

    bool kbd[16];

}

void chip8_init();
void chip8_cycle();
void chip8_render();

word fetch(Chip8 *comp);

void execute(Chip8 *comp);

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
void rndvxnn(Chip8 *comp, byte nn);
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
