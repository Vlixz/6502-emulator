#ifndef INC_INSTRUCTION_H
#define INC_INSTRUCTION_H

#include "common.h"
#include <stdint.h>

typedef struct {
    char *name;

    Byte (*operation)(Byte operand);
    Byte (*addrmode)(Byte *operand);

    uint8_t cycles;
} instruction;

// =======================================
//             Instructions
// =======================================

uint8_t ins_execute();

Byte ADC(Byte operand);
Byte AND(Byte operand);
Byte ASL(Byte operand);
Byte BCC(Byte operand);
Byte BCS(Byte operand);
Byte BEQ(Byte operand);
Byte BIT(Byte operand);
Byte BMI(Byte operand);
Byte BNE(Byte operand);
Byte BPL(Byte operand);
Byte BRK(Byte operand);
Byte BVC(Byte operand);
Byte BVS(Byte operand);
Byte CLC(Byte operand);

Byte CLD(Byte operand);
Byte CLI(Byte operand);
Byte CLV(Byte operand);
Byte CMP(Byte operand);
Byte CPX(Byte operand);
Byte CPY(Byte operand);
Byte DEC(Byte operand);
Byte DEX(Byte operand);
Byte DEY(Byte operand);
Byte EOR(Byte operand);
Byte INC(Byte operand);
Byte INX(Byte operand);
Byte INY(Byte operand);
Byte JMP(Byte operand);

Byte JSR(Byte operand);
Byte LDA(Byte operand);
Byte LDX(Byte operand);
Byte LDY(Byte operand);
Byte LSR(Byte operand);
Byte NOP(Byte operand);
Byte ORA(Byte operand);
Byte PHA(Byte operand);
Byte PHP(Byte operand);
Byte PLA(Byte operand);
Byte PLP(Byte operand);
Byte ROL(Byte operand);
Byte ROR(Byte operand);
Byte RTI(Byte operand);

Byte RTS(Byte operand);
Byte SBC(Byte operand);
Byte SEC(Byte operand);
Byte SED(Byte operand);
Byte SEI(Byte operand);
Byte STA(Byte operand);
Byte STX(Byte operand);
Byte STY(Byte operand);
Byte TAX(Byte operand);
Byte TAY(Byte operand);
Byte TSX(Byte operand);
Byte TXA(Byte operand);
Byte TXS(Byte operand);
Byte TYA(Byte operand);

Byte XXX(Byte operand);

// =======================================
//            Addressing Modes
// =======================================

Byte IMP(Byte *operand);
Byte ACC(Byte *operand);

/**
 * @brief Immediate mode returns the value specified during compile time with
 * '#'
 *
 */
Byte IMM(Byte *operand);

/**
 * @brief Zero Page mode returns the value at a specific address in the Zero
 * Page (0x00 -> 0xTYA - Transfer Y to AccumulatorFF)
 *
 */
Byte ZP0(Byte *operand);

/**
 * @brief Zero Page X returns the value at a address added to the current value
 * in the X register
 *
 * @note EX: If the x register contains 0x0F and the given value is 0x80 then
 * the returned value is the value specified at address 0x8F
 *
 * @note The address calculation wraps around:
 *
 * EX: 0x80 + 0xFF = 0x7F and not 0x017F
 */
Byte ZPX(Byte *operand);

/**
 * @brief Zero Page Y returns the value at a address calculated by adding the
 * 8-bit value of the zero page address and adding it to the current valeu in
 * the Y register.
 *
 * @note PS: This addressing mode is only used with the instructions LDX and
 * STX.
 *
 */
Byte ZPY(Byte *operand);

/**
 * @brief Addressing mode relative does not return a value and only increments
 * the Program Counter by a specified value.
 *
 * @note PS: This addressing mode is only used by branch instructions.
 *
 */
Byte REL(Byte *operanbd);

/**
 * @brief Absolute addressing mode returns the value at the given 16-bit address
 * specifeid in the program code.
 *
 */
Byte AB0(Byte *operand);

/**
 * @brief Absolute X addressing mode returns the value at a given 16-bit address
 * added to the current value in the X register.
 *
 */
Byte ABX(Byte *operand);

/**
 * @brief Absolute Y addressing mode returns the value at a given 16-bit address
 * added to the current value of the Y register.
 *
 */
Byte ABY(Byte *operand);

/**
 * @brief JMP is the only 6502 instruction to support indirection. The
 * instruction contains a 16 bit address which identifies the location of the
 * least significant byte of another 16 bit memory address which is the real
 * target of the instruction.
 *
 * @note For example if location $0120 contains $FC and location $0121 contains
 * $BA then the instruction JMP ($0120) will cause the next instruction
 * execution to occur at $BAFC (e.g. the contents of $0120 and $0121).
 *
 */
Byte IND(Byte *operand);

/**
 * @brief Indexed indirect addressing is normally used in conjunction with a
 * table of address held on zero page. The address of the table is taken from
 * the instruction and the X register added to it (with zero page wrap around)
 * to give the location of the least significant byte of the target address.
 *
 */
Byte IIX(Byte *operand);

/**
 * @brief Indirect indirect addressing is the most common indirection mode used
 * on the 6502. In instruction contains the zero page location of the least
 * significant byte of 16 bit address. The Y register is dynamically added to
 * this value to generated the actual target address for operation.
 *
 */
Byte IIY(Byte *operand);

#endif /* INC_INSTRUCTION_H */
