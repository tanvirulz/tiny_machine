#include "registers.h"

/** 
 * allocates memory for registers 
 * initializes the programm counter to its start point
 * */
struct Registers * init_registers (uint16_t program_start_point, uint16_t stack_segment_start_point){
    struct Registers * R;
    R = (struct Registers *) malloc(sizeof(struct Registers));
    R->reg[_pc] = program_start_point;
    R->reg[_sp] = stack_segment_start_point;
    return R;
}

void free_reg(struct Registers * R){
    free(R);
}

void reset_pc(struct Registers * r, uint16_t pc_start){
    r->reg[_pc] = pc_start;

}