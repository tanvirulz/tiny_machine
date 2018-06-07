#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NUM_MEM_BUCKETS 256
#define MEM_BUCKET_SIZE 256
struct Memory{
    uint8_t * mbl [NUM_MEM_BUCKETS];

};

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
    if  (M->mbl[bi] == NULL){
        M->mbl[bi] = (uint8_t *) malloc(MEM_BUCKET_SIZE);
    }
    i = dp - bi * MEM_BUCKET_SIZE;
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


int main(){
    struct Memory * M;
    M = init_memory();
    uint16_t dp = 0xffff;
    put_byte(M,dp,42);
    printf("%d\n",(int)M->mbl[0xff][0xff]);
    printf("%d\n",(int)get_byte(M,dp));
    printf("success!\n");

}