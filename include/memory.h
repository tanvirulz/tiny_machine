#ifndef MEMORY_H
#define MEMORY_H 

#include <stdlib.h>
#include <stdint.h>

#define NUM_MEM_BUCKETS 256
#define MEM_BUCKET_SIZE 256
struct Memory{
    uint8_t * mbl [NUM_MEM_BUCKETS];
};

struct Memory * init_memory();

/**
 * put_byte() - copy a byte to a specific locaiton in the memory 
 * @M: pointer to the memory
 * @dp: memory address
 * @byte: byte to be stored
 * 
 * This function can only wirite one byte at a time to the memory. 
 * 
 */
void put_byte(struct Memory * M, uint16_t dp, uint8_t byte);
uint8_t get_byte(struct Memory * M, uint16_t dp);
void free_mem(struct Memory * M);    
uint16_t get_word(struct Memory * m,uint16_t dp);
void put_word(struct Memory * m,uint16_t dp,uint16_t word);
#endif /*MEMORY_H*/