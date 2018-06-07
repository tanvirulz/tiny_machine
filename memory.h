#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define NUM_MEM_BUCKETS 256
#define MEM_BUCKET_SIZE 256
struct Memory{
    uint8_t * mbl [NUM_MEM_BUCKETS];

};

struct Memory * init_memory();
void put_byte(struct Memory * M, uint16_t dp, uint8_t byte);
uint8_t get_byte(struct Memory * M, uint16_t dp);
void free_mem(struct Memory * M);    
