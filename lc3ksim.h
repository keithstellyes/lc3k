/*
 * lc3ksim.h
 */

#ifndef LC3KSIM_H
#define LC3KSIM_H

#include "instructions.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct lc3machine_t {
    uint16_t registers[8];
    uint16_t pc;
    uint16_t memory[1<<16];
    uint16_t psr;
} lc3machine_t;

int* lc3k_puts(lc3machine_t* m);
char* lc3k_userdebug_printregisters(lc3machine_t* m);
bool lc3k_sameopcode(uint16_t a, uint16_t b);
int lc3k_step(lc3machine_t* m);
int16_t lc3k_addi_getval(uint16_t i);
int* lc3k_add(lc3machine_t* m);
int* lc3k_and(lc3machine_t* m);
int* lc3k_not(lc3machine_t* m);
int* lc3k_jmp(lc3machine_t* m);
char* lc3k_userdebug_printregisters(lc3machine_t* m);


#endif /* LC3KSIM_H */
