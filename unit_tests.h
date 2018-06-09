#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "processor.h"
#include "registers.h"
#include "memory.h"

#define PASS 1
#define FAIL 0


int load_ins_from_array(struct Processor *p, uint16_t * ins_list);

int run_test_suit();

#endif /*UNIT_TESTS_H*/