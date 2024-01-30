#include "6502.h"

#include "instruction.h"
#include <string.h>

void em6502_reset(central_processing_unit *cpu) {
    cpu->A = RESET_VALUE_A;
    cpu->B = RESET_VALUE_B;
    cpu->C = RESET_VALUE_C;
    cpu->D = RESET_VALUE_D;
    cpu->I = RESET_VALUE_I;
    cpu->N = RESET_VALUE_N;
    cpu->V = RESET_VALUE_V;
    cpu->Z = RESET_VALUE_Z;

    //Byte LSB = mem_fetch(RESET_VECTOR_LSB);
    //Byte MSB = mem_fetch(RESET_VECTOR_MSB);

    //cpu->PC = (MSB << 8) | LSB;
    cpu->PC = 0xFFFC;
    // cpu->PC = 0x03F6;
    cpu->SP = STACK_START;

    cpu->X = 0;
    cpu->Y = 0;

    // memset(cpu->memory, 0, sizeof(cpu->memory));
}

void em6502_destroy(central_processing_unit *cpu) {}

Byte em6502_execute_instruction(void) {
    return instruction_execute();
}

int em6502_execute(central_processing_unit *cpu, int cycles) {
    int runCycles = 0, temp = 0;

    while (cycles > 0) {

        uint8_t cyc = instruction_execute();

        runCycles += cyc;
        cycles -= cyc;
    }

    return runCycles;
}
