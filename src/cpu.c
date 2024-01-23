#include "cpu.h"

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

// =======================================
//            Addressing Modes
// =======================================

inline Byte AddressingMode_Immediate(const Byte *memory, Word *PC) {
    return memory[(*PC)++];
}

inline Byte AddressingMode_ZeroPage(const Byte *memory, Word *PC) {
    Byte zeroPageAddress = memory[(*PC)++];

    return memory[zeroPageAddress];
}

inline Byte AddressingMode_ZeroPageX(const Byte *memory, Word *PC,
                                     const Byte X) {
    Byte ZeroPageMemoryLocation = X + memory[(*PC)++];

    return memory[ZeroPageMemoryLocation];
}

inline Byte AddressingMode_ZeroPageY(const Byte *memory, Word *PC,
                                     const Byte Y) {
    fprintf(stderr, "Addressing mode Zero Page Y not implemented yet.");

    exit(EXIT_FAILURE);
}

inline void AddressingMode_Relative(const Byte *memory, Word *PC, int *cycles) {
    (*cycles)++; // +1 for a succeeded branching operation.

    Byte offset = memory[(*PC)++];

    Word tempPC = (*PC);

    (*PC) += offset;

    (*cycles) += (tempPC >> 8) != ((*PC) >> 8); // +1 if a page is crossed.
}

inline Byte AddressingMode_Absolute(const Byte *memory, Word *PC) {
    Byte LSB = memory[(*PC)++];
    Byte MSB = memory[(*PC)++];

    Word address = (Word)LSB | MSB << 8;

    return memory[address];
}

inline Byte AddressingMode_AbsoluteX(const Byte *memory, Word *PC, const Byte X,
                                     int *cycles) {
    Byte LSB = memory[(*PC)++];
    Byte MSB = memory[(*PC)++];

    (*cycles) = (Byte)(LSB + X) < X; // The addition wraped around +1 cycle.

    Word address = (Word)LSB | MSB << 8;

    address += X;

    return memory[address];
}

inline Byte AddressingMode_AbsoluteY(const Byte *memory, Word *PC, const Byte Y,
                                     int *cycles) {
    Byte LSB = memory[(*PC)++];
    Byte MSB = memory[(*PC)++];

    (*cycles) = (Byte)(LSB + Y) < Y; // The addition wraped around +1 cycle.

    Word address = (Word)LSB | MSB << 8;

    address += Y;

    return memory[address];
}

inline Byte AddressingMode_Indirect(const Byte *memory, Word *PC) {
    fprintf(stderr, "Addressing mode Indirect not implemented yet.");

    exit(EXIT_FAILURE);
}

inline Byte AddressingMode_IndexedIndirect(const Byte *memory, Word *PC,
                                           Byte X) {
    Byte zeroPageAddress = memory[(*PC)++];

    Byte absoluteAddress = zeroPageAddress + X;

    Byte LSB = memory[absoluteAddress];
    Byte MSB = memory[absoluteAddress + 1];

    Word address = (Word)LSB | MSB << 8;

    return memory[address];
}

inline Byte AddressingMode_IndirectIndexed(const Byte *memory, Word *PC, Byte Y,
                                           int *cycles) {
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
 * Adds the content of a memory location to the accumulator together with the
 * carry bit. If a overflow occurs the carry bit is set.
 *
 */
void ADC_Algorithmics(CPU_6502 *cpu, Byte O);

inline void ADC_Algorithmics(CPU_6502 *cpu, Byte O) {
    bool areSignBitsEqual =
        !((cpu->A & BIT_MASK_SIGNED) ^ (O & BIT_MASK_SIGNED));

    unsigned int value = cpu->A + cpu->C + O;

    cpu->A = value;

    cpu->C = (value & BIT_MASK_CARRY) > 0;
    cpu->Z = IS_ZERO(cpu->A);
    cpu->N = IS_NEGATIVE(cpu->A);

    cpu->V = areSignBitsEqual *
             ((O & BIT_MASK_SIGNED) != (cpu->A & BIT_MASK_SIGNED));
}

Byte ADC_IM(CPU_6502 *cpu) {
    Byte O = AddressingMode_Immediate(cpu->memory, &cpu->PC);

    ADC_Algorithmics(cpu, O);

    return ADC_IM_CYCLES;
}

Byte ADC_ZP(CPU_6502 *cpu) {
    Byte O = AddressingMode_ZeroPage(cpu->memory, &cpu->PC);

    ADC_Algorithmics(cpu, O);

    return ADC_ZP_CYCLES;
}

Byte ADC_ZP_X(CPU_6502 *cpu) {
    Byte O = AddressingMode_ZeroPageX(cpu->memory, &cpu->PC, cpu->X);

    ADC_Algorithmics(cpu, O);

    return ADC_ZP_X_CYCLES;
}

Byte ADC_AB(CPU_6502 *cpu) {
    Byte O = AddressingMode_Absolute(cpu->memory, &cpu->PC);

    ADC_Algorithmics(cpu, O);

    return ADC_AB_CYCLES;
}

Byte ADC_AB_X(CPU_6502 *cpu) {
    int cycles = 0;

    Byte O = AddressingMode_AbsoluteX(cpu->memory, &cpu->PC, cpu->X, &cycles);

    ADC_Algorithmics(cpu, O);

    return ADC_AB_X_CYCLES + cycles;
}

Byte ADC_AB_Y(CPU_6502 *cpu) {
    int cycles = 0;

    Byte O = AddressingMode_AbsoluteY(cpu->memory, &cpu->PC, cpu->Y, &cycles);

    ADC_Algorithmics(cpu, O);

    return ADC_AB_Y_CYCLES + cycles;
}

Byte ADC_IN_X(CPU_6502 *cpu) {
    Byte O = AddressingMode_IndexedIndirect(cpu->memory, &cpu->PC, cpu->X);

    ADC_Algorithmics(cpu, O);

    return ADC_IN_X_CYCLES;
}

Byte ADC_IN_Y(CPU_6502 *cpu) {
    int cycles = 0;

    Byte O =
        AddressingMode_IndirectIndexed(cpu->memory, &cpu->PC, cpu->Y, &cycles);

    ADC_Algorithmics(cpu, O);

    return ADC_IN_Y_CYCLES + cycles;
}

// =======================================
//             Logical AND
// =======================================

/**
 *
 * A,Z,N = A&M
 *
 * Logical AND operation on the accumulator contents using the contents of a
 * byte of memory.
 *
 */
void AND_Algorithmics(CPU_6502 *cpu, Byte O);

inline void AND_Algorithmics(CPU_6502 *cpu, Byte O) {
    cpu->A &= O;

    cpu->Z = IS_ZERO(cpu->A);
    cpu->N = IS_NEGATIVE(cpu->A);
}

Byte AND_IM(CPU_6502 *cpu) {
    Byte O = AddressingMode_Immediate(cpu->memory, &cpu->PC);

    AND_Algorithmics(cpu, O);

    return AND_IM_CYCLES;
}

Byte AND_ZP(CPU_6502 *cpu) {
    Byte O = AddressingMode_ZeroPage(cpu->memory, &cpu->PC);

    AND_Algorithmics(cpu, O);

    return AND_ZP_CYCLES;
}

Byte AND_ZP_X(CPU_6502 *cpu) {
    Byte O = AddressingMode_ZeroPageX(cpu->memory, &cpu->PC, cpu->X);

    AND_Algorithmics(cpu, O);

    return AND_ZP_X_CYCLES;
}

Byte AND_AB(CPU_6502 *cpu) {
    Byte O = AddressingMode_Absolute(cpu->memory, &cpu->PC);

    AND_Algorithmics(cpu, O);

    return AND_AB_CYCLES;
}

Byte AND_AB_X(CPU_6502 *cpu) {
    int cycles = 0;

    Byte O = AddressingMode_AbsoluteX(cpu->memory, &cpu->PC, cpu->X, &cycles);

    AND_Algorithmics(cpu, O);

    return AND_AB_X_CYCLES + cycles;
}

Byte AND_AB_Y(CPU_6502 *cpu) {
    int cycles = 0;

    Byte O = AddressingMode_AbsoluteY(cpu->memory, &cpu->PC, cpu->Y, &cycles);

    AND_Algorithmics(cpu, O);

    return AND_AB_Y_CYCLES + cycles;
}

Byte AND_IN_X(CPU_6502 *cpu) {
    int cycles = 0;

    Byte O = AddressingMode_IndexedIndirect(cpu->memory, &cpu->PC, cpu->X);

    AND_Algorithmics(cpu, O);

    return AND_IN_X_CYCLES;
}

Byte AND_IN_Y(CPU_6502 *cpu) {
    int cycles = 0;

    Byte O =
        AddressingMode_IndirectIndexed(cpu->memory, &cpu->PC, cpu->Y, &cycles);

    AND_Algorithmics(cpu, O);

    return AND_IN_Y_CYCLES + cycles;
}

// =======================================
//        Arithmatic Shift Left
// =======================================

/**
 *
 * A,Z,C,N = M*2 or M,Z,C,N = M*2
 *
 * ASL shift all the bits in the accumulator one bit to the left. Old bit 7 is
 * placed in the Carry and bit 0 is set to zero.
 *
 */
void ASL_Algorithmics(CPU_6502 *cpu, Byte O);

inline void ASL_Algorithmics(CPU_6502 *cpu, Byte O) {
    Word value = cpu->A << 1;

    cpu->A = (Byte)value;

    cpu->C = (value & 0x100) > 0;
    cpu->Z = IS_ZERO(cpu->A);

    cpu->N = IS_NEGATIVE(cpu->A);
}

Byte ASL_AC(CPU_6502 *cpu) {
    Byte O = cpu->A;

    ASL_Algorithmics(cpu, O);

    return ASL_AC_CYCLES;
}

Byte ASL_ZP(CPU_6502 *cpu) {
    Byte O = AddressingMode_ZeroPage(cpu->memory, &cpu->PC);

    ASL_Algorithmics(cpu, O);

    return ASL_ZP_CYCLES;
}

Byte ASL_ZP_X(CPU_6502 *cpu) {
    Byte O = AddressingMode_ZeroPageX(cpu->memory, &cpu->PC, cpu->X);

    ASL_Algorithmics(cpu, O);

    return ASL_ZP_X_CYCLES;
}

Byte ASL_AB(CPU_6502 *cpu) {
    Byte O = AddressingMode_Absolute(cpu->memory, &cpu->PC);

    ASL_Algorithmics(cpu, O);

    return ASL_AB_CYCLES;
}

Byte ASL_AB_X(CPU_6502 *cpu) {
    int cycles = 0;

    Byte O = AddressingMode_AbsoluteX(cpu->memory, &cpu->PC, cpu->X, &cycles);

    ASL_Algorithmics(cpu, O);

    return ASL_AB_X_CYCLES;
}

// =======================================
//         Branch if Carry Clear
// =======================================

Byte BCC_RE(CPU_6502 *cpu) {
    int cycles = 0;

    if (!cpu->C) // TODO: Try to code this without using a if statement
        AddressingMode_Relative(cpu->memory, &cpu->PC, &cycles);
    else
        /**
         * We need to increment by one because we didn't run the fist cycle
         * which is getting the increment.
         *
         *      +1 getting the increment.
         *
         */
        cpu->PC++;

    return BCC_RE_CYCLES + cycles;
}

// =======================================
//          Branch if Carry Set
// =======================================

Byte BCS_RE(CPU_6502 *cpu) {
    int cycles = 0;

    if (cpu->C) // TODO: Try to code this without using a if statement
        AddressingMode_Relative(cpu->memory, &cpu->PC, &cycles);
    else
        /**
         * We need to increment by one because we didn't run the fist cycle
         * which is getting the increment.
         *
         *      +1 getting the increment.
         *
         */
        cpu->PC++;

    return BCS_RE_CYCLES + cycles;
}

// =======================================
//           Branch if Equal
// =======================================

Byte BEQ_RE(CPU_6502 *cpu) {
    int cycles = 0;

    if (cpu->Z) // TODO: Try to code this without using a if statement
        AddressingMode_Relative(cpu->memory, &cpu->PC, &cycles);
    else
        /**
         * We need to increment by one because we didn't run the fist cycle
         * which is getting the increment.
         *
         *      +1 getting the increment.
         *
         */
        cpu->PC++;

    return BEQ_RE_CYCLES + cycles;
}

// =======================================
//              Bit Tests
// =======================================

/**
 * A & M, N = M7, V = M6
 *
 * The mask pattern in A is AND-ed with the value in memory to set of clear the
 * zero flag. Bit 7 and 6 of the value from memory are copied into the N and V
 * flags.
 *
 */
void BIT_Functionality(CPU_6502 *cpu, Byte O);

inline void BIT_Functionality(CPU_6502 *cpu, Byte O) {
    Byte result = cpu->A & O; // Result is not kept.

    cpu->N = IS_NEGATIVE(O);
    cpu->V = (O & 0b01000000) > 0;

    cpu->Z = IS_ZERO(result);
}

Byte BIT_ZP(CPU_6502 *cpu) {
    Byte O = AddressingMode_ZeroPage(cpu->memory, &cpu->PC);

    BIT_Functionality(cpu, O);

    return BIT_ZP_CYCLES;
}

Byte BIT_AB(CPU_6502 *cpu) {
    Byte O = AddressingMode_Absolute(cpu->memory, &cpu->PC);

    BIT_Functionality(cpu, O);

    return BIT_AB_CYCLES;
}

// =======================================
//            Branch if Minus
// =======================================

Byte BMI_RE(CPU_6502 *cpu) {
    int cycles = 0;

    if (cpu->N) // TODO: Try to code this without using a if statement
        AddressingMode_Relative(cpu->memory, &cpu->PC, &cycles);
    else
        /**
         * We need to increment by one because we didn't run the fist cycle
         * which is getting the increment.
         *
         *      +1 getting the increment.
         *
         */
        cpu->PC++;

    return BMI_RE_CYCLES + cycles;
}

// =======================================
//            Branch if Not Equal
// =======================================

Byte BNE_RE(CPU_6502 *cpu) {
    int cycles = 0;

    if (!cpu->Z) // TODO: Try to code this without using a if statement
        AddressingMode_Relative(cpu->memory, &cpu->PC, &cycles);
    else
        /**
         * We need to increment by one because we didn't run the fist cycle
         * which is getting the increment.
         *
         *      +1 getting the increment.
         *
         */
        cpu->PC++;

    return BNE_RE_CYCLES + cycles;
}

// =======================================
//            Branch if Positive
// =======================================

Byte BPL_RE(CPU_6502 *cpu) {
    int cycles = 0;

    if (!cpu->N) // TODO: Try to code this without using a if statement
        AddressingMode_Relative(cpu->memory, &cpu->PC, &cycles);
    else
        /**
         * We need to increment by one because we didn't run the fist cycle
         * which is getting the increment.
         *
         *      +1 getting the increment.
         *
         */
        cpu->PC++;

    return BNE_RE_CYCLES + cycles;
}

// =======================================
//       Branch if Overflow Clear
// =======================================

Byte BVC_RE(CPU_6502 *cpu) {
    int cycles = 0;

    if (!cpu->V)
        AddressingMode_Relative(cpu->memory, &cpu->PC, &cycles);
    else
        /**
         * We need to increment by one because we didn't run the fist cycle
         * which is getting the increment.
         *
         *      +1 getting the increment.
         *
         */
        cpu->PC++;

    return BVC_RE_CYCLES + cycles;
}

// =======================================
//       Branch if Overflow Set
// =======================================

Byte BVS_RE(CPU_6502 *cpu) {
    int cycles = 0;

    if (cpu->V)
        AddressingMode_Relative(cpu->memory, &cpu->PC, &cycles);
    else
        /**
         * We need to increment by one because we didn't run the fist cycle
         * which is getting the increment.
         *
         *      +1 getting the increment.
         *
         */
        cpu->PC++;

    return BVS_RE_CYCLES + cycles;
}

// =======================================
//            Clear Carry Flag
// =======================================

inline Byte CLC_IP(CPU_6502 *cpu) {
    cpu->C = 0;

    return CLC_IP_CYCLES;
}

// =======================================
//          Clear Decimal Mode
// =======================================

inline Byte CLD_IP(CPU_6502 *cpu) {
    cpu->D = 0;

    return CLD_IP_CYCLES;
}

// =======================================
//        Clear Interrupt Disable
// =======================================

inline Byte CLI_IP(CPU_6502 *cpu) {
    cpu->I = 0;

    return CLI_IP_CYCLES;
}

// =======================================
//          Clear Overflow Flag
// =======================================

inline Byte CLV_IP(CPU_6502 *cpu) {
    cpu->V = 0;

    return CLV_IP_CYCLES;
}

// =======================================
//            Set Carry Flag
// =======================================

inline Byte SEC_IP(CPU_6502 *cpu) {
    cpu->C = 1;

    return SEC_IP_CYCLES;
}

// =======================================
//           Set Decimal Mode
// =======================================

inline Byte SED_IP(CPU_6502 *cpu) {
    cpu->D = 1;

    printf("SED: (Decimal mode not supported currently) \n");

    // exit(EXIT_FAILURE);

    return SED_IP_CYCLES;
}

// =======================================
//           Set Interrupt Disable
// =======================================

inline Byte SEI_IP(CPU_6502 *cpu) {
    cpu->I = 1;

    return SEI_IP_CYCLES;
}

// =======================================
//       Transfer Accumulator to X
// =======================================

Byte TAX_IP(CPU_6502 *cpu) {
    cpu->X = cpu->A;

    cpu->Z = IS_ZERO(cpu->X);
    cpu->N = IS_NEGATIVE(cpu->X);

    return TAX_IP_CYCLES;
}

// =======================================
//       Transfer Accumulator to Y
// =======================================

Byte TAY_IP(CPU_6502 *cpu) {
    cpu->Y = cpu->A;

    cpu->Z = IS_ZERO(cpu->Y);
    cpu->N = IS_NEGATIVE(cpu->Y);

    return TAX_IP_CYCLES;
}

// =======================================
//       Transfer X to Accumulator
// =======================================

Byte TXA_IP(CPU_6502 *cpu) {
    cpu->A = cpu->X;

    cpu->Z = IS_ZERO(cpu->A);
    cpu->N = IS_NEGATIVE(cpu->A);

    return TXA_IP_CYCLES;
}

// =======================================
//       Transfer Y to Accumulator
// =======================================

Byte TYA_IP(CPU_6502 *cpu) {
    cpu->A = cpu->Y;

    cpu->Z = IS_ZERO(cpu->A);
    cpu->N = IS_NEGATIVE(cpu->A);

    return TYA_IP_CYCLES;
}

// =======================================
//            Load Accumulator
// =======================================

/**
 *
 * A,Z,N = M
 *
 * Loads a byte of memory into the accumulator setting the zero and negative
 * flags as appropriate.
 *
 */
void LDA_Logics(CPU_6502 *cpu, Byte O);

inline void LDA_Logics(CPU_6502 *cpu, Byte O) {
    cpu->A = O;

    cpu->Z = IS_ZERO(cpu->A);
    cpu->N = IS_NEGATIVE(cpu->A);
}

Byte LDA_IM(CPU_6502 *cpu) {
    Byte O = AddressingMode_Immediate(cpu->memory, &cpu->PC);

    LDA_Logics(cpu, O);

    return LDA_IM_CYCLES;
}

Byte LDA_ZP(CPU_6502 *cpu) {
    Byte O = AddressingMode_ZeroPage(cpu->memory, &cpu->PC);

    LDA_Logics(cpu, O);

    return LDA_ZP_CYCLES;
}

Byte LDA_ZP_X(CPU_6502 *cpu) {
    Byte O = AddressingMode_ZeroPageX(cpu->memory, &cpu->PC, cpu->X);

    LDA_Logics(cpu, O);

    return LDA_ZP_X_CYCLES;
}

Byte LDA_AB(CPU_6502 *cpu) {
    Byte O = AddressingMode_Absolute(cpu->memory, &cpu->PC);

    LDA_Logics(cpu, O);

    return LDA_AB_CYCLES;
}

Byte LDA_AB_X(CPU_6502 *cpu) {
    int cycles = 0;

    Byte O = AddressingMode_AbsoluteX(cpu->memory, &cpu->PC, cpu->X, &cycles);

    LDA_Logics(cpu, O);

    return LDA_AB_X_CYCLES + cycles;
}

Byte LDA_AB_Y(CPU_6502 *cpu) {
    int cycles = 0;

    Byte O = AddressingMode_AbsoluteY(cpu->memory, &cpu->PC, cpu->Y, &cycles);

    LDA_Logics(cpu, O);

    return LDA_AB_Y_CYCLES + cycles;
}

Byte LDA_IN_X(CPU_6502 *cpu) {
    Byte O = AddressingMode_IndexedIndirect(cpu->memory, &cpu->PC, cpu->X);

    LDA_Logics(cpu, O);

    return LDA_IN_X_CYCLES;
}

Byte LDA_IN_Y(CPU_6502 *cpu) {
    int cycles = 0;

    Byte O =
        AddressingMode_IndirectIndexed(cpu->memory, &cpu->PC, cpu->Y, &cycles);

    LDA_Logics(cpu, O);

    return LDA_IN_Y_CYCLES + cycles;
}

// =======================================
//            No Operation
// =======================================

inline Byte NOP_IP(CPU_6502 *cpu) { return NOP_IP_CYCLES; }

// =======================================
//            Decrement X
// =======================================

Byte DEX_IP(CPU_6502 *cpu) {

    cpu->X--;

    cpu->Z = IS_ZERO(cpu->X);
    cpu->N = IS_NEGATIVE(cpu->X);

    return DEX_IP_CYCLES;
}

// =======================================
//            Decrement Y
// =======================================

Byte DEY_IP(CPU_6502 *cpu) {

    cpu->Y--;

    cpu->Z = IS_ZERO(cpu->Y);
    cpu->N = IS_NEGATIVE(cpu->Y);

    return DEY_IP_CYCLES;
}

// =======================================
//            Load X Register
// =======================================

void LDX_Logics(CPU_6502 *cpu, Byte O);

inline void LDX_Logics(CPU_6502 *cpu, Byte O) {
    cpu->X = O;
    cpu->Z = IS_ZERO(cpu->X);
    cpu->N = IS_NEGATIVE(cpu->X);
}

Byte LDX_IM(CPU_6502 *cpu) {
    Byte O = AddressingMode_Immediate(cpu->memory, &cpu->PC);

    LDX_Logics(cpu, O);

    return LDX_IM_CYCLES;
}

Byte LDX_ZP(CPU_6502 *cpu) {
    Byte O = AddressingMode_ZeroPage(cpu->memory, &cpu->PC);

    LDX_Logics(cpu, O);

    return LDX_ZP_CYCLES;
}

Byte LDX_ZP_Y(CPU_6502 *cpu) {
    Byte O = AddressingMode_ZeroPageY(cpu->memory, &cpu->PC, cpu->Y);

    LDX_Logics(cpu, O);

    return LDX_ZP_Y_CYCLES;
}

Byte LDX_AB(CPU_6502 *cpu) {
    Byte O = AddressingMode_Absolute(cpu->memory, &cpu->PC);

    LDX_Logics(cpu, O);

    return LDX_AB_CYCLES;
}

Byte LDX_AB_Y(CPU_6502 *cpu) {
    int cycles = 0;

    Byte O = AddressingMode_AbsoluteY(cpu->memory, &cpu->PC, cpu->Y, &cycles);

    LDX_Logics(cpu, O);

    return LDX_AB_Y_CYCLES + cycles;
}
