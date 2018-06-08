#include "unit_tests.h"



int test_processor(){
    struct Processor *p;
    p = init_processor();
    struct Instruction inst;

    load_instruction(p,0x23,0x3,0xf,0x8086);
    

}