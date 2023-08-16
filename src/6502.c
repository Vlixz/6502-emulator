#include "6502.h"

#include "stdlib.h"

void reset_6502(CPU_6502 *cpu)
{
    cpu->AC = 0;
    cpu->BC = 0;
    cpu->CF = 0;
    cpu->DM = 0;
    cpu->ID = 0;
    cpu->NF = 0;
    cpu->OF = 0;
    cpu->PC = 0xFFFC;
    cpu->SP = START_OF_STACK;
    cpu->ZF = 0;
    cpu->X = 0;
    cpu->Y = 0;

    cpu->memory = (Word *)calloc(MEMORY_WORD_COUNT_6502, sizeof(Word));
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