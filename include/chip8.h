#ifndef CHIP8_HEADER
#define CHIP8_HEADER

typedef unsigned char byte;
typedef unsigned short word;

struct Chip8 {

    unsigned char ram[4096];
    unsigned char v[16];

    unsigned short i;
    unsigned char vf;

    unsigned char dt;
    unsigned char st;

    unsigned short pc;
    unsigned char sp;

    unsigned short stack[16];

}

unsigned short fetch(Chip8 *comp);

void execute(Chip8 *comp);

void cls(Chip8 *comp);
void ret(Chip8 *comp);
void jmp(Chip8 *comp);
void callnnn(Chip8 *comp);
void sevxnn(Chip8 *comp);
void snevxnn(Chip8 *comp);
void sevxvy(Chip8 *comp);
void ldvxnn(Chip8 *comp);
void addvxnn(Chip8 *comp);
void ldvxvy(Chip8 *comp);
void orvxvy(Chip8 *comp);
void addvxvy(Chip8 *comp);
void subvxvy(Chip8 *comp);
void shrvxvy(Chip8 *comp);
void subnvxvy(Chip8 *comp);
void shlvxvy(Chip8 *comp);
void snevxvy(Chip8 *comp);
void ldinnn(Chip8 *comp);
void jmpv0nnn(Chip8 *comp);
void rndvxnn(Chip8 *comp);
void drwvxvyn(Chip8 *comp);
void skpvx(Chip8 *comp);
void sknpvx(Chip8 *comp);
void ldvxdt(Chip8 *comp);
void ldvxk(Chip8 *comp);
void lddtvx(Chip8 *comp);
void ldstvx(Chip8 *comp);
void addivx(Chip8 *comp);
void ldfvx(Chip8 *comp);
void ldbvx(Chip8 *comp);
void ldivx(Chip8 *comp);
void ldvxi(Chip8 *comp);

#endif
