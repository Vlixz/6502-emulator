#include <stdbool.h>
#include <stdio.h>

#include "cpu.h"
#include "memory.h"
#include "instruction.h"

instruction current_instruction;

uint8_t branch(Word relative_address_offset) {
    Word tmp = cpu.PC;

    if (relative_address_offset & 0x80) {
        relative_address_offset |= 0xFF00;
    }

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
    Word value = (current_instruction.addrmode == &ACC) ? cpu.A : mem_fetch(address);

    value <<= 1;

    cpu.C = (value & 0x100) > 0;
    cpu.Z = IS_ZERO(value & 0x00FF);
    cpu.N = IS_NEGATIVE(value & 0x00FF);

    (current_instruction.addrmode == &ACC) ? cpu.A = value : mem_write(address, value);

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
    
    cpu.I = 1; // Disable interrupts during BRK

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
    cpu.N = IS_NEGATIVE((Word)cpu.A - (Word)operand);

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
    Word value = (current_instruction.addrmode == &ACC) ? cpu.A : mem_fetch(address);
    
    cpu.C = (value & 0x01) > 0;
    
    value >>= 1;

    cpu.Z = IS_ZERO(value & 0x00FF);
    cpu.N = IS_NEGATIVE(value & 0x00FF);

    (current_instruction.addrmode == &ACC) ? cpu.A = value : mem_write(address, value);

    return NO_EXTRA_CYCLES;
}

uint8_t NOP(Word address) { return NO_EXTRA_CYCLES; }

uint8_t ORA(Word address) {
    Byte operand = mem_fetch(address);

    cpu.A |= operand;

    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.A);

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

    cpu.Z = IS_ZERO(cpu.A);
    cpu.N = IS_NEGATIVE(cpu.A);

    return NO_EXTRA_CYCLES;
}

uint8_t PLP(Word address) {
    stack_pop_ps();
    return NO_EXTRA_CYCLES;
}

uint8_t ROL(Word address) {
    Byte operand = (current_instruction.addrmode == &ACC) ? cpu.A : mem_fetch(address);

    Word value = (Word)(operand << 1) | cpu.C;

    cpu.C = (value & 0x0100) > 0;
    cpu.Z = IS_ZERO(value & 0x00FF);
    cpu.N = IS_NEGATIVE(value);

    (current_instruction.addrmode == &ACC) ? cpu.A = value : mem_write(address, value);

    return NO_EXTRA_CYCLES;
}

uint8_t ROR(Word address) {
    Byte operand =  (current_instruction.addrmode == &ACC) ? cpu.A : mem_fetch(address);

    Word value = (Word)(operand >> 1) | (cpu.C << 7) ;

    cpu.C = operand & 0x01; 
    cpu.Z = IS_ZERO(value & 0x00FF);
    cpu.N = IS_NEGATIVE(value);

    (current_instruction.addrmode == &ACC) ? cpu.A = value : mem_write(address, value);

    return NO_EXTRA_CYCLES;
}

uint8_t RTI(Word address) {
    stack_pop_ps();
    cpu.PC = stack_pop_word();

    return NO_EXTRA_CYCLES;
}

uint8_t RTS(Word address) {
    cpu.PC = stack_pop_word() + 1;

    return NO_EXTRA_CYCLES;
}

uint8_t SBC(Word address) { 
    Byte operand = mem_fetch(address);

    uint16_t value = ((uint16_t)operand) ^ 0x00FF;

    uint16_t tmp = (uint16_t)cpu.A + value + cpu.C;

    cpu.C = (tmp & 0xFF00) > 0;
    cpu.Z = (tmp & 0x00FF) == 0;
    cpu.V = (((tmp ^ (uint16_t)cpu.A) & (tmp ^ value) & 0x0080)) > 0;
    cpu.N = IS_NEGATIVE(tmp);

    cpu.A = tmp & 0x00FF;

    return NO_EXTRA_CYCLES;
}

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
    mem_write(address, cpu.X);

    return NO_EXTRA_CYCLES;
}

uint8_t STY(Word address) {
    mem_write(address, cpu.Y);

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