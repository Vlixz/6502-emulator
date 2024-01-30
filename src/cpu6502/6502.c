#include "6502.h"

#include "instruction.h"
#include <string.h>

void em6502_reset(CPU_6502 *cpu) {
    cpu->A = ACCUMULATOR_RESET_VALUE;
    cpu->B = BREAK_COMMAND_RESET_VALUE;
    cpu->C = CARRY_FLAG_RESET_VALUE;
    cpu->D = DECIMAL_MODE_RESET_VALUE;
    cpu->I = INTERRUPT_DISABLE_RESET_VALUE;
    cpu->N = NEGATIVE_FLAG_RESET_VALUE;
    cpu->V = OVERFLOW_FLAG_RESET_VALUE;
    cpu->Z = ZERO_FLAG_RESET_VALUE;

    //Byte LSB = mem_fetch(RESET_VECTOR_LSB);
    //Byte MSB = mem_fetch(RESET_VECTOR_MSB);

    //cpu->PC = (MSB << 8) | LSB;
    cpu->PC = 0xFFFC;
    // cpu->PC = 0x03F6;
    cpu->SP = START_OF_STACK;

    cpu->X = 0;
    cpu->Y = 0;

    // memset(cpu->memory, 0, sizeof(cpu->memory));
}

void em6502_destroy(CPU_6502 *cpu) {}

Byte em6502_execute_instruction(void) {
    return ins_execute();
}

int em6502_execute(CPU_6502 *cpu, int cycles) {
    int runCycles = 0, temp = 0;

    while (cycles > 0) {

        uint8_t cyc = ins_execute();

        runCycles += cyc;
        cycles -= cyc;
    }

    return runCycles;
}
