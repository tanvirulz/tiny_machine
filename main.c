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
  
    printf("\n\n\n");
    #ifdef TEST_MODE
        if(run_test_suit()) {
            printf("Test Suit completed!\n");
        }
    #endif

    printf("pc survived!!\n");

}