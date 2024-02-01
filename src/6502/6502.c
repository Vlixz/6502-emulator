#include "6502.h"

#include "instruction.h"
#include <string.h>

void em6502_reset(central_processing_unit *cpu, Word reset_vector) {
    cpu->A = RESET_VALUE_A;
    cpu->B = RESET_VALUE_B;
    cpu->C = RESET_VALUE_C;
    cpu->D = RESET_VALUE_D;
    cpu->I = RESET_VALUE_I;
    cpu->N = RESET_VALUE_N;
    cpu->V = RESET_VALUE_V;
    cpu->Z = RESET_VALUE_Z;

    cpu->PC = reset_vector;
    // cpu->PC = 0x03F6;
    // cpu->PC = 0x0400;
    
    cpu->SP = 0;

    cpu->X = 0;
    cpu->Y = 0;

    // memset(cpu->memory, 0, sizeof(cpu->memory));
}

void em6502_destroy(central_processing_unit *cpu) {}

execution_information em6502_execute_instruction(void) {
    return instruction_execute();
}

int em6502_execute(central_processing_unit *cpu, int cycles) {
    int runCycles = 0, temp = 0;

    while (cycles > 0) {

        uint8_t cyc = instruction_execute().cycles;

        runCycles += cyc;
        cycles -= cyc;
    }

    return runCycles;
}
