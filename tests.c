#include <stdbool.h>

#include "lc3ksim.h"
#include "instructions.h"

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

  /* ADDI r0, r0, 1 */
  m.memory[1] = INSTRUCTION_ADDI;
  LI_SET_DR(m.memory[1], 0);
  LI_SET_IMM(m.memory[1], 1);
  lc3k_step(&m);

  /* Assert PC=2, r0=1*/
  failflag = failflag || m.pc != 2 || m.registers[0] != 1;

  return failflag;
}
