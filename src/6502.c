#include "6502.h"

#include "stdlib.h"

void em6502_reset(CPU_6502 *cpu)
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

void em6502_destroy(CPU_6502 *cpu)
{
    free(cpu->memory);
}

int em6502_execute(CPU_6502 *cpu, int cycles)
{
    int runCycles = 0, temp = 0;

    while (cycles > 0)
    {

        Word opcode = cpu->memory[cpu->PC++];

        switch (opcode)
        {

            /**
             * Add with Carry
             *
             */

        case ADC_IM_OPCODE:

            temp = ADC_IM(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ADC_ZP_OPCODE:

            temp = ADC_ZP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ADC_ZP_X_OPCODE:

            temp = ADC_ZP_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ADC_AB_OPCODE:

            temp = ADC_AB(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ADC_AB_X_OPCODE:

            temp = ADC_AB_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ADC_AB_Y_OPCODE:

            temp = ADC_AB_Y(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ADC_IN_X_OPCODE:

            temp = ADC_IN_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ADC_IN_Y_OPCODE:

            temp = ADC_IN_Y(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Logical AND
             *
             */

        case AND_IM_OPCODE:

            temp = AND_IM(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case AND_ZP_OPCODE:

            temp = AND_ZP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case AND_ZP_X_OPCODE:

            temp = AND_ZP_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case AND_AB_OPCODE:

            temp = AND_AB(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case AND_AB_X_OPCODE:

            temp = AND_AB_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case AND_AB_Y_OPCODE:

            temp = AND_AB_Y(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case AND_IN_X_OPCODE:

            temp = AND_IN_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case AND_IN_Y_OPCODE:

            temp = AND_IN_Y(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Arithmatic Shift Left
             *
             */

        case ASL_AC_OPCODE:

            temp = ASL_AC(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ASL_ZP_OPCODE:

            temp = ASL_ZP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ASL_ZP_X_OPCODE:

            temp = ASL_ZP_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ASL_AB_OPCODE:

            temp = ASL_AB(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ASL_AB_X_OPCODE:

            temp = ASL_AB_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        default:
            break;
        }
    }

    return runCycles;
}