/**
 * File: memory.h
 *
 * The Memory module for the tiny virtual machine. 
 *
 * Copyright (C) 2018 Tanvirul Islam
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

/**
 * Some properties of the Memory module.
 *      * The memory is byte addressable.
 *      * The address space is 16 bits. 
 *      * Maximum memory size fo tiny_machine is 2^16 bytes. 
 *      * The Memory is divided into 256 memory blocks called 
 *          memory buckets. 
 *      * Each memory bucket size is of 256 bytes. 
 *      * During operations a memory bucket is allocated only
 *          if it is needed. 
 * */
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