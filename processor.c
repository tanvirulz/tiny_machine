#include "processor.h"

struct Processor * init_processor(){
    struct Processor * p;

    p = (struct Processor *) malloc(sizeof(struct Processor));
    p->m = init_memory();
    p->r = init_registers(PROGRAM_COUNTER_START);

    return p;
}

/**
 * fetch_instruction() - fetch the current instruction with the optional word
 * increment the pc by 2 if no optional word is needed
 * increment the pc by 4 if optional word is also fetched
 * this decision is made by observing the opcode.
 * @P : is the processor instance
 * @pc : is the pointer to the programm counter register
 * @ins : is the pointer to a instruction container where the instruction is 
 * to be loaded. 
 * 
 * By default aftr fetching pc points to the next instruction to be fetche. 
 * pc can later be changed during execution of the jump or jz instructions.
 * 
 * */

void fetch_instruction (struct Processor * P, struct Instruction * ins){
    uint8_t r1_id=0;
    uint8_t r2_id=0;
    uint16_t * pc = & (P->r->pc); /*get the pointer to pc */

    ins->op_code = get_byte(P->m,*pc) ;
    (*pc)++;
    r2_id = get_byte(P->m,*pc);
    (*pc)++;
    r1_id = (r1_id >> REG_ID_SIZE )  & LS_4_BITS; /*I always mask as a rule. I know it is redundant here.*/
    r2_id = r2_id & LS_4_BITS ;
    ins->reg1_id = r1_id;
    ins->reg2_id = r2_id;
    if (ins->op_code & OPTIONAL_WORD_NEEDED) {
        ins->op_ival = get_byte(P->m,*pc) ;
        (*pc)++; 
        ins->op_ival = ins->op_ival | ((uint16_t)get_byte(P->m,*pc) << 8);
        (*pc)++; 
    }
}


void load_instruction (struct Processor * P, uint8_t op_code, uint8_t r1_id, uint8_t r2_id, uint16_t op_ival){
    uint8_t i_bytes[4];
    uint16_t * pc;
    pc = & (P->r->pc);

    i_bytes[0] = op_code;
    i_bytes[1] = r1_id;
    i_bytes[1] <<= REG_ID_SIZE;
    i_bytes[1] = i_bytes[1] | r2_id;
    i_bytes[2] = op_ival & 0xFF;
    i_bytes[3] = (op_ival >> 8) & 0xFF;
    put_byte(P->m , *pc , i_bytes[0] );
    (*pc)++;
    put_byte(P->m , *pc, i_bytes[1] );
    (*pc)++;
    if (op_code & OPTIONAL_WORD_NEEDED ) {
        put_byte(P->m , *pc, i_bytes[2] );
        (*pc)++;
        put_byte(P->m , *pc, i_bytes[3] );
        (*pc)++;
    }
}

void reset_pc(struct Processor * p){
    p->r->pc = PROGRAM_COUNTER_START;
}
/**
 * test print out
 * */
void print_instruction(struct Instruction * ins ){
    printf( "op_code: %02x reg1: %0x reg2: %0x\n",ins->op_code,ins->reg1_id,ins->reg2_id);
    if ( ins ->op_code & OPTIONAL_WORD_NEEDED) {
        printf( "op_val_hex: %04x op_val_decimal: %d\n",ins->op_ival,ins->op_ival);
    }
}

