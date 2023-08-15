#include "6502.h"

#include "stdlib.h"

void reset(void)
{

    cpu.AC = 0;
    cpu.BC = 0;
    cpu.CF = 0;
    cpu.DM = 0;
    cpu.ID = 0;
    cpu.NF = 0;
    cpu.OF = 0;
    cpu.PC = 0;
    cpu.SP = 0;
    cpu.ZF = 0;
    cpu.X = 0;
    cpu.Y = 0;

    cpu.memory = (Word *)calloc(MEMORY_WORD_COUNT_6502, sizeof(Word));
}

void execute(int cycles)
{
    while (cycles > 0)
    {

        Word opcode = cpu.memory[BASE_STACK + cpu.SP];

        switch (opcode)
        {
        case OPCODE_ADC_IM:

            cycles -= ADC_IM(cpu);

            break;

        case OPCODE_ADC_ZP:

            cycles -= ADC_ZP(cpu);

            break;

        case OPCODE_ADC_ZP_X:

            cycles -= ADC_ZP_X(cpu);

            break;

        case OPCODE_ADC_AB:

            cycles -= ADC_AB(cpu);

            break;

        case OPCODE_ADC_AB_X:

            cycles -= ADC_AB_X(cpu);

            break;

        case OPCODE_ADC_AB_Y:

            cycles -= ADC_AB_Y(cpu);

            break;

        case OPCODE_ADC_IN_X:

            cycles -= ADC_IN_X(cpu);

            break;

        case OPCODE_ADC_IN_Y:

            cycles -= ADC_IN_Y(cpu);

            break;

        default:
            break;
        }
    }
}