#include "chip8.h"

const unsigned char fontset[80] = 
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, //0
    0x20, 0x60, 0x20, 0x20, 0x70, //1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
    0x90, 0x90, 0xF0, 0x10, 0x10, //4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
    0xF0, 0x10, 0x20, 0x40, 0x40, //7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
    0xF0, 0x90, 0xF0, 0x90, 0x90, //A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
    0xF0, 0x80, 0x80, 0x80, 0xF0, //C
    0xE0, 0x90, 0x90, 0x90, 0xE0, //D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
    0xF0, 0x80, 0xF0, 0x80, 0x80  //F

}; 

unsigned short fetch(Chip8 *comp) {

    unsigned short opcode = (comp->PC >> 8) | (comp->PC+1);
    comp->pc+=2;

    return opcode;

}

void execute(Chip8 *comp, unsigned short opcode) {

    
    unsigned short nnn = opcode & 0x0FFF;
    unsigned char n = opcode & 0x000F;
    unsigned char x = opcode & 0x0F00;
    unsigned char y = opcode & 0x00F0;
    unsigned char nn = opcode & 0x00FF;

    switch(opcode & 0xF000) {

	case 0x0000:
	    
	    switch(opcode & 0x00FF) {

		case 0xE0:

		    cls(comp);

		    break;

		case 0xEE:

		    ret(comp);

		    break;

	    }

	    break;

	case 0x1000:
	    
	    jmp(comp, nnn);

	    break;


	case 0x2000:

	    callnnn(comp, nnn);

	    break;
	
	case 0x3000: 

	    sevnn(comp, x, nn);
	    
	    break;

	case 0x4000:

	    snevxnn(comp, x, nn);

	    break;

	case 0x5000:
	    
	    sevxvy(comp, x, y);

	    break;

	case 0x6000:
	
	    ldvxnn(comp, x, nn);

	    break;

	case 0x7000:
	    
	    addvxnn(comp, x, nn);

	    break;

	case 0x8000:
	    
	    switch (opcode & 0x000F) {

		case 0x0:
		    
		    ldvxvy(comp, x, y);

		    break;

		case 0x1:

		    orvxvy(comp, x, y);

		    break;

		case 0x2:

		    andvxvy(comp, x, y);

		    break;

		case 0x3:

		    xorvxvy(comp, x, y);

		    break;

		case 0x4:

		    addvxvy(comp, x, y);

		    break;

		case 0x5:
		
		    subvxvy(comp, x, y);

		    break;

		case 0x6:

		    shrvxvy(comp, x, y);

		    break;

		case 0x7:

		    subnvxvy(comp, x, y);

		    break;

		case 0xE:

		    shlvxvy(comp, x, y);

		    break;

	    }

	    break;

	case 0x9000:
	    
	    snevxvy(comp, x, y);

	    break;

	case 0xA000:

	    ldinnn(comp, nnn);

	    break;

	case 0xB000:
	
	    jmpv0nnn(comp, nnn);

	    break;

	case 0xC000:
	    
	    rndvxnn(comp, x, nn);

	    break;

	case 0xD000:

	    drwvxvyn(comp, x, y, n);

	    break;

	case 0xE000:

	    switch (opcode & 0x000F) {

		case 0xE:

		    skpvx(comp, x);

		    break;

		case 0x1:

		    sknpvx(comp,x );

		    break;
    
	    }

	    break;

	case 0xF000:
	    
	    switch(opcode & 0x00FF) {
	
		case 0x07:

		    ldvxdt(comp, x);

		    break;

		case 0x0A:

		    ldvxk(comp, x);

		    break;

		case 0x15:

		    lddtvx(comp, x);

		    break;

		case 0x18:

		    ldstvx(comp, x);

		    break;

		case 0x1E:

		    addivx(comp, x);

		    break;

		case 0x29:

		    ldfvx(comp, x);

		    break;

		case 0x33:

		    ldbvx(comp, x);

		    break;

		case 0x55:

		    ldivx(comp, x);

		    break;

		case 0x65:

		    ldvxi(comp, x);

		    break;
    
	    }
	    
	    break;

    }

}

void cls(Chip8 *comp);

void ret(Chip8 *comp) {

    comp->pc = comp->stack[comp->sp];
    comp->sp--;

}

void jmp(Chip8 *comp, unsigned short nnn) {

    comp->pc = nnn;

}

void callnnn(Chip8 *comp, unsigned short nnn) {

    comp->sp++;
    comp->stack[comp->sp] = comp->pc;
    comp->pc = nnn;

}

void sevxnn(Chip8 *comp, unsigned char x, unsigned char nn) {

    if (comp->v[x] == nn) {

	comp->pc+=2;

    }

}

void snevxnn(Chip8 *comp, unsigned char x, unsigned char nn) {

    if (comp->v[x] != nn) {

	comp->pc+=2;

    }

}

void sevxvy(Chip8 *comp, unsigned char x, unsigned char y) {

    if (comp->v[x] == comp->v[y]) {

	comp->pc+=2;

    }

}

void ldvxnn(Chip8 *comp, unsigned char x, unsigned char nn) {

    comp->v[x] = nn;

}

void addvxnn(Chip8 *comp, unsigned char x, unsigned char nn) {

    comp->v[x] += nn;

}

void ldvxvy(Chip8 *comp, unsigned char x, unsigned char y) {

    comp->v[x] = comp->v[y];

}

void orvxvy(Chip8 *comp, unsigned char x, unsigned char y) {

    comp->v[x] = comp->v[x] | comp->v[y];

}

void andvxvy(Chip8 *comp, unsigned char x, unsigned char y) {

    comp->v[x] = comp->v[x] & comp->v[y];

}

void xorvxvy(Chip8 *comp, unsigned char x, unsigned char y) {

    comp->v[x] = comp->v[x] ^ comp->v[y];

}

void addvxvy(Chip8 *comp, unsigned char x, unsigned char y) {

    unsigned short res = comp->v[x] + comp->[y];

    if (res > 0xFF) {

	comp->vf = 1;

    }

    else {

	comp->vf = 0;

    }

    comp->v[x] += comp->v[y];
    

}

void subvxvy(Chip8 *comp, unsigned char x, unsigned char y) {

    if (comp->v[x] > comp->v[y]) {

	comp->vf = 1;

    }

    else {

	comp->vf = 0;

    }

    comp->v[x] -= comp->v[y];
    
}

void shrvxvy(Chip8 *comp, unsigned char x) {

    comp->vf = comp->v[x] & 0x01;
    comp->v[x] = comp->v[x] >> 1;

}

void subnvxvy(Chip8 *comp, unsigned char x, unsigned char y) {

    if (comp->v[x] > comp->v[y]) {

	comp->vf = 1;

    }

    else {

	comp->vf = 0;

    }

    comp->v[x] = comp->v[y] - comp->v[x];

}

void shlvxvy(Chip8 *comp, unsigned char x) {

    comp->vf = comp->v[x] & 0x80;
    comp->v[x] = comp->v[x] << 1;

}

void snevxvy(Chip8 *comp, unsigned char x, unsigned char y) {

    if (comp->v[x] != comp->v[y]) {

	comp->pc+=2;

    }

}

void ldinnn(Chip8 *comp, unsigned short nnn) {

    comp->i = nnn;

}

void jmpv0nnn(Chip8 *comp, unsigned short nnn) {

    comp->pc = comp->v[0] + nnn;

}

void rndvxnn(Chip8 *comp, unsigned char nn) {

    comp->v[x] = rand() & nn;

}

void drwvxvyn(Chip8 *comp, unsigned char x, unsigned char y, unsigned char n) {}

void skpvx(Chip8 *comp, unsigned char x) {}

void sknpvx(Chip8 *comp, unsigned char x) {}

void ldvxdt(Chip8 *comp, unsigned char x) {

    comp->v[x] = dt;

}

void ldvxk(Chip8 *comp, unsigned char x) {}

void lddtvx(Chip8 *comp, unsigned char x) {

    comp->dt = comp->v[x];

}

void ldstvx(Chip8 *comp, unsigned char x) {

    comp->st = comp->v[x];

}

void addivx(Chip8 *comp, unsigned char x) {

    comp->i += x;

}

void ldfvx(Chip8 *comp, unsigned char x) {}

void ldbvx(Chip8 *comp, unsigned char x) {}

void ldivx(Chip8 *comp, unsigned char x) {}

void ldvxi(Chip8 *comp, unsigned char x) {}
