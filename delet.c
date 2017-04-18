#include "lc3ksim.h"
#include "instructions.def"
#include <string.h>

int main()
{
     lc3machine_t m;
     m.pc = 0;
     m.memory[0] = OPCODE_TRAP;
     m.memory[0] = LI_TRAPVECTOR_PUTS | m.memory[0];

     (m.registers)[0] = 30;

     strcpy((char*)m.memory + 30, "Hello, World!\n");

     lc3k_step(&m);

     m.memory[1] = INSTRUCTION_ADDI | BIT_BUILD(1, 0);
     LI_SET_DR(m.memory[1], 3);
     lc3k_step(&m);

    
     m.memory[2] = INSTRUCTION_ADDR;
     LI_SET_DR(m.memory[2], 4);
     LI_SET_SR1(m.memory[2], 3);
     LI_SET_SR2(m.memory[2], 0);
    

     lc3k_step(&m);
     char* s = lc3k_userdebug_printregisters(&m);
     printf("%s\n", s);
}
