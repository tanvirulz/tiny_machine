#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
#include "registers.h"
#include "processor.h"

#define CASE2 2
#ifdef TEST_MODE
    #include "unit_tests.h"
#endif

int main(){
    struct Memory * m;
    struct Registers * r;
    uint16_t * n; 
    uint8_t * t;
    int i = 2; 
    uint16_t a,b,c;
    a = 5;
    b = 2;
    c = b - a;
    t = (uint8_t *) malloc(sizeof(uint8_t)*2);
    
    
    t[2] = 0xAB;
    t[1] = 0xCD;
    t[0] = 0xEF;

    printf("%x %x\n",(int)t[1],(int)t[0]);
    n = (uint16_t *) (t); 
    printf("%x ",(int)*n);
    m = init_memory();
    r = init_registers(16,67);
    uint16_t dp = 0xffff;
    put_byte(m,dp,42);
    printf("%d\n", (int)m->mbl[0xff][0xff]);
    printf("%d\n", (int)get_byte(m,dp));
    //free memory for no reason
    free_mem(m);
    free_reg(r);
    #ifdef TEST_MODE
        if(test_processor()) {
            printf("Unit test success!\n");
        }
    #endif

    switch(i){
        case 1:
        printf("case 1\n");
        break;
        case CASE2:
        printf("case 2\n");
        break;
    }

    printf("%u\d",c);

    printf("success!\n");

}