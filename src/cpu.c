#include "cpu.h"

// =======================================
//             Add with Carry
// =======================================

Byte ADC_IM(CPU_6502 *cpu)
{
    // Add together: CF, ACC, MEM
    Byte AC = cpu->AC; // Accumulator value
    Byte CF = cpu->CF; // Carry Flag
    Byte MEM = cpu->memory[cpu->PC++];

    unsigned int value = AC + CF + MEM;

    cpu->AC = value;

    /**
     * Process after use:
     *
     *  Carry Flag: If overflow in bit 7
     *  Zero Flag: If AC = 0
     *  Overflow Flag: If sign bit is incorrect
     *  Negative Flag: If bit 7 set
     *
     */

    cpu->CF = value >> 8;
    cpu->ZF = !cpu->AC * 1;
    cpu->NF = cpu->AC >> 7;

    // If Negative + Negative = Positive || Positive + Positive = Negative | Set Overflow Flag

    if (AC >> 7 && MEM >> 7) // Both 1 (so both numbers negative)
    {
        cpu->OF = !(cpu->AC >> 7); // If sign bit is zero then calculation overflowed
    }

    if (!(AC >> 7) && !(MEM >> 7)) // Both 0 (so both number positive)
    {
        cpu->OF = (cpu->AC >> 7); // If sign bit is one then calculation overflowed
    }

    return ADC_IM_CYCLES;
}

Byte ADC_ZP(CPU_6502 *cpu)
{
    return ADC_ZP_CYCLES;
}

Byte ADC_ZP_X(CPU_6502 *cpu)
{
    return ADC_ZP_X_CYCLES;
}

Byte ADC_AB(CPU_6502 *cpu)
{
    return ADC_AB_CYCLES;
}

Byte ADC_AB_X(CPU_6502 *cpu)
{
    return ADC_AB_X_CYCLES;
}

Byte ADC_AB_Y(CPU_6502 *cpu)
{
    return ADC_AB_Y_CYCLES;
}

Byte ADC_IN_X(CPU_6502 *cpu)
{
    return ADC_IN_X_CYCLES;
}

Byte ADC_IN_Y(CPU_6502 *cpu)
{
    return ADC_IN_Y_CYCLES;
}
