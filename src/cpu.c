#include "cpu.h"

// =======================================
//             Add with Carry
// =======================================

inline void ADC_UpdateRegisters(CPU_6502 *cpu, Byte AC, Byte CF, Byte MEM, unsigned int value)
{
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
}

Byte ADC_IM(CPU_6502 *cpu)
{
    Byte AC = cpu->AC;                 // Accumulator value
    Byte CF = cpu->CF;                 // Carry Flag
    Byte MEM = cpu->memory[cpu->PC++]; // Immediate value

    unsigned int value = AC + CF + MEM;

    cpu->AC = value;

    ADC_UpdateRegisters(cpu, AC, CF, MEM, value);

    return ADC_IM_CYCLES;
}

Byte ADC_ZP(CPU_6502 *cpu)
{
    Byte AC = cpu->AC;                              // Accumulator value
    Byte CF = cpu->CF;                              // Carry Flag
    Byte MEM = cpu->memory[cpu->memory[cpu->PC++]]; // Value at specific Zero Page address (0x0000 -> 0x00FF)

    unsigned int value = AC + CF + MEM;

    cpu->AC = value;

    ADC_UpdateRegisters(cpu, AC, CF, MEM, value);

    return ADC_ZP_CYCLES;
}

Byte ADC_ZP_X(CPU_6502 *cpu)
{
    Byte AC = cpu->AC; // Accumulator value
    Byte CF = cpu->CF; // Carry Flag

    // Calculated Zero Page location (8-bit Zero Page address + X) - this wraps around so 0xFF + 0x80 -> 0x7F
    Byte ZeroPageMemoryLocation = cpu->X + cpu->memory[cpu->PC++];

    Byte MEM = cpu->memory[ZeroPageMemoryLocation];

    unsigned int value = AC + CF + MEM;

    cpu->AC = value;

    ADC_UpdateRegisters(cpu, AC, CF, MEM, value);

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
