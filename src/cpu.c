#include "cpu.h"

#include "stdbool.h"

// =======================================
//             Add with Carry
// =======================================

inline void ADC_Algorithmics(CPU_6502 *cpu, Byte O)
{
    bool areSignBitsEqual = !((cpu->A & BIT_MASK_SIGNED) ^ (O & BIT_MASK_SIGNED));

    unsigned int value = cpu->A + cpu->C + O;

    cpu->A = value;

    cpu->C = (value & BIT_MASK_CARRY) > 0;
    cpu->Z = cpu->A <= 0;
    cpu->N = (cpu->A & BIT_MASK_SIGNED) > 0;

    cpu->V = areSignBitsEqual * ((O & BIT_MASK_SIGNED) != (cpu->A & BIT_MASK_SIGNED));
}

Byte ADC_IM(CPU_6502 *cpu)
{
    Byte O = cpu->memory[cpu->PC++];

    ADC_Algorithmics(cpu, O);

    return ADC_IM_CYCLES;
}

Byte ADC_ZP(CPU_6502 *cpu)
{
    Byte O = cpu->memory[cpu->memory[cpu->PC++]];

    ADC_Algorithmics(cpu, O);

    return ADC_ZP_CYCLES;
}

Byte ADC_ZP_X(CPU_6502 *cpu)
{
    // Calculated Zero Page location (8-bit Zero Page address + X) - this wraps around so 0xFF + 0x80 -> 0x7F
    Byte ZeroPageMemoryLocation = cpu->X + cpu->memory[cpu->PC++];

    Byte O = cpu->memory[ZeroPageMemoryLocation];

    ADC_Algorithmics(cpu, O);

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
