#include "registers.h"

struct Registers * init_registers (){
    struct Registers * R;
    R = (struct Registers *) malloc(sizeof(struct Registers));
    return R;
}

void free_reg(struct Registers * R){
    free(R);

}