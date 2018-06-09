#include "unit_tests.h"

#define MAX_TEST_INS_COUNT 512

char * exe_status_translator[]= {"OK","STACK_OVERFLOW","STACK_UNDERFLOW","PHALT"};

char * test_status[]= {"FAIL","PASS"};


uint16_t ins_set_1[] = {
    SET, _a, 2,
    SET, _b, 5,
    ADD, _a, _b,
    MOV, _c, _a,
    HALT, _DM,_DM 

};



void make_test_instruction(struct Instruction * ins, uint16_t a,uint16_t b, uint16_t c ){
    //printf ("ins: %d,%d,%d\n",a,b,c);
    if (a & OPTIONAL_WORD_NEEDED){
        make_instruction(ins, a,b,_DM,c );
    }
    else{
        make_instruction(ins, a,b,c,_DM);
    }

}

int load_ins_from_array(struct Processor *p, uint16_t * ins_list){
    struct Instruction  ins;
    int i = 0;
    printf("Loading instruction from array\n");
    do{
        make_test_instruction(&ins,ins_list[i],ins_list[i+1],ins_list[i+2]);
        
        load_instruction(p,&ins);  
        
        i += 3;
    }while (ins_list[i-3]!= HALT); 
    printf("Loading DONE\n");
    printf("resetting programm counter\n");
    reset_pc(p->r,PROGRAM_COUNTER_START);
    printf("load_from_arry_complete\n");
}

    





int test1(struct Processor *p){
    int est;
    int tst;
    time_t btime, etime;
    double runtime;

    printf ("Test suit 1 started:\n");
    time(&btime);
    load_ins_from_array(p,ins_set_1);
    est = run(p);

    /*check validity*/
    if (p->r->reg[_c]==7) {
        tst = PASS;
    }
    else{
        tst = FAIL;
    }

    time(&etime);
    printf ("Test suit 1 ended:\n");
    runtime = difftime(etime,btime);
    
    printf( "Execution status: %s,\t\t Test 1 status: %s \nRuntime: %f\n",exe_status_translator[est],
                        test_status[tst], runtime);
}

int run_test_suit(){
    struct Processor *p; 
    p = create_processor();

    test1( p);
    //struct Instruction * inst = (struct Instruction *) malloc(sizeof(struct Instruction));
    
}