#include "memory.h"

struct Memory * init_memory(){
    struct Memory * M;
    int i;
    M = (struct Memory *) malloc(sizeof(struct Memory ));
    for (i = 0;i<NUM_MEM_BUCKETS;i++){
        M->mbl[i] = NULL;
    }
    //printf("%d\n",(int)sizeof(M->mbl));
    return M;
}

void put_byte(struct Memory * M, uint16_t dp, uint8_t byte){
    int bi , i ;
    bi = dp/MEM_BUCKET_SIZE;
    
    /* If specific memory bank that contains dp'th byte is not allocated
    then the memory is allocated first.*/
    if  (M->mbl[bi] == NULL){
        M->mbl[bi] = (uint8_t *) malloc(MEM_BUCKET_SIZE);
    }
    
    i = dp - bi * MEM_BUCKET_SIZE; //compute memory bank offset
    M->mbl[bi][i] = byte;
}

uint8_t get_byte(struct Memory * M, uint16_t dp){
    int bi , i ;
    uint8_t byte;
    bi = dp/MEM_BUCKET_SIZE;
    if  (M->mbl[bi] == NULL){
        M->mbl[bi] = (uint8_t *) malloc(MEM_BUCKET_SIZE);
    }
    i = dp - bi * MEM_BUCKET_SIZE;
    byte = M->mbl[bi][i] ;
    return byte;
}

uint16_t get_word(struct Memory * m, uint16_t dp){
    uint16_t h;
    h = get_byte(m,dp);
    h = h | ( (uint16_t)get_byte(m,dp+1)<<8);
}
void put_word(struct Memory * m,uint16_t dp,uint16_t word){
    uint8_t i_bytes[2];
    i_bytes[0] = word & 0xFF;
    i_bytes[1] = (word >> 8) & 0xFF;
    put_byte(m , dp , i_bytes[0] );
   
    put_byte(m , dp+1, i_bytes[1] );
    
}
void free_mem(struct Memory * M){
    int i;
    for (i=0;i<NUM_MEM_BUCKETS;i++){
        if (M->mbl[i]){
            free(M->mbl[i]);
            M->mbl[i] = NULL;
        } 
    }
    free(M);
}
