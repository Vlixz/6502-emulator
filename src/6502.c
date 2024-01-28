#include "6502.h"

#include "instruction.h"
#include "stdlib.h"
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

    cpu->PC = 0xFFFC;
    cpu->SP = START_OF_STACK;

    cpu->X = 0;
    cpu->Y = 0;

    memset(cpu->memory, 0, sizeof(cpu->memory));
    // cpu->memory = (Byte *)calloc(MEMORY_WORD_COUNT_6502, sizeof(Byte));
}

void em6502_destroy(CPU_6502 *cpu) {}

int em6502_execute(CPU_6502 *cpu, int cycles) {
    int runCycles = 0, temp = 0;

    while (cycles > 0) {

        uint8_t cyc = ins_execute();

        runCycles += cyc;
        cycles -= cyc;
    }

    return runCycles;
}
