#include "processor.h"

struct Processor * create_processor(){
    struct Processor * p;

    p = (struct Processor *) malloc(sizeof(struct Processor));
    p->m = init_memory();
    p->r = init_registers(PROGRAM_COUNTER_START,STACK_SEGMENT_START);

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
    uint16_t * pc = P->r->reg +_pc; /*get the pointer to pc */

    ins->op_code = get_byte(P->m,*pc) ;
    (*pc)++;
    r2_id = get_byte(P->m,*pc);
    (*pc)++;
    r1_id = (r2_id >> REG_ID_SIZE )  & LS_4_BITS; /*I always mask as a rule. I know it is redundant here.*/
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

void make_instruction( struct Instruction * ins, uint8_t op_code, uint8_t r1_id, uint8_t r2_id, uint16_t op_ival ){
    ins->op_code = op_code;
    ins->op_ival = op_ival;
    ins->reg1_id = r1_id;
    ins->reg2_id = r2_id;
}

void load_instruction (struct Processor * P, struct Instruction * ins ){
    uint8_t i_bytes[4];
    uint16_t * pc;
    
    pc = P->r->reg +_pc;

    i_bytes[0] = ins->op_code;
    i_bytes[1] = ins->reg1_id;
    i_bytes[1] <<= REG_ID_SIZE;
    i_bytes[1] = i_bytes[1] | ins->reg2_id;
    i_bytes[2] = ins->op_ival & 0xFF;
    i_bytes[3] = (ins->op_ival >> 8) & 0xFF;
    
    put_byte(P->m , *pc , i_bytes[0] );
    
    (*pc)++;
    put_byte(P->m , *pc, i_bytes[1] );
    (*pc)++;
    
    if (ins->op_code & OPTIONAL_WORD_NEEDED ) {
        put_byte(P->m , *pc, i_bytes[2] );
        (*pc)++;
        put_byte(P->m , *pc, i_bytes[3] );
        (*pc)++;
    }
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

/**
 * get_reg() - returns the pointer to the 16 bit register identified by reg_id
 * */
uint16_t * get_reg(struct Processor * p, uint16_t reg_id){
    return p->r->reg + reg_id;
}

uint16_t run(struct Processor * p){
    uint16_t est;
    struct Instruction ins;
    do{
        fetch_instruction(p,&ins );
        est = execute(p,&ins );
    }while(est == OK);
    
    return est;
}


uint16_t execute(struct Processor * p, struct Instruction * ins){
    uint16_t * a;
    uint16_t * b;
    uint16_t * z;
    uint16_t * sp;

    uint16_t * dp;
    uint16_t * pc;

   
    
    z = get_reg(p,_z);
    switch(ins->op_code){
    
        case HALT:
        
        return PHALT; /* halt!!! */
        
        break;
        case ADD:
        //printf ("%d %d\n",ins->reg1_id,ins->reg2_id);
        a = get_reg(p,ins->reg1_id);
        b = get_reg(p,ins->reg2_id);
        //printf("add %d %d\n", *a,*b);
        *z = (*a + *b > 0xFFFF)?  1 : 0 ;
        (*a )+= (*b);

        break;
        case ADDI:

        a = get_reg(p,ins->reg1_id);

        *z = (*a + ins->op_ival > 0xFFFF)?  1 : 0 ;

        *a += ins->op_ival;

        break;
        case SUB:

        a = get_reg(p,ins->reg1_id);
        b = get_reg(p,ins->reg2_id);
        
        *z = *a < *b ?  1 : 0 ;
        *a -= *b;

        break;
        case SUBI:

        a = get_reg(p,ins->reg1_id);

         *z = *a < ins->op_ival ?  1 : 0 ;

        *a -= ins->op_ival;
        break;
        case LD:

        a = get_reg(p,ins->reg1_id);
        dp = get_reg(p,_dp);

        *a = get_word(p->m,*dp);

        break;
        case LDI:

        a = get_reg(p,ins->reg1_id);
        *a = get_word(p->m,ins->op_ival);

        break;
        case MOV:

        a = get_reg(p,ins->reg1_id);
        b = get_reg(p,ins->reg2_id);
        *a = *b;

        break;
        case JMP:

        pc = get_reg(p,_pc);
        *pc = ins->op_ival;

        break;
        case JZ:

        a = get_reg(p,ins->reg1_id);
        
        if(*a==0){
            pc = get_reg(p,_pc);
            *pc = ins->op_ival;
        
        }

        break;
        case JNZ:

        a = get_reg(p,ins->reg1_id);
        
        if(*a!=0){
            pc = get_reg(p,_pc);
            *pc = ins->op_ival;
        
        }
        
        break;
        case SET:

        a = get_reg(p,ins->reg1_id);
        *a = ins->op_ival;
        
        break;
        case PUT:
        a = get_reg(p,ins->reg1_id);
        dp = get_reg(p,_dp);
        put_word(p->m,*dp,*a);

        break;
        case PUTI:
        a = get_reg(p,ins->reg1_id);
        put_word(p->m,ins->op_ival,*a);
        
        break;
        case CMP:
        a = get_reg(p,ins->reg1_id);
        b = get_reg(p,ins->reg2_id);
        *z = *a < *b ?  1 : 0 ;
        
        break;
        case MOD:
        a = get_reg(p,ins->reg1_id);
        b = get_reg(p,ins->reg2_id);
        *a %= *b;
        
        break;
        case PUSH:
        a = get_reg(p,ins->reg1_id);
        sp = get_reg(p,_sp);
        if (*sp == STACK_SEGMENT_END) {
            return STACK_OVERFLOW;
        }
        put_word(p->m,*sp,*a);
        (*sp) +=2;

        break;
        case POP:
        a = get_reg(p,ins->reg1_id);
        sp = get_reg(p,_sp);
        if (*sp == STACK_SEGMENT_START) {
            return STACK_UNDERFLOW;

        }
        *a = get_word(p->m,*sp);
        (*sp) -=2;





        /*adding mul,div should be easy*/

    }
    return OK;
}