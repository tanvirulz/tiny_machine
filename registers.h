#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdlib.h>
#include <stdint.h>

// big value for dev stage. will change later
#define NUMBER_OF_REGISTERS 256

enum registers {
    _a,_b,_c,_d,_dp,_sp,_pc,_hp,_z,_v,_DM
};

struct Registers{
    uint16_t reg[NUMBER_OF_REGISTERS]; //{ A B C D dp sp pc hp z v}
    /*uint16_t a,b,c,d; //work regitsers
    uint16_t dp, sp, pc, hp;
    uint16_t z,v; */
};

struct Registers * init_registers (uint16_t pc,uint16_t sp);
void free_reg(struct Registers * R);
void reset_pc(struct Registers * r, uint16_t pc_start);

#endif /*REGISTERS_H*/