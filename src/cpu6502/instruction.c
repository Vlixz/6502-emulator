#include "instruction.h"
#include "cpu.h"
#include <stdbool.h>
#include <stdio.h>

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
     {"LDX", &LDX, &ZPY, 4},
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

uint8_t (*addrmode)(Word *address);

uint8_t branch(Word relative_address_offset) {
    Word tmp = cpu.PC;

    cpu.PC += relative_address_offset;

    return 1 + ((tmp >> 8) != (cpu.PC >> 8)); // +1 succesfull branch && +1 if a page is crossed.
}

/**
 * =======================================
 *              Instructions
 * =======================================
 * 
 */

uint8_t ADC(Word address) {
    Byte operand = mem_fetch(address);

    bool areSignBitsEqual =
        !((cpu.A & BIT_MASK_SIGNED) ^ (operand & BIT_MASK_SIGNED));

    unsigned int value = cpu.A + cpu.C + operand;

    cpu.A = value;

    cpu.C = (value & BIT_MASK_CARRY) > 0;
    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.A);

    cpu.V = areSignBitsEqual *
            ((operand & BIT_MASK_SIGNED) != (cpu.A & BIT_MASK_SIGNED));

    return NO_EXTRA_CYCLES;
}

uint8_t AND(Word address) {
    cpu.A &= mem_fetch(address);

    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.A);

    return NO_EXTRA_CYCLES;
}

uint8_t ASL(Word address) {
    Word value = (addrmode == &ACC) ? cpu.A : mem_fetch(address);

    value <<= 1;

    cpu.C = (value & 0x100) > 0;
    cpu.Z = IS_ZERO(value & 0x00FF);
    cpu.N = IS_NEGATIVE(value & 0x00FF);

    (addrmode == &ACC) ? cpu.A = value : mem_write(address, value);

    return NO_EXTRA_CYCLES;
}

uint8_t BCC(Word address) {
    return (!cpu.C) ? branch(address) : NO_EXTRA_CYCLES;
}

uint8_t BCS(Word address) {
    return (cpu.C) ? branch(address) : NO_EXTRA_CYCLES;
}

uint8_t BEQ(Word address) {
    return (cpu.Z) ? branch(address) : NO_EXTRA_CYCLES;
}

uint8_t BIT(Word address) {
    Byte operand = mem_fetch(address);

    Byte result = cpu.A & operand;

    cpu.N = IS_NEGATIVE(operand);
    cpu.V = (operand & 0b01000000) > 0;

    cpu.Z = IS_ZERO(result);

    return NO_EXTRA_CYCLES;
}

uint8_t BMI(Word address) {
    return (cpu.N) ? branch(address) : NO_EXTRA_CYCLES;
}

uint8_t BNE(Word address) {
    return (!cpu.Z) ? branch(address) : NO_EXTRA_CYCLES;
}

uint8_t BPL(Word address) {
    return (!cpu.N) ? branch(address) : NO_EXTRA_CYCLES;
}

uint8_t BRK(Word address) {
    stack_push_word(++cpu.PC);
    cpu.B = 1;
    stack_push_ps();

    Byte LSB = mem_fetch(0xFFFE);
    Byte MSB = mem_fetch(0xFFFF);

    cpu.PC =  COMBINE_BYTES_LITTLE_ENDIAN(MSB, LSB);

    return NO_EXTRA_CYCLES;
}

uint8_t BVC(Word address) {
    return (!cpu.V) ? branch(address) : NO_EXTRA_CYCLES;
}

uint8_t BVS(Word address) {
    return (cpu.V) ? branch(address) : NO_EXTRA_CYCLES;
}

uint8_t CLC(Word address) {
    cpu.C = 0;
    return NO_EXTRA_CYCLES;
}

uint8_t CLD(Word address) {
    cpu.D = 0;
    return NO_EXTRA_CYCLES;
}

uint8_t CLI(Word address) {
    cpu.I = 0;
    return NO_EXTRA_CYCLES;
}

uint8_t CLV(Word address) {
    cpu.V = 0;
    return NO_EXTRA_CYCLES;
}

uint8_t CMP(Word address) {
    Byte operand = mem_fetch(address);

    cpu.C = (cpu.A >= operand);
    cpu.Z = (cpu.A == operand);
    cpu.N = IS_NEGATIVE(cpu.A - operand);

    return NO_EXTRA_CYCLES;
}

uint8_t CPX(Word address) {
    Byte operand = mem_fetch(address);

    cpu.C = (cpu.X >= operand);
    cpu.Z = (cpu.X == operand);
    cpu.N = IS_NEGATIVE(cpu.X - operand);

    return NO_EXTRA_CYCLES;
}

uint8_t CPY(Word address) {
    Byte operand = mem_fetch(address);

    cpu.C = (cpu.Y >= operand);
    cpu.Z = (cpu.Y == operand);
    cpu.N = IS_NEGATIVE(cpu.Y - operand);

    return NO_EXTRA_CYCLES;
}

uint8_t DEC(Word address) {
    Byte operand = mem_fetch(address);

    Byte value = operand - 1;

    cpu.Z = IS_ZERO(value);
    cpu.N = IS_NEGATIVE(value);

    mem_write(address, value);

    return NO_EXTRA_CYCLES;
}

uint8_t DEX(Word address) {
    cpu.X -= 1;

    cpu.Z = IS_ZERO(cpu.X);
    cpu.N = IS_NEGATIVE(cpu.X);

    return NO_EXTRA_CYCLES;
}

uint8_t DEY(Word address) {
    cpu.Y -= 1;

    cpu.Z = IS_ZERO(cpu.Y);
    cpu.N = IS_NEGATIVE(cpu.Y);

    return NO_EXTRA_CYCLES;
}

uint8_t EOR(Word address) {
    Byte operand = mem_fetch(address);

    cpu.A ^= operand;

    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.A);

    return NO_EXTRA_CYCLES;
}

uint8_t INC(Word address) {
    Byte operand = mem_fetch(address);

    operand += 1;

    cpu.Z = IS_ZERO(operand);
    cpu.N = IS_NEGATIVE(operand);

    mem_write(address, operand);

    return NO_EXTRA_CYCLES;
}

uint8_t INX(Word address) {
    cpu.X += 1;

    cpu.Z = IS_ZERO(cpu.X);
    cpu.N = IS_NEGATIVE(cpu.X);

    return NO_EXTRA_CYCLES;
}

uint8_t INY(Word address) {
    cpu.Y += 1;

    cpu.Z = IS_ZERO(cpu.Y);
    cpu.N = IS_NEGATIVE(cpu.Y);

    return NO_EXTRA_CYCLES;
}

uint8_t JMP(Word address) {
    cpu.PC = address;
    return NO_EXTRA_CYCLES;
}

uint8_t JSR(Word address) {
    stack_push_word(--cpu.PC);

    cpu.PC = address;

    return NO_EXTRA_CYCLES;
}

uint8_t LDA(Word address) {
    Byte operand = mem_fetch(address);

    cpu.A = operand;

    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.A);

    return NO_EXTRA_CYCLES;
}

uint8_t LDX(Word address) {
    Byte operand = mem_fetch(address);

    cpu.X = operand;

    cpu.Z = IS_ZERO(cpu.X);
    cpu.N = IS_NEGATIVE(cpu.X);

    return NO_EXTRA_CYCLES;
}

uint8_t LDY(Word address) {
    Byte operand = mem_fetch(address);

    cpu.Y = operand;

    cpu.Z = IS_ZERO(cpu.Y);
    cpu.N = IS_NEGATIVE(cpu.Y);

    return NO_EXTRA_CYCLES;
}

uint8_t LSR(Word address) {
    Byte operand = mem_fetch(address);

    Word value = operand >> 1;

    cpu.C = (value & 0x100) > 0;
    cpu.Z = IS_ZERO(value);
    cpu.N = IS_NEGATIVE(value);

    if (addrmode == &ACC) {
        cpu.A = value;
    } else {
        mem_write(address, value);
    }

    return NO_EXTRA_CYCLES;
}

uint8_t NOP(Word address) { return NO_EXTRA_CYCLES; }

uint8_t ORA(Word address) {
    Byte operand = mem_fetch(address);

    operand = mem_fetch(address);
    
    cpu.A |= operand;

    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.N);

    return NO_EXTRA_CYCLES;
}

uint8_t PHA(Word address) {
    stack_push_byte(cpu.A);
    return NO_EXTRA_CYCLES;
}

uint8_t PHP(Word address) {
    stack_push_ps();
    return NO_EXTRA_CYCLES;
}

uint8_t PLA(Word address) {
    cpu.A = stack_pop_byte();
    return NO_EXTRA_CYCLES;
}

uint8_t PLP(Word address) {
    stack_pop_ps();
    return NO_EXTRA_CYCLES;
}

uint8_t ROL(Word address) {
    Byte operand = (addrmode == &ACC) ? cpu.A : mem_fetch(address);

    Word value = (Word)(operand << 1) | cpu.C;

    cpu.C = (value & 0xFF00) == 1;
    cpu.Z = IS_ZERO(value & 0x00FF);
    cpu.N = IS_NEGATIVE(value);

    if (addrmode == &ACC) {
        cpu.A = value;
    } else {
        mem_write(address, value);
    }

    return NO_EXTRA_CYCLES;
}

uint8_t ROR(Word address) {
    Byte operand =  (addrmode == &ACC) ? cpu.A : mem_fetch(address);

    Word value = (Word)(cpu.C << 7) | (operand >> 1);

    cpu.C = value & 0x0001;
    cpu.Z = IS_ZERO(value & 0x00FF);
    cpu.N = IS_NEGATIVE(value);

    if (addrmode == &ACC) {
        cpu.A = value;
    } else {
        mem_write(address, value);
    }

    return NO_EXTRA_CYCLES;
}

uint8_t RTI(Word address) {
    stack_pop_ps();
    cpu.PC = stack_pop_word();
    return NO_EXTRA_CYCLES;
}

uint8_t RTS(Word address) {
    cpu.PC = stack_pop_word() - 1;
    return NO_EXTRA_CYCLES;
}

uint8_t SBC(Word address) { return 0; }

uint8_t SEC(Word address) {
    cpu.C = 1;
    return NO_EXTRA_CYCLES;
}

uint8_t SED(Word address) {
    cpu.D = 1;
    return NO_EXTRA_CYCLES;
}

uint8_t SEI(Word address) {
    cpu.I = 1;
    return NO_EXTRA_CYCLES;
}

uint8_t STA(Word address) {
    mem_write(address, cpu.A);
    return NO_EXTRA_CYCLES;
}

uint8_t STX(Word address) {
    Byte operand = mem_fetch(address);
    mem_write(operand, cpu.X);
    return NO_EXTRA_CYCLES;
}

uint8_t STY(Word address) {
    Byte operand = mem_fetch(address);
    mem_write(operand, cpu.Y);
    return NO_EXTRA_CYCLES;
}

uint8_t TAX(Word address) {
    cpu.X = cpu.A;

    cpu.Z = IS_ZERO(cpu.X);
    cpu.N = IS_NEGATIVE(cpu.X);

    return NO_EXTRA_CYCLES;
}

uint8_t TAY(Word address) {
    cpu.Y = cpu.A;

    cpu.Z = IS_ZERO(cpu.Y);
    cpu.N = IS_NEGATIVE(cpu.Y);

    return NO_EXTRA_CYCLES;
}

uint8_t TSX(Word address) {
    cpu.X = cpu.SP;

    cpu.Z = IS_ZERO(cpu.X);
    cpu.N = IS_NEGATIVE(cpu.X);

    return NO_EXTRA_CYCLES;
}

uint8_t TXA(Word address) {
    cpu.A = cpu.X;

    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.A);

    return NO_EXTRA_CYCLES;
}

uint8_t TXS(Word address) {
    cpu.SP = cpu.X;

    cpu.Z = IS_ZERO(cpu.SP);
    cpu.N = IS_NEGATIVE(cpu.SP);
    
    return NO_EXTRA_CYCLES;
}

uint8_t TYA(Word address) {
    cpu.A = cpu.Y;

    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.A);

    return NO_EXTRA_CYCLES;
}

uint8_t XXX(Word address) { 
    fprintf(stderr, "Unknown opcode\n");
    return NO_EXTRA_CYCLES; 
}

/**
 * =======================================
 *           Addressing Modes
 * =======================================
 * 
 */

uint8_t IMP(Word *address) { return NO_EXTRA_CYCLES; }

uint8_t ACC(Word *address) { return NO_EXTRA_CYCLES; }

uint8_t IMM(Word *address) {
    (*address) = cpu.PC;

    return NO_EXTRA_CYCLES;
}

uint8_t ZP0(Word *address) {
    (*address) = mem_fetch(cpu.PC) & 0x00FF;
    
    return NO_EXTRA_CYCLES;
}

uint8_t ZPX(Word *address) {
    Byte LSB = mem_fetch(cpu.PC);
    (*address) = (LSB + cpu.X) & 0x00FF;

    return NO_EXTRA_CYCLES;
}

uint8_t ZPY(Word *address) {
    Byte LSB = mem_fetch(cpu.PC);
    (*address) = (LSB + cpu.Y) & 0x00FF;

    return NO_EXTRA_CYCLES;
}

uint8_t REL(Word *address) {
    (*address) = mem_fetch(cpu.PC);

    return 0;
}

uint8_t AB0(Word *address) {
    Byte LSB = mem_fetch(cpu.PC);
    Byte MSB = mem_fetch(cpu.PC);

    (*address) = COMBINE_BYTES_LITTLE_ENDIAN(MSB, LSB);

    return NO_EXTRA_CYCLES;
}

uint8_t ABX(Word *address) {
    Byte LSB = mem_fetch(cpu.PC);
    Byte MSB = mem_fetch(cpu.PC);

    (*address) = COMBINE_BYTES_LITTLE_ENDIAN(MSB, LSB) + cpu.X;

    return DID_CROSS_PAGE_BOUNDARY(LSB, cpu.X);
}

uint8_t ABY(Word *address) {
    Byte LSB = mem_fetch(cpu.PC);
    Byte MSB = mem_fetch(cpu.PC);

    (*address) = COMBINE_BYTES_LITTLE_ENDIAN(MSB, LSB) + cpu.Y;

    return DID_CROSS_PAGE_BOUNDARY(LSB, cpu.Y);
}

uint8_t IND(Word *address) {
    Byte LSB = mem_fetch(cpu.PC);
    Byte MSB = mem_fetch(cpu.PC);

    Word pointer = COMBINE_BYTES_LITTLE_ENDIAN(MSB, LSB);

    if (LSB == 0xFF) {
        (*address) = (mem_fetch(pointer & 0xFF00) << 8) | mem_fetch(pointer);
    } else {
        (*address) = (mem_fetch(pointer + 1) << 8) | mem_fetch(pointer);
    }

    return NO_EXTRA_CYCLES;
}

uint8_t IIX(Word *address) {
    Byte zero_page_address = mem_fetch(cpu.PC);

    zero_page_address += cpu.X;

    Byte LSB = mem_fetch(zero_page_address);
    Byte MSB = mem_fetch(zero_page_address + 1);

    (*address) = COMBINE_BYTES_LITTLE_ENDIAN(MSB, LSB);

    return NO_EXTRA_CYCLES;
}

uint8_t IIY(Word *address) {
    Byte zero_page_address = mem_fetch(cpu.PC);

    Byte LSB = mem_fetch(zero_page_address);
    Byte MSB = mem_fetch(zero_page_address + 1);

    (*address) = COMBINE_BYTES_LITTLE_ENDIAN(MSB, LSB) + cpu.Y;

    return DID_CROSS_PAGE_BOUNDARY(LSB, cpu.Y);
}

instruction get_instruction(Byte opcode) {
    return matrix[opcode >> 4][opcode & 0x0F];
}

Byte ins_execute() {
    Byte opcode = mem_fetch(cpu.PC);

    instruction ins = get_instruction(opcode);
    addrmode = ins.addrmode;

    Word address;

    uint8_t additional_cycles_1 = ins.addrmode(&address);
    uint8_t additional_cycles_2 = ins.operation(address);

    return ins.cycles + additional_cycles_1 + additional_cycles_2;
}
