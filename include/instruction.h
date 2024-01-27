#ifndef INC_INSTRUCTION_H
#define INC_INSTRUCTION_H

#include "common.h"
#include <stdint.h>

typedef struct {
    char *name;

    Byte (*operation)(void);
    Byte (*addrmode)(void);

    uint8_t cycles;
} instruction;

// =======================================
//             Instructions
// =======================================

Byte ADC();
Byte AND();
Byte ASL();
Byte BCC();
Byte BCS();
Byte BEQ();
Byte BIT();
Byte BMI();
Byte BNE();
Byte BPL();
Byte BRK();
Byte BVC();
Byte BVS();
Byte CLC();

Byte CLD();
Byte CLI();
Byte CLV();
Byte CMP();
Byte CPX();
Byte CPY();
Byte DEC();
Byte DEX();
Byte DEY();
Byte EOR();
Byte INC();
Byte INX();
Byte INY();
Byte JMP();

Byte JSR();
Byte LDA();
Byte LDX();
Byte LDY();
Byte LSR();
Byte NOP();
Byte ORA();
Byte PHA();
Byte PHP();
Byte PLA();
Byte PLP();
Byte ROL();
Byte ROR();
Byte RTI();

Byte RTS();
Byte SBC();
Byte SEC();
Byte SED();
Byte SEI();
Byte STA();
Byte STX();
Byte STY();
Byte TAX();
Byte TAY();
Byte TSX();
Byte TXA();
Byte TXS();
Byte TYA();

Byte XXX();

// =======================================
//            Addressing Modes
// =======================================

Byte IMP();
Byte ACC();

/**
 * @brief Immediate mode returns the value specified during compile time with
 * '#'
 *
 */
Byte IMM();

/**
 * @brief Zero Page mode returns the value at a specific address in the Zero
 * Page (0x00 -> 0xFF)
 *
 */
Byte ZP0();

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
Byte ZPX();

/**
 * @brief Zero Page Y returns the value at a address calculated by adding the
 * 8-bit value of the zero page address and adding it to the current valeu in
 * the Y register.
 *
 * @note PS: This addressing mode is only used with the instructions LDX and
 * STX.
 *
 */
Byte ZPY();

/**
 * @brief Addressing mode relative does not return a value and only increments
 * the Program Counter by a specified value.
 *
 * @note PS: This addressing mode is only used by branch instructions.
 *
 */
Byte REL();

/**
 * @brief Absolute addressing mode returns the value at the given 16-bit address
 * specifeid in the program code.
 *
 */
Byte AB0();

/**
 * @brief Absolute X addressing mode returns the value at a given 16-bit address
 * added to the current value in the X register.
 *
 */
Byte ABX();

/**
 * @brief Absolute Y addressing mode returns the value at a given 16-bit address
 * added to the current value of the Y register.
 *
 */
Byte ABY();

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
Byte IND();

/**
 * @brief Indexed indirect addressing is normally used in conjunction with a
 * table of address held on zero page. The address of the table is taken from
 * the instruction and the X register added to it (with zero page wrap around)
 * to give the location of the least significant byte of the target address.
 *
 */
Byte IIX();

/**
 * @brief Indirect indirect addressing is the most common indirection mode used
 * on the 6502. In instruction contains the zero page location of the least
 * significant byte of 16 bit address. The Y register is dynamically added to
 * this value to generated the actual target address for operation.
 *
 */
Byte IIY();
#endif /* INC_INSTRUCTION_H */
