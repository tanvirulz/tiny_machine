#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "registers.h"
#include "memory.h"

#define LS_4_BITS 0x0F
#define OPTIONAL_WORD_NEEDED 0x80
#define REG_ID_SIZE 4
#define PROGRAM_COUNTER_START 0X010

struct Processor{
    struct Registers * r;
    struct Memory * m;
};

/**
 * explain the optional second instruction word
 * and the division of the first word
 * */

struct Instruction{
    uint8_t op_code;
    uint8_t reg1_id;
    uint8_t reg2_id;
    uint16_t op_ival; 
};

struct Processor * init_processor();


void fetch_instruction (struct Processor * P, struct Instruction * ins);

void load_instruction (struct Processor * P, uint8_t op_code, uint8_t r1_id, uint8_t r2_id, uint16_t op_ival);

void reset_pc(struct Processor * p);

void print_instruction(struct Instruction * ins );

#endif /*PROCESSOR_H*/