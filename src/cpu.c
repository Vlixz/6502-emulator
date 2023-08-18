#include "cpu.h"

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

// =======================================
//            Addressing Modes
// =======================================

inline Byte AddressingMode_Immediate(const Byte *memory, Word *PC)
{
    return memory[(*PC)++];
}

inline Byte AddressingMode_ZeroPage(const Byte *memory, Word *PC)
{
    Byte zeroPageAddress = memory[(*PC)++];

    return memory[zeroPageAddress];
}

inline Byte AddressingMode_ZeroPageX(const Byte *memory, Word *PC, const Byte X)
{
    Byte ZeroPageMemoryLocation = X + memory[(*PC)++];

    return memory[ZeroPageMemoryLocation];
}

inline Byte AddressingMode_ZeroPageY(const Byte *memory, Word *PC, const Byte Y)
{
    fprintf(stderr, "Addressing mode Zero Page Y not implemented yet.");

    exit(EXIT_FAILURE);
}

inline void AddressingMode_Relative(const Byte *memory, Word *PC)
{
    fprintf(stderr, "Addressing mode Relative not implemented yet.");

    exit(EXIT_FAILURE);
}

inline Byte AddressingMode_Absolute(const Byte *memory, Word *PC)
{
    Byte LSB = memory[(*PC)++];
    Byte MSB = memory[(*PC)++];

    Word address = (Word)LSB | MSB << 8;

    return memory[address];
}

inline Byte AddressingMode_AbsoluteX(const Byte *memory, Word *PC, const Byte X, int *cycles)
{
    Byte LSB = memory[(*PC)++];
    Byte MSB = memory[(*PC)++];

    (*cycles) = (Byte)(LSB + X) < X; // The addition wraped around +1 cycle.

    Word address = (Word)LSB | MSB << 8;

    address += X;

    return memory[address];
}

inline Byte AddressingMode_AbsoluteY(const Byte *memory, Word *PC, const Byte Y, int *cycles)
{
    Byte LSB = memory[(*PC)++];
    Byte MSB = memory[(*PC)++];

    (*cycles) = (Byte)(LSB + Y) < Y; // The addition wraped around +1 cycle.

    Word address = (Word)LSB | MSB << 8;

    address += Y;

    return memory[address];
}

inline Byte AddressingMode_Indirect(const Byte *memory, Word *PC)
{
    fprintf(stderr, "Addressing mode Indirect not implemented yet.");

    exit(EXIT_FAILURE);
}

inline Byte AddressingMode_IndexedIndirect(const Byte *memory, Word *PC, Byte X)
{
    Byte zeroPageAddress = memory[(*PC)++];

    Byte absoluteAddress = zeroPageAddress + X;

    Byte LSB = memory[absoluteAddress];
    Byte MSB = memory[absoluteAddress + 1];

    Word address = (Word)LSB | MSB << 8;

    return memory[address];
}

inline Byte AddressingMode_IndirectIndexed(const Byte *memory, Word *PC, Byte Y, int *cycles)
{
    Byte zeroPageAddress = memory[(*PC)++];

    Byte LSB = memory[zeroPageAddress];
    Byte MSB = memory[zeroPageAddress + 1];

    Word absoluteAddress = (Word)LSB | MSB << 8;

    (*cycles) = (Byte)(LSB + Y) < Y; // The addition wraped around +1 cycle.

    Word address = absoluteAddress + Y;

    return memory[address];
}

// =======================================
//             Add with Carry
// =======================================
/**
 *
 * A,Z,C,N = A+M+C
 *
 * Adds the content of a memory location to the accumulator together with the carry bit. If a overflow
 * occurs the carry bit is set.
 *
 */
void ADC_Algorithmics(CPU_6502 *cpu, Byte O);

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
    Byte O = AddressingMode_Immediate(cpu->memory, &cpu->PC);

    ADC_Algorithmics(cpu, O);

    return ADC_IM_CYCLES;
}

Byte ADC_ZP(CPU_6502 *cpu)
{
    Byte O = AddressingMode_ZeroPage(cpu->memory, &cpu->PC);

    ADC_Algorithmics(cpu, O);

    return ADC_ZP_CYCLES;
}

Byte ADC_ZP_X(CPU_6502 *cpu)
{
    Byte O = AddressingMode_ZeroPageX(cpu->memory, &cpu->PC, cpu->X);

    ADC_Algorithmics(cpu, O);

    return ADC_ZP_X_CYCLES;
}

Byte ADC_AB(CPU_6502 *cpu)
{
    Byte O = AddressingMode_Absolute(cpu->memory, &cpu->PC);

    ADC_Algorithmics(cpu, O);

    return ADC_AB_CYCLES;
}

Byte ADC_AB_X(CPU_6502 *cpu)
{
    int cycles = 0;

    Byte O = AddressingMode_AbsoluteX(cpu->memory, &cpu->PC, cpu->X, &cycles);

    ADC_Algorithmics(cpu, O);

    return ADC_AB_X_CYCLES + cycles;
}

Byte ADC_AB_Y(CPU_6502 *cpu)
{
    int cycles = 0;

    Byte O = AddressingMode_AbsoluteY(cpu->memory, &cpu->PC, cpu->Y, &cycles);

    ADC_Algorithmics(cpu, O);

    return ADC_AB_Y_CYCLES + cycles;
}

Byte ADC_IN_X(CPU_6502 *cpu)
{
    Byte O = AddressingMode_IndexedIndirect(cpu->memory, &cpu->PC, cpu->X);

    ADC_Algorithmics(cpu, O);

    return ADC_IN_X_CYCLES;
}

Byte ADC_IN_Y(CPU_6502 *cpu)
{
    int cycles = 0;

    Byte O = AddressingMode_IndirectIndexed(cpu->memory, &cpu->PC, cpu->Y, &cycles);

    ADC_Algorithmics(cpu, O);

    return ADC_IN_Y_CYCLES + cycles;
}
