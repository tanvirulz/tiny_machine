#include "debug.h"

void debug(char *s){

    #ifdef DEBUG_MODE
        printf("\t\t"ANSI_COLOR_YELLOW"%s"ANSI_COLOR_RESET"\n",s);
    #endif

}