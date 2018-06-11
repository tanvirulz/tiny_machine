#ifndef MEMORY_H
#define MEMORY_H 

#include <stdlib.h>
#include <stdint.h>

/**
 * Number of memory bucket that the system supports
*/
#define NUM_MEM_BUCKETS 256

/**
 * Size of each memory bucket in bytes. 
 * */
#define MEM_BUCKET_SIZE 256

/**
 * struct Memory - contains a list of pointer to *used* memory blocks.
 * 
 * @mbl: Pointer to an array of size NUM_MEM_BUCKETS. Each element of 
 * the array points to a used memory bucket (block). If a memory bucket
 * is never referenced from the code it will not be allocated
 * This is to make sure that we don't allocate a large quantity of memory
 * to run the virtual machine. 
 * 
 *  
 * */
struct Memory{
    uint8_t * mbl [NUM_MEM_BUCKETS];
};


/* Consult the associated source file (.c) for detailed documentation */
struct Memory * init_memory();
void put_byte(struct Memory * M, uint16_t dp, uint8_t byte);
uint8_t get_byte(struct Memory * M, uint16_t dp);
void free_mem(struct Memory * M);    
uint16_t get_word(struct Memory * m,uint16_t dp);
void put_word(struct Memory * m,uint16_t dp,uint16_t word);

#endif /*MEMORY_H*/