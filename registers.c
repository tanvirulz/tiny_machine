#include "registers.h"

/** 
 * allocates memory for registers 
 * initializes the programm counter to its start point
 * */
struct Registers * init_registers (uint16_t program_start_point){
    struct Registers * R;
    R = (struct Registers *) malloc(sizeof(struct Registers));
    R->pc = program_start_point;
    return R;
}

void free_reg(struct Registers * R){
    free(R);
}