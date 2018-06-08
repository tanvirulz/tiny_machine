#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
#include "registers.h"
#include "processor.h"
int main(){
    struct Memory * m;
    struct Registers * r;
    uint16_t * n; 
    uint8_t * t;

    t = (uint8_t *) malloc(sizeof(uint8_t)*2);
    
    
    t[2] = 0xAB;
    t[1] = 0xCD;
    t[0] = 0xEF;

    printf("%x %x\n",(int)t[1],(int)t[0]);
    n = (uint16_t *) (t); 
    printf("%x ",(int)*n);
    m = init_memory();
    r = init_registers(16);
    uint16_t dp = 0xffff;
    put_byte(m,dp,42);
    printf("%d\n", (int)m->mbl[0xff][0xff]);
    printf("%d\n", (int)get_byte(m,dp));
    //free memory for no reason
    free_mem(m);
    free_reg(r);

    
    printf("success!\n");

}