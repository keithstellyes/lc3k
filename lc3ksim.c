/*
 * lc3ksim.c
 */

#include "lc3ksim.h"

/*
 * Returns if two instructions have the same opcode
 */
bool lc3k_sameopcode(uint16_t a, uint16_t b)
{
    a = a & BIT_BUILD(4, 15, 14, 13, 12);
    b = b & BIT_BUILD(4, 15, 14, 13, 12);
    return a == b;
}

int* lc3k_not(lc3machine_t* m)
{
  uint16_t inst = (m->memory)[m->pc];
  uint16_t dr = LI_GET_DR(inst);
  uint16_t sr = LI_GET_SR1(inst);

  (m->registers)[dr] = ~((m->registers)[sr]);

  return NULL;
}

/*
 * Returns a value based on what has happened with the step.
 * Returns a negative status on error.
 * 0 on success, no I/O, no halt.
 * -1 INVALID OPCODE
 */
int lc3k_step(lc3machine_t* m)
{
    uint16_t pc = m->pc;
    uint16_t inst = (m->memory)[pc];
    
     if(LI_GETTRAPVECTOR((inst) == LI_TRAPVECTOR_PUTS)) {
       //printf("PUTS!\n");
       lc3k_puts(m);
      } else if(lc3k_sameopcode(inst, OPCODE_ADD)) {
       lc3k_add(m);
     } else if(lc3k_sameopcode(inst, OPCODE_NOT)) {
       lc3k_not(m);
     } else if(lc3k_sameopcode(inst, OPCODE_JMP)) {
       lc3k_jmp(m);
     }

     /*
      * Use an array of function pointers instead of if or switch
      * (lc3machine_t*) ops[1 << 4] { NOP, ADD, LD, ST, ... TRAP }
      * ops[LI_GETOPCODE](m);
      */
    m->pc = m->pc + 1;
    return 0;
}

/*
 * Error status/success status/other misc info
 * Typically returns NULL
 */
int* lc3k_puts(lc3machine_t* m)
{
  uint16_t addr = (m->registers)[0];
  uint16_t *mem = m->memory;

  printf("%s", (char*)mem + addr);
  return NULL;
}

int16_t lc3k_addi_getval(uint16_t i)
{
  int16_t t = i & BIT_BUILD(5, 0, 1, 2, 3, 4);
  if(t & BIT_BUILD(1, 4)) {
    t = t | BIT_BUILD(11, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5);
    t = ~t;
    t += 1;
    t = t * -1;

  }

  return t;
}

int* lc3k_add(lc3machine_t* m)
{
  uint16_t inst = (m->memory)[m->pc];

  uint16_t dr = LI_GET_DR(inst);
  int sr = LI_GET_SR1(inst); 

  int16_t x, y;
  
  if(LI_IS_ADDI(inst)) {
    x = lc3k_addi_getval(inst);
  } else {
    int sr2 = LI_GET_SR2(inst);
    x = (m->registers)[sr2];
    printf("dr:%d = sr1:%d + sr2:%d\n", dr, sr, sr2);
  }
  y = (m->registers)[sr];

  printf("x=%d y=%d dr=%d\n", x, y, dr);
  
  (m->registers)[dr] = x + y;

  return NULL;
}

int* lc3k_and(lc3machine_t* m)
{
  uint16_t inst = (m->memory)[m->pc];

  uint16_t dr = LI_GET_DR(inst);
  uint16_t sr = LI_GET_SR1(inst);

  uint16_t x, y;

  if(LI_IS_ANDI(inst)) {
    x = lc3k_andigetval(inst);
  } else {
    uint16_t sr2 = LI_GET_SR2(inst);
    x = (m->registers)[sr];
  }
  y = (m->registers)[dr] = x & y;

  return NULL;
}

int* lc3k_jmp(lc3machine_t* m)
{
  uint16_t inst = (m->memory)[m->pc];
  m->pc = (m->registers)[LI_GET_SR1(inst)] - 1;

  return NULL;
}

char* lc3k_userdebug_printregisters(lc3machine_t* m)
{
  char* s = (char*)malloc(sizeof(char) * 100);
  char* formatstr = "r0:%04x r1:%04x r2:%04x r3:%04x\n"
                    "r4:%04x r5:%04x r6:%04x r7:%04x\n"
                    "pc:%04x";
  
  snprintf(s, 100, formatstr, m->registers[0], m->registers[1],
	   m->registers[2], m->registers[3], m->registers[4],
	   m->registers[5], m->registers[6], m->registers[7],
	   m->pc);

  return s;
}

uint16_t lc3k_mk_not(uint16_t sr, uint16_t dr)
{
  uint16_t inst = INSTRUCTION_NOT;

  LI_SET_DR(inst, dr);
  LI_SET_SR1(inst, sr);
  
  return inst;
}

uint16_t lc3k_mk_jmp(uint16_t base_reg)
{
  uint16_t inst = INSTRUCTION_JMP;
  LI_SET_BR(inst, base_reg);
  return inst;
}

uint16_t lc3k_mk_ret()
{
  return INSTRUCTION_RET;
}
