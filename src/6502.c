#include "6502.h"

#include "stdlib.h"

void reset_6502(CPU_6502 *cpu)
{
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

    cpu->memory = (Byte *)calloc(MEMORY_WORD_COUNT_6502, sizeof(Byte));
}

void destroy_6502(CPU_6502 *cpu)
{
    free(cpu->memory);
}

void execute_6502(CPU_6502 *cpu, int cycles)
{
    while (cycles > 0)
    {

        Word opcode = cpu->memory[cpu->PC++];

        switch (opcode)
        {

            /**
             * Add with Carry
             *
             * This instruction adds the contents of a memory location to the accumulator together with the carry bit.
             * If overflow occurs the carry bit is set, this enables multiple byte addition to be performed.
             */

        case ADC_IM_OPCODE:

            cycles -= ADC_IM(cpu);

            break;

        case ADC_ZP_OPCODE:

            cycles -= ADC_ZP(cpu);

            break;

        case ADC_ZP_X_OPCODE:

            cycles -= ADC_ZP_X(cpu);

            break;

        case ADC_AB_OPCODE:

            cycles -= ADC_AB(cpu);

            break;

        case ADC_AB_X_OPCODE:

            cycles -= ADC_AB_X(cpu);

            break;

        case ADC_AB_Y_OPCODE:

            cycles -= ADC_AB_Y(cpu);

            break;

        case ADC_IN_X_OPCODE:

            cycles -= ADC_IN_X(cpu);

            break;

        case ADC_IN_Y_OPCODE:

            cycles -= ADC_IN_Y(cpu);

            break;

        default:
            break;
        }
    }
}