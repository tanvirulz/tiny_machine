#include <stdlib.h>
#include <stdint.h>



struct Registers{
    uint16_t a,b,c,d; //work regitsers
    uint16_t dp, sp, pc, hp;
    uint16_t z;
};

struct Registers * init_registers (uint16_t pc);
void free_reg(struct Registers * R);