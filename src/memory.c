#include "memory.h"

/**
 * init_memory() - Allocate memory for memory bucket list and return the pointer. 
 * 
 * Each element of the returned bucket list is explicitly initialized to NULL. 
 * */

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

/**
 * put_byte() - Write the input data byte to the dp'th byte in the Memory. 
 * If any data from the associated memory bucket was not previously referenced 
 * the associated memory bucket is first allocated. 
 * 
 * @M: pointer to the Memory.
 * @dp: 16 bit address to the byte to be written. 
 * @byte: The 8 bit data byte.
 * 
 * Note: This function can only write one byte at a time to the memory. 
 * */
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

/**
 * get_byte() - Read the dp'th byte from the Memory.
 * 
 * @M: Pointer to memory
 * @dp: 16 bit address
 * 
 * If the byte is un-referenced previously and the associated memory 
 * bucket is not allocated then the bucket is allocated first and 
 * the dp'th value is returned. For previously unwritten byte 
 * the returned value will be garbage.
 * */

uint8_t get_byte(struct Memory * M, uint16_t dp){
    int bi , i ;
    uint8_t byte;
    bi = dp/MEM_BUCKET_SIZE;
    /* If specific memory bank that contains dp'th byte is not 
    previously allocated then the memory is allocated first.*/
    if  (M->mbl[bi] == NULL){
        M->mbl[bi] = (uint8_t *) malloc(MEM_BUCKET_SIZE);
    }
    i = dp - bi * MEM_BUCKET_SIZE;
    byte = M->mbl[bi][i] ;
    return byte;
}

/**
 * get_word() - Return the memory word (2 bytes) pointed by the 
 * address dp.
 * @m: pointer to Memory.
 * @dp: 16 bit address. 
 * 
 * In the returned word, the least significant 8 bits will come 
 * from dp'th byte and the most significant 8 bits will come from 
 * (dp+1)th byte. 
 * 
 * Therefore if dp points to the last byte of Memory then coll to 
 * get_word() would crash or show unknown behaviour. 
 *  
 * */
uint16_t get_word(struct Memory * m, uint16_t dp){
    uint16_t h;
    h = get_byte(m,dp);
    h = h | ( (uint16_t)get_byte(m,dp+1)<<8);
}


/**
 * put_word() - Write the 2 byte input word to memory. 
 * See the documentation for get_word() to understand the byte 
 * ordering. 
 * 
 * @m: pointer to memory.
 * @dp: 16 bit address. 
 * */

void put_word(struct Memory * m,uint16_t dp,uint16_t word){
    uint8_t i_bytes[2];
    i_bytes[0] = word & 0xFF;
    i_bytes[1] = (word >> 8) & 0xFF;
    put_byte(m , dp , i_bytes[0] );
   
    put_byte(m , dp+1, i_bytes[1] );
    
}

/**
 * free_mem() - Release all the allocated memory. 
 * @M: pointer to Memory. 
 * */
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
