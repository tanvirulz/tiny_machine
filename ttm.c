#include <stdio.h>

#include "memory.h"
#include "registers.h"

int main(){
    struct Memory * m;
    struct Registers * r;
    m = init_memory();
    r = init_registers();
    uint16_t dp = 0xffff;
    put_byte(m,dp,42);
    printf("%d\n", (int)m->mbl[0xff][0xff]);
    printf("%d\n", (int)get_byte(m,dp));
    //free memory for no reason
    free_mem(m);
    free_reg(r);

    printf("success!\n");

}