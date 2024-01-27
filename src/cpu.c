#include "cpu.h"

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

instruction matrix[16][16] = {
/*                   0x0                     0x1                     0x2                     0x3                     0x4                     0x5                     0x6                     0x7                     0x8                     0x9                     0xA                     0xB                     0xC                     0xD                     0xE                     0xF                    */
/* 0x0 */ { {"BRK", &BRK, &IMP, 7}, {"ORA", &ORA, &IIX, 6}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"ORA", &ORA, &ZP0, 3}, {"ASL", &ASL, &ZP0, 5}, {"???", &XXX, &IMP, 1}, {"PHP", &PHP, &IMP, 3}, {"ORA", &ORA, &IMM, 2}, {"ASL", &ASL, &ACC, 2}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"ORA", &ORA, &AB0, 4}, {"ASL", &ASL, &AB0, 6}, {"???", &XXX, &IMP, 1}}, /* 0x0 */
/* 0x1 */ { {"BPL", &BPL, &REL, 2}, {"ORA", &ORA, &IIY, 5}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"ORA", &ORA, &ZPX, 4}, {"ASL", &ASL, &ZPX, 6}, {"???", &XXX, &IMP, 1}, {"CLC", &CLC, &IMP, 2}, {"ORA", &ORA, &ABY, 4}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"ORA", &ORA, &ABX, 4}, {"ASL", &ASL, &ABX, 7}, {"???", &XXX, &IMP, 1}}, /* 0x1 */
/* 0x2 */ { {"JSR", &JSR, &AB0, 6}, {"AND", &AND, &IIX, 6}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"BIT", &BIT, &ZP0, 3}, {"AND", &AND, &ZP0, 3}, {"ROL", &ROL, &ZP0, 5}, {"???", &XXX, &IMP, 1}, {"PLP", &PLP, &IMP, 4}, {"AND", &AND, &IMM, 2}, {"ROL", &ROL, &ACC, 2}, {"???", &XXX, &IMP, 1}, {"BIT", &BIT, &AB0, 4}, {"AND", &AND, &AB0, 4}, {"ROL", &ROL, &AB0, 6}, {"???", &XXX, &IMP, 1}}, /* 0x2 */
/* 0x3 */ { {"BMI", &BMI, &REL, 2}, {"AND", &AND, &IIY, 5}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"AND", &AND, &ZPX, 4}, {"ROL", &ROL, &ZPX, 6}, {"???", &XXX, &IMP, 1}, {"SEC", &SEC, &IMP, 2}, {"AND", &AND, &ABY, 4}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"AND", &AND, &ABX, 4}, {"ROL", &ROL, &ABX, 7}, {"???", &XXX, &IMP, 1}}, /* 0x3 */
/* 0x4 */ { {"RTI", &RTI, &IMP, 6}, {"EOR", &EOR, &IIX, 6}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"EOR", &EOR, &ZP0, 3}, {"LSR", &LSR, &ZP0, 5}, {"???", &XXX, &IMP, 1}, {"PHA", &PHA, &IMP, 3}, {"EOR", &EOR, &IMM, 2}, {"LSR", &LSR, &ACC, 2}, {"???", &XXX, &IMP, 1}, {"JMP", &JMP, &AB0, 3}, {"EOR", &EOR, &AB0, 4}, {"LSR", &LSR, &AB0, 6}, {"???", &XXX, &IMP, 1}}, /* 0x4 */
/* 0x5 */ { {"BVC", &BVC, &REL, 2}, {"EOR", &EOR, &IIY, 5}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"EOR", &EOR, &ZPX, 4}, {"LSR", &LSR, &ZPX, 6}, {"???", &XXX, &IMP, 1}, {"CLI", &CLI, &IMP, 2}, {"EOR", &EOR, &ABY, 4}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"EOR", &EOR, &ABX, 4}, {"LSR", &LSR, &ABX, 7}, {"???", &XXX, &IMP, 1}}, /* 0x5 */
/* 0x6 */ { {"RTS", &RTS, &IMP, 6}, {"ADC", &ADC, &IIX, 6}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"ADC", &ADC, &ZP0, 3}, {"ROR", &ROR, &ZP0, 5}, {"???", &XXX, &IMP, 1}, {"PLA", &PLA, &IMP, 4}, {"ADC", &ADC, &IMM, 2}, {"ROR", &ROR, &ACC, 2}, {"???", &XXX, &IMP, 1}, {"JMP", &JMP, &IND, 4}, {"ADC", &ADC, &AB0, 4}, {"ROR", &ROR, &AB0, 6}, {"???", &XXX, &IMP, 1}}, /* 0x6 */
/* 0x7 */ { {"BVS", &BVS, &REL, 2}, {"ADC", &ADC, &IIY, 5}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"ADC", &ADC, &ZPX, 4}, {"ROR", &ROR, &ZPX, 6}, {"???", &XXX, &IMP, 1}, {"SEI", &SEI, &IMP, 2}, {"ADC", &ADC, &ABY, 4}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"ADC", &ADC, &ABX, 4}, {"ROR", &ROR, &ABX, 7}, {"???", &XXX, &IMP, 1}}, /* 0x7 */
/* 0x8 */ { {"???", &XXX, &IMP, 0}, {"STA", &STA, &IIX, 6}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"STY", &STY, &ZP0, 3}, {"STA", &STA, &ZP0, 3}, {"STX", &STX, &ZP0, 3}, {"???", &XXX, &IMP, 1}, {"DEY", &DEY, &IMP, 2}, {"???", &XXX, &IMP, 1}, {"TXA", &TXA, &IMP, 2}, {"???", &XXX, &IMP, 1}, {"STY", &STY, &AB0, 4}, {"STA", &STA, &AB0, 4}, {"STX", &STX, &AB0, 4}, {"???", &XXX, &IMP, 1}}, /* 0x8 */
/* 0x9 */ { {"BCC", &BCC, &REL, 2}, {"STA", &STA, &IIY, 6}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"STY", &STY, &ZPX, 4}, {"STA", &STA, &ZPX, 4}, {"STX", &STX, &ZPY, 4}, {"???", &XXX, &IMP, 1}, {"TYA", &TYA, &IMP, 2}, {"STA", &STA, &ABY, 5}, {"TXS", &TXS, &IMP, 2}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"STA", &STA, &ABX, 5}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}}, /* 0x9 */
/* 0xA */ { {"LDY", &LDY, &IMM, 2}, {"LDA", &LDA, &IIX, 6}, {"LDX", &LDX, &IMM, 2}, {"???", &XXX, &IMP, 1}, {"LDY", &LDY, &ZP0, 3}, {"LDA", &LDA, &ZP0, 3}, {"LDX", &LDX, &ZP0, 3}, {"???", &XXX, &IMP, 1}, {"TAY", &TAY, &IMP, 2}, {"LDA", &LDA, &IMM, 2}, {"TAX", &TAX, &IMP, 2}, {"???", &XXX, &IMP, 1}, {"LDY", &LDY, &AB0, 4}, {"LDA", &LDA, &AB0, 4}, {"LDX", &LDX, &AB0, 4}, {"???", &XXX, &IMP, 1}}, /* 0xA */
/* 0xB */ { {"BCS", &BCS, &REL, 2}, {"LDA", &LDA, &IIY, 5}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"LDY", &LDY, &ZPX, 4}, {"LDA", &LDA, &ZPX, 4}, {"LDX", &LDX, &ZPX, 4}, {"???", &XXX, &IMP, 1}, {"CLV", &CLV, &IMP, 2}, {"LDA", &LDA, &ABY, 4}, {"TSX", &TSX, &IMP, 2}, {"???", &XXX, &IMP, 1}, {"LDY", &LDY, &ABX, 4}, {"LDA", &LDA, &ABX, 4}, {"LDX", &LDX, &ABY, 4}, {"???", &XXX, &IMP, 1}}, /* 0xB */
/* 0xC */ { {"CPY", &CPY, &IMM, 2}, {"CMP", &CMP, &IIX, 6}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"CPY", &CPY, &ZP0, 3}, {"CMP", &CMP, &ZP0, 3}, {"DEC", &DEC, &ZP0, 5}, {"???", &XXX, &IMP, 1}, {"INY", &INY, &IMP, 2}, {"CMP", &CMP, &IMM, 2}, {"DEX", &DEX, &IMP, 2}, {"???", &XXX, &IMP, 1}, {"CPY", &CPY, &AB0, 4}, {"CMP", &CMP, &AB0, 4}, {"DEC", &DEC, &AB0, 6}, {"???", &XXX, &IMP, 1}}, /* 0xC */
/* 0xD */ { {"BNE", &BNE, &REL, 2}, {"CMP", &CMP, &IIY, 5}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"CMP", &CMP, &ZPX, 4}, {"DEC", &DEC, &ZPX, 6}, {"???", &XXX, &IMP, 1}, {"CLD", &CLD, &IMP, 2}, {"CMP", &CMP, &ABY, 4}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"CMP", &CMP, &ABX, 4}, {"DEC", &DEC, &ABX, 7}, {"???", &XXX, &IMP, 1}}, /* 0xD */
/* 0xE */ { {"CPX", &CPX, &IMM, 2}, {"SBC", &SBC, &IIX, 6}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"CPX", &CPX, &ZP0, 3}, {"SBC", &SBC, &ZP0, 3}, {"INC", &INC, &ZP0, 5}, {"???", &XXX, &IMP, 1}, {"INX", &INX, &IMP, 2}, {"SBC", &SBC, &IMM, 2}, {"NOP", &NOP, &IMP, 2}, {"???", &XXX, &IMP, 1}, {"CPX", &CPX, &AB0, 4}, {"SBC", &SBC, &AB0, 4}, {"INC", &INC, &AB0, 6}, {"???", &XXX, &IMP, 1}}, /* 0xE */
/* 0xF */ { {"BEQ", &BEQ, &REL, 2}, {"SBC", &SBC, &IIY, 5}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"SBC", &SBC, &ZPX, 4}, {"INC", &INC, &ZPX, 6}, {"???", &XXX, &IMP, 1}, {"SED", &SED, &IMP, 2}, {"SBC", &SBC, &ABY, 4}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"???", &XXX, &IMP, 1}, {"SBC", &SBC, &ABX, 4}, {"INC", &INC, &ABX, 7}, {"???", &XXX, &IMP, 1}}, /* 0xF */
};

Byte ADC() {
return 0;
}
Byte AND() {
return 0;
}
Byte ASL(){
return 0;
}
Byte BCC() {
return 0;
}
Byte BCS() {
return 0;
}
Byte BEQ() {
return 0;
}
Byte BIT() {
return 0;
}
Byte BMI() {
return 0;
}
Byte BNE() {
return 0;
}
Byte BPL() {
 return 0;
}
Byte BRK() {
return 0;
}
Byte BVC() {
 return 0;
}
Byte BVS() {
 return 0;
}
Byte CLC(){
return 0;
}

Byte CLD() {
return 0;
}
Byte CLI() {
return 0;
}
Byte CLV() {
return 0;
}
Byte CMP() {
return 0;
}
Byte CPX() {
return 0;
}
Byte CPY() {
return 0;
}
Byte DEC() {
return 0;
}
Byte DEX() {
return 0;
}
Byte DEY() {
return 0;
}
Byte EOR(){
return 0;
}
Byte INC() {
return 0;
}
Byte INX() {
return 0;
}
Byte INY() {
return 0;
}
Byte JMP() {
return 0;
}

Byte JSR() {
return 0;
}
Byte LDA() {
return 0;
}
Byte LDX() {
return 0;
}
Byte LDY() {
return 0;
}
Byte LSR() {
 return 0;
}
Byte NOP() {
return 0; 
}
Byte ORA() {
return 0;
}
Byte PHA() {
return 0;
}
Byte PHP() {
return 0;
}
Byte PLA(){
return 0;
}
Byte PLP() {
return 0;
}
Byte ROL() {
return 0;
}
Byte ROR(){
return 0;
}
Byte RTI(){
return 0;
}

Byte RTS() {
return 0;
}
Byte SBC() {
return 0;
}
Byte SEC() {
return 0;
}
Byte SED() {
return 0;
}
Byte SEI() {
return 0;
}
Byte STA() {
return 0;
}
Byte STX(){
return 0; 
}
Byte STY() {
return 0;
}
Byte TAX(){
return 0;
}
Byte TAY() {
return 0;
}
Byte TSX(){
return 0;
}
Byte TXA(){
return 0;
}
Byte TXS() {
return 0;
}
Byte TYA(){
return 0;
}

Byte XXX(){
return 0;
}


Byte IMP(){
return 0;
}
Byte ACC(){
return 0;
}
Byte IMM(){
return 0;
}
Byte ZP0() {
return 0;
}
Byte ZPX(){
return 0;
}
Byte ZPY() {
return 0;
}
Byte REL() {
return 0;
}
Byte AB0() {
return 0;
}
Byte ABX() {
return 0;
}
Byte ABY() {
return 0;
}
Byte IND() {
return 0;
}
Byte IIX(){
return 0;
}
Byte IIY(){
return 0;
}
// =======================================
//          Addressing Modes
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
    Byte ZeroPageMemoryLocation = Y + memory[(*PC)++];

    return memory[ZeroPageMemoryLocation];
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

// =======================================
//            Load Y Register
// =======================================

void LDY_Logics(CPU_6502 *cpu, Byte O);

inline void LDY_Logics(CPU_6502 *cpu, Byte O) {
    cpu->Y = O;

    cpu->Z = IS_ZERO(cpu->Y);
    cpu->N = IS_NEGATIVE(cpu->Y);
}

Byte LDY_IM(CPU_6502 *cpu) {
    Byte O = AddressingMode_Immediate(cpu->memory, &cpu->PC);

    LDY_Logics(cpu, O);

    return LDY_IM_CYCLES;
}

Byte LDY_ZP(CPU_6502 *cpu) {
    Byte O = AddressingMode_ZeroPage(cpu->memory, &cpu->PC);

    LDY_Logics(cpu, O);

    return LDY_ZP_CYCLES;
}

Byte LDY_ZP_X(CPU_6502 *cpu) {
    Byte O = AddressingMode_ZeroPageX(cpu->memory, &cpu->PC, cpu->X);

    LDY_Logics(cpu, O);

    return LDY_ZP_X_CYCLES;
}

Byte LDY_AB(CPU_6502 *cpu) {
    Byte O = AddressingMode_Absolute(cpu->memory, &cpu->PC);

    LDY_Logics(cpu, O);

    return LDY_AB_CYCLES;
}

Byte LDY_AB_X(CPU_6502 *cpu) {
    int cycles = 0;
    Byte O = AddressingMode_AbsoluteX(cpu->memory, &cpu->PC, cpu->X, &cycles);

    LDY_Logics(cpu, O);

    return LDY_AB_X_CYCLES + cycles;
}
