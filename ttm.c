#include <stdio.h>

#include "memory.h"
#include "registers.h"

int main(){
    struct Memory * M;
    M = init_memory();
    uint16_t dp = 0xffff;
    put_byte(M,dp,42);
    printf("%d\n",(int)M->mbl[0xff][0xff]);
    printf("%d\n",(int)get_byte(M,dp));
    //free memory for no reason
    clear_mem(M);

    
    printf("success!\n");

}