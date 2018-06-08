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

/*51200 BYTES this leaves 56*256 bytes for the stack*/

#define STACK_SEGMENT_START 0XC800
#define STACK_SEGMENT_END 0XFFFF

enum opcodes {
    HALT = 0x00,
    ADD = 0x01,
    ADDI = 0x81,
    SUB = 0x02,
    SUBI = 0x82,
    LD = 0x03,
    LDI = 0x83,
    MOV = 0x04,
    JMP = 0x85, 
    JZ = 0x86,
    JNZ = 0x8A,
    SET = 0x87,
    PUT = 0x08,
    PUTI = 0x88,
    CMP = 0x09,
    MOD = 0x0B,
    PUSH = 0x0C,
    POP = 0x0D
    /*push pop todo*/
};

enum exe_status {
    OK = 0x00,
    STACK_OVERFLOW = 0x01,
    STACK_UNDERFLOW = 0x02,
    PHALT = 0xFF
};

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



void print_instruction(struct Instruction * ins );

uint16_t execute(struct Processor * p, struct Instruction * ins);

#endif /*PROCESSOR_H*/