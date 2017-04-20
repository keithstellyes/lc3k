/* PAGE 525 */

#ifndef INSTRUCTIONS_D
#define INSTRUCTIONS_D

#include <stdint.h>
#include <stdarg.h>

#ifndef INSTRUCTIONS_DBB
#define INSTRUCTIONS_DBB
/* TODO: translate BIT_BUILD into a macro */
uint16_t BIT_BUILD(int count,...)
{
  va_list ap;
  va_start(ap, count);

  uint16_t ONE16 = 1;
  uint16_t result = 0;

  int i;
  for(i = 0; i < count; i++) {
    result = result | (ONE16 << va_arg(ap, int));
  }

  return result;
}
#endif

/*
 * Retreives the condition codes for an LC3 machine
 */
#define GETCC_N(_m_) ((_m_->psr) & BIT_BUILD(1, 11))
#define GETCC_Z(_m_) ((_m_->psr) & BIT_BUILD(1, 10))
#define GETCC_P(_m_) ((_m_->psr) & BIT_BUILD(1, 9))

#define OPCODE_ADD  BIT_BUILD(1, 12)
#define OPCODE_AND  BIT_BUILD(2, 14, 12)
#define OPCODE_BR   0
#define OPCODE_JMP  BIT_BUILD(2, 15, 14)
#define OPCODE_JSR  BIT_BUILD(1, 14)
#define OPCODE_JSRR OPCODE_JSR
#define OPCODE_LD   BIT_BUILD(1, 13)
#define OPCODE_LDI  BIT_BUILD(2, 15, 14)
#define OPCODE_LDR  BIT_BUILD(2, 14, 14)
#define OPCODE_LEA  BIT_BUILD(3, 15, 14, 13)
#define OPCODE_NOT  BIT_BUILD(2, 15, 12)
#define OPCODE_RET  BIT_BUILD(2, 15, 14)
#define OPCODE_RTI  BIT_BUILD(1, 15)
#define OPCODE_ST   BIT_BUILD(2, 13, 12)
#define OPCODE_STI  BIT_BUILD(3, 15, 14, 12)
#define OPCODE_STR  BIT_BUILD(3, 14, 13, 12)
#define OPCODE_TRAP BIT_BUILD(4, 15, 14, 13, 12)
#define OPCODE_RESERVED BIT_BUILD(3, 15, 14, 12)

#define INSTRUCTION_ADDR OPCODE_ADD
#define INSTRUCTION_ADDI (INSTRUCTION_ADDR | BIT_BUILD(1, 5))
#define INSTRUCTION_ANDR OPCODE_AND
#define INSTRUCTION_ANDI (INSTRUCTION_ANDR | BIT_BUILD(1, 5))
#define INSTRUCTION_BRN  (OPCODE_BR | BIT_BUILD(1, 11))
#define INSTRUCTION_BRZ  (OPCODE_BR | BIT_BUILD(1, 10))
#define INSTRUCTION_BRP  (OPCODE_BR | BIT_BUILD(1,  9))
#define INSTRUCTION_JMP  OPCODE_JMP
#define INSTRUCTION_JSR  (OPCODE_JSR | BIT_BUILD(1, 11))
#define INSTRUCTION_JSRR OPCODE_JSRR 
#define INSTRUCTION_LD   OPCODE_LD
#define INSTRUCTION_LDR  OPCODE_LDR
#define INSTRUCTION_LEA  OPCODE_LEA
#define INSTRUCTION_NOT  (OPCODE_NOT | BIT_BUILD(6, 5, 4, 3, 2, 1, 0))
#define INSTRUCTION_RET  (OPCODE_RET | BIT_BUILD(3, 8, 7, 6))
#define INSTRUCTION_RTI  OPCODE_RTI
#define INSTRUCTION_ST   OPCODE_ST
#define INSTRUCTION_STR  OPCODE_STR
#define INSTRUCTION_TRAP OPCODE_TRAP
#define INSTRUCTION_RESERVED OPCODE_RESERVED

/*
 * Gets a given word's options
 */
#define LI_GET_DR(i)  ((i & BIT_BUILD(3, 11, 10, 9)) >> 9)
#define LI_GET_SR1(i) ((i & BIT_BUILD(3, 8, 7, 6)) >> 6)
#define LI_GET_SR2(i) (i & BIT_BUILD(3, 0, 1, 2))

/*
 * Sets a given word's options 
 */
#define LI_SET_DR(i, n)  do { i = i | n << 9; } while(0);
#define LI_SET_SR1(i, n) do { i = i | n << 6; } while(0);
#define LI_SET_SR2(i, n) do { i = i | n; } while(0);
#define LI_SET_IMM(i, n) do { if(i >= 0) i = i | n; \
  else {					    \
    int M = (~n) - 1;				    \
    M = M & BIT_BUILD(5, 0, 1, 2, 3, 4);	    \
    i = i | M;}} while(0);

#define LI_GETTRAPVECTOR(i) (i & BIT_BUILD(8, 0, 1, 2, 3, 4, 5, 6, 7))
#define LI_TRAPVECTOR_PUTS BIT_BUILD(2, 1, 5) //0x22
#define LI_TRAPPUTS (INSTRUCTION_TRAP | LI_TRAPVECTOR_PUTS)

/*
 * 1: immediate
 * 0: register
 */
#define LI_GET_REGMODE(i) (i & BIT_BUILD(1, 5))

/*
 * Assumes i is an ADD instruction.
 */
#define LI_IS_ADDI(i) LI_GET_REGMODE(i)

/*
 * Assumes i is an ADD instruction
 */
#define LI_IS_ANDI(i) LI_GET_REGMODE(i)

#define lc3k_andigetval(i) (i & BIT_BUILD(5, 0, 1, 2, 3, 4))

#endif /* INSTRUCTIONS_D */
