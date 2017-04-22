#include <stdbool.h>

#include "lc3ksim.h"
#include "instructions.h"

#define KILLONFAIL(s) do { if(failflag) { printf("%s\n", s); return 1; }  } while(0);

int main()
{
  bool failflag = false;
  lc3machine_t m;
  m.pc = 0;

  /*
   * ADDI TESTS
   */

  /* ADDI r0, r0, 0 */
  m.memory[0] = INSTRUCTION_ADDI;
  (m.registers)[0] = 0;
  LI_SET_DR(m.memory[0], 0);
  
  lc3k_step(&m);

  /* Make sure PC=1 and r0=0 */
  failflag = failflag || m.pc != 1 || m.registers[0] != 0;

  KILLONFAIL("ADDI r0 = r0 + 0 fail.");
  
  /* ADDI r0, r0, 1 */
  m.memory[1] = INSTRUCTION_ADDI;
  LI_SET_DR(m.memory[1], 0);
  LI_SET_IMM(m.memory[1], 1);
  lc3k_step(&m);

  /* Assert PC=2, r0=1*/
  failflag = failflag || m.pc != 2 || m.registers[0] != 1;
  KILLONFAIL("ADDI r0 = r0 + 1 fail.");

  
  /* 
   * NOT tests
   */
  
  m.memory[2] = lc3k_mk_not(0, 0);
  m.registers[0] = 0;
  lc3k_step(&m);
  uint16_t expectedr0 = ~0;

  printf("%d %d\n", expectedr0, m.registers[0]);
  failflag = failflag || expectedr0 != m.registers[0];
  KILLONFAIL("NOT failure.");

  /*
   * JMP test
   */

  m.memory[3] = lc3k_mk_jmp(1);
  m.registers[1] = 5;
  lc3k_step(&m);
  failflag = failflag || m.pc != 5;
  KILLONFAIL("JMP failure, jmp (r1 = 5)");

  return failflag;
}
