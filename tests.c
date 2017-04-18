#include <stdbool.h>

#include "lc3ksim.h"
#include "instructions.def"

int main()
{
  bool failflag = false;
  lc3machine_t m;
  m.pc = 0;

  /*
   * ADDI TESTS
   */

  /* ADDI r0, r0, 0 */
  m.memory[1] = INSTRUCTION_ADDI;
  (m.registers)[0] = 0;
  LI_SET_DR(m.memory[1], 0);
  
  lc3k_step(&m);

  failflag = failflag || m.pc != 1 || m.registers[0] != 0;

  return failflag;
}
