#include "unit_tests.h"



int test_processor(){
    struct Processor *p;
    p = init_processor();
    struct Instruction * inst = (struct Instruction *) malloc(sizeof(struct Instruction));
    load_instruction(p,0x23,0x3,0xf,0x8086);
    load_instruction(p,0x8f,0x3,0xf,0x5086);
    load_instruction(p,0x10,0x4,0xe,0x86);
    load_instruction(p,0x23,0x3,0xf,0x8086);
    load_instruction(p,0x8f,0x3,0xf,0x5086);
    load_instruction(p,0x10,0x4,0xe,0x86);
    reset_pc(p);
    fetch_instruction(p,inst);
    print_instruction(inst);
    fetch_instruction(p,inst);
    print_instruction(inst);
    fetch_instruction(p,inst);
    print_instruction(inst);
    fetch_instruction(p,inst);
    print_instruction(inst);
    fetch_instruction(p,inst);
    print_instruction(inst);
    fetch_instruction(p,inst);
    print_instruction(inst);
    return SUCCESS;
}