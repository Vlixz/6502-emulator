#include "instruction.h"
#include "cpu.h"
#include <stdbool.h>

instruction matrix[16][16] = {

    {{"BRK", &BRK, &IMP, 7}, /* 0x0 */
     {"ORA", &ORA, &IIX, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"ORA", &ORA, &ZP0, 3},
     {"ASL", &ASL, &ZP0, 5},
     {"???", &XXX, &IMP, 1},
     {"PHP", &PHP, &IMP, 3},
     {"ORA", &ORA, &IMM, 2},
     {"ASL", &ASL, &ACC, 2},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"ORA", &ORA, &AB0, 4},
     {"ASL", &ASL, &AB0, 6},
     {"???", &XXX, &IMP, 1}}, /* 0x0 */
                              /* 0x1 */
    {{"BPL", &BPL, &REL, 2},
     {"ORA", &ORA, &IIY, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"ORA", &ORA, &ZPX, 4},
     {"ASL", &ASL, &ZPX, 6},
     {"???", &XXX, &IMP, 1},
     {"CLC", &CLC, &IMP, 2},
     {"ORA", &ORA, &ABY, 4},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"ORA", &ORA, &ABX, 4},
     {"ASL", &ASL, &ABX, 7},
     {"???", &XXX, &IMP, 1}}, /* 0x1 */
                              /* 0x2 */
    {{"JSR", &JSR, &AB0, 6},
     {"AND", &AND, &IIX, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"BIT", &BIT, &ZP0, 3},
     {"AND", &AND, &ZP0, 3},
     {"ROL", &ROL, &ZP0, 5},
     {"???", &XXX, &IMP, 1},
     {"PLP", &PLP, &IMP, 4},
     {"AND", &AND, &IMM, 2},
     {"ROL", &ROL, &ACC, 2},
     {"???", &XXX, &IMP, 1},
     {"BIT", &BIT, &AB0, 4},
     {"AND", &AND, &AB0, 4},
     {"ROL", &ROL, &AB0, 6},
     {"???", &XXX, &IMP, 1}}, /* 0x2 */
                              /* 0x3 */
    {{"BMI", &BMI, &REL, 2},
     {"AND", &AND, &IIY, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"AND", &AND, &ZPX, 4},
     {"ROL", &ROL, &ZPX, 6},
     {"???", &XXX, &IMP, 1},
     {"SEC", &SEC, &IMP, 2},
     {"AND", &AND, &ABY, 4},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"AND", &AND, &ABX, 4},
     {"ROL", &ROL, &ABX, 7},
     {"???", &XXX, &IMP, 1}}, /* 0x3 */
                              /* 0x4 */
    {{"RTI", &RTI, &IMP, 6},
     {"EOR", &EOR, &IIX, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"EOR", &EOR, &ZP0, 3},
     {"LSR", &LSR, &ZP0, 5},
     {"???", &XXX, &IMP, 1},
     {"PHA", &PHA, &IMP, 3},
     {"EOR", &EOR, &IMM, 2},
     {"LSR", &LSR, &ACC, 2},
     {"???", &XXX, &IMP, 1},
     {"JMP", &JMP, &AB0, 3},
     {"EOR", &EOR, &AB0, 4},
     {"LSR", &LSR, &AB0, 6},
     {"???", &XXX, &IMP, 1}}, /* 0x4 */
                              /* 0x5 */
    {{"BVC", &BVC, &REL, 2},
     {"EOR", &EOR, &IIY, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"EOR", &EOR, &ZPX, 4},
     {"LSR", &LSR, &ZPX, 6},
     {"???", &XXX, &IMP, 1},
     {"CLI", &CLI, &IMP, 2},
     {"EOR", &EOR, &ABY, 4},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"EOR", &EOR, &ABX, 4},
     {"LSR", &LSR, &ABX, 7},
     {"???", &XXX, &IMP, 1}}, /* 0x5 */
                              /* 0x6 */
    {{"RTS", &RTS, &IMP, 6},
     {"ADC", &ADC, &IIX, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"ADC", &ADC, &ZP0, 3},
     {"ROR", &ROR, &ZP0, 5},
     {"???", &XXX, &IMP, 1},
     {"PLA", &PLA, &IMP, 4},
     {"ADC", &ADC, &IMM, 2},
     {"ROR", &ROR, &ACC, 2},
     {"???", &XXX, &IMP, 1},
     {"JMP", &JMP, &IND, 4},
     {"ADC", &ADC, &AB0, 4},
     {"ROR", &ROR, &AB0, 6},
     {"???", &XXX, &IMP, 1}}, /* 0x6 */
                              /* 0x7 */
    {{"BVS", &BVS, &REL, 2},
     {"ADC", &ADC, &IIY, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"ADC", &ADC, &ZPX, 4},
     {"ROR", &ROR, &ZPX, 6},
     {"???", &XXX, &IMP, 1},
     {"SEI", &SEI, &IMP, 2},
     {"ADC", &ADC, &ABY, 4},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"ADC", &ADC, &ABX, 4},
     {"ROR", &ROR, &ABX, 7},
     {"???", &XXX, &IMP, 1}}, /* 0x7 */
                              /* 0x8 */
    {{"???", &XXX, &IMP, 0},
     {"STA", &STA, &IIX, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"STY", &STY, &ZP0, 3},
     {"STA", &STA, &ZP0, 3},
     {"STX", &STX, &ZP0, 3},
     {"???", &XXX, &IMP, 1},
     {"DEY", &DEY, &IMP, 2},
     {"???", &XXX, &IMP, 1},
     {"TXA", &TXA, &IMP, 2},
     {"???", &XXX, &IMP, 1},
     {"STY", &STY, &AB0, 4},
     {"STA", &STA, &AB0, 4},
     {"STX", &STX, &AB0, 4},
     {"???", &XXX, &IMP, 1}}, /* 0x8 */
                              /* 0x9 */
    {{"BCC", &BCC, &REL, 2},
     {"STA", &STA, &IIY, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"STY", &STY, &ZPX, 4},
     {"STA", &STA, &ZPX, 4},
     {"STX", &STX, &ZPY, 4},
     {"???", &XXX, &IMP, 1},
     {"TYA", &TYA, &IMP, 2},
     {"STA", &STA, &ABY, 5},
     {"TXS", &TXS, &IMP, 2},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"STA", &STA, &ABX, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1}}, /* 0x9 */
                              /* 0xA */
    {{"LDY", &LDY, &IMM, 2},
     {"LDA", &LDA, &IIX, 6},
     {"LDX", &LDX, &IMM, 2},
     {"???", &XXX, &IMP, 1},
     {"LDY", &LDY, &ZP0, 3},
     {"LDA", &LDA, &ZP0, 3},
     {"LDX", &LDX, &ZP0, 3},
     {"???", &XXX, &IMP, 1},
     {"TAY", &TAY, &IMP, 2},
     {"LDA", &LDA, &IMM, 2},
     {"TAX", &TAX, &IMP, 2},
     {"???", &XXX, &IMP, 1},
     {"LDY", &LDY, &AB0, 4},
     {"LDA", &LDA, &AB0, 4},
     {"LDX", &LDX, &AB0, 4},
     {"???", &XXX, &IMP, 1}}, /* 0xA */
                              /* 0xB */
    {{"BCS", &BCS, &REL, 2},
     {"LDA", &LDA, &IIY, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"LDY", &LDY, &ZPX, 4},
     {"LDA", &LDA, &ZPX, 4},
     {"LDX", &LDX, &ZPX, 4},
     {"???", &XXX, &IMP, 1},
     {"CLV", &CLV, &IMP, 2},
     {"LDA", &LDA, &ABY, 4},
     {"TSX", &TSX, &IMP, 2},
     {"???", &XXX, &IMP, 1},
     {"LDY", &LDY, &ABX, 4},
     {"LDA", &LDA, &ABX, 4},
     {"LDX", &LDX, &ABY, 4},
     {"???", &XXX, &IMP, 1}}, /* 0xB */
                              /* 0xC */
    {{"CPY", &CPY, &IMM, 2},
     {"CMP", &CMP, &IIX, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"CPY", &CPY, &ZP0, 3},
     {"CMP", &CMP, &ZP0, 3},
     {"DEC", &DEC, &ZP0, 5},
     {"???", &XXX, &IMP, 1},
     {"INY", &INY, &IMP, 2},
     {"CMP", &CMP, &IMM, 2},
     {"DEX", &DEX, &IMP, 2},
     {"???", &XXX, &IMP, 1},
     {"CPY", &CPY, &AB0, 4},
     {"CMP", &CMP, &AB0, 4},
     {"DEC", &DEC, &AB0, 6},
     {"???", &XXX, &IMP, 1}}, /* 0xC */
                              /* 0xD */
    {{"BNE", &BNE, &REL, 2},
     {"CMP", &CMP, &IIY, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"CMP", &CMP, &ZPX, 4},
     {"DEC", &DEC, &ZPX, 6},
     {"???", &XXX, &IMP, 1},
     {"CLD", &CLD, &IMP, 2},
     {"CMP", &CMP, &ABY, 4},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"CMP", &CMP, &ABX, 4},
     {"DEC", &DEC, &ABX, 7},
     {"???", &XXX, &IMP, 1}}, /* 0xD */
                              /* 0xE */
    {{"CPX", &CPX, &IMM, 2},
     {"SBC", &SBC, &IIX, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"CPX", &CPX, &ZP0, 3},
     {"SBC", &SBC, &ZP0, 3},
     {"INC", &INC, &ZP0, 5},
     {"???", &XXX, &IMP, 1},
     {"INX", &INX, &IMP, 2},
     {"SBC", &SBC, &IMM, 2},
     {"NOP", &NOP, &IMP, 2},
     {"???", &XXX, &IMP, 1},
     {"CPX", &CPX, &AB0, 4},
     {"SBC", &SBC, &AB0, 4},
     {"INC", &INC, &AB0, 6},
     {"???", &XXX, &IMP, 1}}, /* 0xE */
                              /* 0xF */
    {{"BEQ", &BEQ, &REL, 2},
     {"SBC", &SBC, &IIY, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"SBC", &SBC, &ZPX, 4},
     {"INC", &INC, &ZPX, 6},
     {"???", &XXX, &IMP, 1},
     {"SED", &SED, &IMP, 2},
     {"SBC", &SBC, &ABY, 4},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"SBC", &SBC, &ABX, 4},
     {"INC", &INC, &ABX, 7},
     {"???", &XXX, &IMP, 1}}, /* 0xF */
};

Byte branch(Word relative_address) {
    int cycles = 1;

    Word tmp = cpu.PC;

    cpu.PC += relative_address;

    cycles += (tmp >> 8) != (cpu.PC >> 8); // +1 if a page is crossed.

    return cycles;
}

Word absolute_address;
Byte (*addrmode)(Byte *operand);

Byte ADC(Byte operand) {
    bool areSignBitsEqual =
        !((cpu.A & BIT_MASK_SIGNED) ^ (operand & BIT_MASK_SIGNED));

    unsigned int value = cpu.A + cpu.C + operand;

    cpu.A = value;

    cpu.C = (value & BIT_MASK_CARRY) > 0;
    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.A);

    cpu.V = areSignBitsEqual *
            ((operand & BIT_MASK_SIGNED) != (cpu.A & BIT_MASK_SIGNED));

    return 0;
}

Byte AND(Byte operand) {
    cpu.A &= operand;

    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.A);

    return 0;
}

Byte ASL(Byte operand) {
    Word value = operand << 1;

    cpu.C = (value & 0x100) > 0;
    cpu.Z = IS_ZERO(value & 0x00FF);
    cpu.N = IS_NEGATIVE(value & 0x00FF);

    if (addrmode == &ACC) {
        cpu.A = value;
    } else {
        mem_write(absolute_address, value);
    }

    return 0;
}

Byte BCC(Byte operand) {
    if (!cpu.C)
        return branch(operand);

    return 0;
}

Byte BCS(Byte operand) {
    if (cpu.C)
        return branch(operand);

    return 0;
}

Byte BEQ(Byte operand) {
    if (cpu.Z)
        return branch(operand);

    return 0;
}

Byte BIT(Byte operand) {
    Byte result = cpu.A & operand;

    cpu.N = IS_NEGATIVE(operand);
    cpu.V = (operand & 0b01000000) > 0;

    cpu.Z = IS_ZERO(result);

    return 0;
}

Byte BMI(Byte operand) {
    if (cpu.N)
        return branch(operand);

    return 0;
}

Byte BNE(Byte operand) {
    if (!cpu.Z)
        return branch(operand);

    return 0;
}

Byte BPL(Byte operand) {
    if (!cpu.N)
        return branch(operand);

    return 0;
}

Byte BRK(Byte operand) {
    stack_push_word(++cpu.PC);
    cpu.B = 1;
    stack_push_ps();

    Byte LSB = mem_fetch(0xFFFE);
    Byte MSB = mem_fetch(0xFFFF);

    cpu.PC = LSB | MSB << 8;

    return 0;
}

Byte BVC(Byte operand) {
    if (!cpu.V)
        return branch(operand);

    return 0;
}

Byte BVS(Byte operand) {
    if (cpu.V)
        return branch(operand);

    return 0;
}

Byte CLC(Byte operand) {
    cpu.C = 0;
    return 0;
}

Byte CLD(Byte operand) {
    cpu.D = 0;
    return 0;
}

Byte CLI(Byte operand) {
    cpu.I = 0;
    return 0;
}

Byte CLV(Byte operand) {
    cpu.V = 0;
    return 0;
}

Byte CMP(Byte operand) {
    cpu.C = (cpu.A >= operand);
    cpu.Z = (cpu.A == operand);
    cpu.N = IS_NEGATIVE(cpu.A - operand);

    return 0;
}

Byte CPX(Byte operand) {
    cpu.C = (cpu.X >= operand);
    cpu.Z = (cpu.X == operand);
    cpu.N = IS_NEGATIVE(cpu.X - operand);

    return 0;
}

Byte CPY(Byte operand) {
    cpu.C = (cpu.Y >= operand);
    cpu.Z = (cpu.Y == operand);
    cpu.N = IS_NEGATIVE(cpu.Y - operand);

    return 0;
}

Byte DEC(Byte operand) {
    Byte value = operand - 1;

    cpu.Z = IS_ZERO(value);
    cpu.N = IS_NEGATIVE(value);

    mem_write(absolute_address, value);
    return 0;
}

Byte DEX(Byte operand) {
    cpu.X -= 1;

    cpu.Z = IS_ZERO(cpu.X);
    cpu.N = IS_NEGATIVE(cpu.X);

    return 0;
}

Byte DEY(Byte operand) {
    cpu.Y -= 1;

    cpu.Z = IS_ZERO(cpu.Y);
    cpu.N = IS_NEGATIVE(cpu.Y);

    return 0;
}

Byte EOR(Byte operand) {
    cpu.A ^= operand;

    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.A);

    return 0;
}

Byte INC(Byte operand) {
    operand += 1;

    cpu.Z = IS_ZERO(operand);
    cpu.N = IS_NEGATIVE(operand);

    mem_write(absolute_address, operand);

    return 0;
}

Byte INX(Byte operand) {
    cpu.X += 1;

    cpu.Z = IS_ZERO(cpu.X);
    cpu.N = IS_NEGATIVE(cpu.X);

    return 0;
}

Byte INY(Byte operand) {
    cpu.Y += 1;

    cpu.Z = IS_ZERO(cpu.Y);
    cpu.N = IS_NEGATIVE(cpu.Y);

    return 0;
}

Byte JMP(Byte operand) {
    cpu.PC = operand;
    return 0;
}

Byte JSR(Byte operand) {
    stack_push_word(--cpu.PC);

    cpu.PC = operand;

    return 0;
}

Byte LDA(Byte operand) {
    cpu.A = operand;

    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.A);

    return 0;
}

Byte LDX(Byte operand) {
    cpu.X = operand;

    cpu.Z = IS_ZERO(cpu.X);
    cpu.N = IS_NEGATIVE(cpu.X);

    return 0;
}

Byte LDY(Byte operand) {
    cpu.Y = operand;

    cpu.Z = IS_ZERO(cpu.Y);
    cpu.N = IS_NEGATIVE(cpu.Y);

    return 0;
}

Byte LSR(Byte operand) {
    Word value = operand >> 1;

    cpu.C = (value & 0x100) > 0;
    cpu.Z = IS_ZERO(value);
    cpu.N = IS_NEGATIVE(value);

    if (addrmode == &ACC) {
        cpu.A = value;
    } else {
        mem_write(absolute_address, value);
    }

    return 0;
}

Byte NOP(Byte operand) { return 0; }

Byte ORA(Byte operand) {
    cpu.A |= operand;

    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.N);

    return 0;
}

Byte PHA(Byte operand) {
    stack_push_byte(cpu.A);
    return 0;
}

Byte PHP(Byte operand) {
    stack_push_ps();
    return 0;
}

Byte PLA(Byte operand) {
    cpu.A = stack_pop_byte();
    return 0;
}

Byte PLP(Byte operand) {
    stack_pop_ps();
    return 0;
}

Byte ROL(Byte operand) {
    Word value = (Word)(operand << 1) | cpu.C;

    cpu.C = (value & 0xFF00) == 1;
    cpu.Z = IS_ZERO(value & 0x00FF);
    cpu.N = IS_NEGATIVE(value);

    if (addrmode == &IMP) {
        cpu.A = value;
    } else {
        mem_write(absolute_address, value);
    }

    return 0;
}

Byte ROR(Byte operand) {
    Word value = (Word)(cpu.C << 7) | (operand >> 1);

    cpu.C = value & 0x0001;
    cpu.Z = IS_ZERO(value & 0x00FF);
    cpu.N = IS_NEGATIVE(value);

    if (addrmode == &IMP) {
        cpu.A = value;
    } else {
        mem_write(absolute_address, value);
    }

    return 0;
}

Byte RTI(Byte operand) {
    stack_pop_ps();
    cpu.PC = stack_pop_word();
    return 0;
}

Byte RTS(Byte operand) {
    cpu.PC = stack_pop_word() - 1;
    return 0;
}

Byte SBC(Byte operand) { return 0; }

Byte SEC(Byte operand) {
    cpu.C = 1;
    return 0;
}

Byte SED(Byte operand) {
    cpu.D = 1;
    return 0;
}

Byte SEI(Byte operand) {
    cpu.I = 1;
    return 0;
}

Byte STA(Byte operand) {
    mem_write(operand, cpu.A);
    return 0;
}

Byte STX(Byte operand) {
    mem_write(operand, cpu.X);
    return 0;
}

Byte STY(Byte operand) {
    mem_write(operand, cpu.Y);
    return 0;
}

Byte TAX(Byte operand) {
    cpu.X = cpu.A;

    cpu.Z = IS_ZERO(cpu.X);
    cpu.N = IS_NEGATIVE(cpu.X);

    return 0;
}

Byte TAY(Byte operand) {
    cpu.Y = cpu.A;

    cpu.Z = IS_ZERO(cpu.Y);
    cpu.N = IS_NEGATIVE(cpu.Y);

    return 0;
}

Byte TSX(Byte operand) {
    cpu.X = cpu.SP;

    cpu.Z = IS_ZERO(cpu.X);
    cpu.N = IS_NEGATIVE(cpu.X);

    return 0;
}

Byte TXA(Byte operand) {
    cpu.A = cpu.X;

    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.A);

    return 0;
}

Byte TXS(Byte operand) {
    cpu.SP = cpu.X;

    cpu.Z = IS_ZERO(cpu.SP);
    cpu.N = IS_NEGATIVE(cpu.SP);
    
    return 0;
}

Byte TYA(Byte operand) {
    cpu.A = cpu.Y;

    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.A);

    return 0;
}

Byte XXX(Byte operand) { return 0; }

uint8_t IMP(Byte *operand) { return 0; }

uint8_t ACC(Byte *operand) { 
    (*operand) = cpu.A;
    return 0; 
}

uint8_t IMM(Byte *operand) {
    (*operand) = mem_fetch(cpu.PC);
    return 0;
}

uint8_t ZP0(Byte *operand) {
    absolute_address = mem_fetch(cpu.PC) & 0x00FF;
    (*operand) = mem_fetch(absolute_address);
    return 0;
}

uint8_t ZPX(Byte *operand) {
    Byte zero_page_address = cpu.X + mem_fetch(cpu.PC);
    absolute_address = (Word)zero_page_address;
    (*operand) = mem_fetch(zero_page_address);
    return 0;
}

uint8_t ZPY(Byte *operand) {
    Byte zero_page_address = cpu.Y + mem_fetch(cpu.PC);
    absolute_address = (Word)zero_page_address;
    (*operand) = mem_fetch(zero_page_address);
    return 0;
}

uint8_t REL(Byte *operand) {
    (*operand) = mem_fetch(cpu.PC);
    return 0;
}

uint8_t AB0(Byte *operand) {
    Byte LSB = mem_fetch(cpu.PC);
    Byte MSB = mem_fetch(cpu.PC);

    absolute_address = (Word)LSB | MSB << 8;

    (*operand) = mem_fetch(absolute_address);
    return 0;
}

uint8_t ABX(Byte *operand) {
    Byte LSB = mem_fetch(cpu.PC);
    Byte MSB = mem_fetch(cpu.PC);

    absolute_address = (Word)LSB | MSB << 8;
    (*operand) = mem_fetch(absolute_address += cpu.X);

    return (Byte)(LSB + cpu.X) < cpu.X;
}

uint8_t ABY(Byte *operand) {
    Byte LSB = mem_fetch(cpu.PC);
    Byte MSB = mem_fetch(cpu.PC);

    absolute_address = (Word)LSB | MSB << 8;
    (*operand) = mem_fetch(absolute_address + cpu.Y);

    return (Byte)(LSB + cpu.Y) < cpu.Y;
}

uint8_t IND(Byte *operand) {
    Byte LSB = mem_fetch(cpu.PC);
    Byte MSB = mem_fetch(cpu.PC);

    Word pointer = (Word)LSB | MSB << 8;

    if (LSB == 0xFF) {
        (*operand) = (mem_fetch(pointer & 0xFF00) << 8) | mem_fetch(pointer);
    } else {
        (*operand) = (mem_fetch(pointer + 1) << 8) | mem_fetch(pointer);
    }

    return 0;
}

uint8_t IIX(Byte *operand) {
    Byte zero_page_address = mem_fetch(cpu.PC);

    zero_page_address += cpu.X;

    Byte LSB = mem_fetch(zero_page_address);
    Byte MSB = mem_fetch(zero_page_address + 1);

    absolute_address = (Word)LSB | MSB << 8;

    (*operand) = mem_fetch(absolute_address);

    return 0;
}

uint8_t IIY(Byte *operand) {
    Byte zero_page_address = mem_fetch(cpu.PC);

    Byte LSB = mem_fetch(zero_page_address);
    Byte MSB = mem_fetch(zero_page_address + 1);

    absolute_address = (Word)LSB | MSB << 8;

    (*operand) = mem_fetch(absolute_address + cpu.Y);

    return (Byte)(LSB + cpu.Y) < cpu.Y;
}

uint8_t ins_execute() {
    Byte opcode = mem_fetch(cpu.PC);

    instruction ins = matrix[opcode >> 4][opcode & 0x0F];
    addrmode = ins.addrmode;

    Byte cycles = ins.cycles;

    Byte operand;

    Byte additional_cycles_1 = ins.addrmode(&operand);
    Byte additional_cycles_2 = ins.operation(operand);

    return cycles + additional_cycles_1 + additional_cycles_2;
}
