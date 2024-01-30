#ifndef INC_INSTRUCTION_H
#define INC_INSTRUCTION_H

#include "common.h"
#include <stdint.h>

typedef struct {
    char *name;

    uint8_t (*operation)(Word absolute_address);
    uint8_t (*addrmode)(Word *absolute_address);

    uint8_t cycles;
} instruction;

instruction get_instruction(Byte opcode);

// =======================================
//             Instructions
// =======================================

uint8_t ins_execute();

uint8_t ADC(Word absolute_address);
uint8_t AND(Word absolute_address);
uint8_t ASL(Word absolute_address);
uint8_t BCC(Word absolute_address);
uint8_t BCS(Word absolute_address);
uint8_t BEQ(Word absolute_address);
uint8_t BIT(Word absolute_address);
uint8_t BMI(Word absolute_address);
uint8_t BNE(Word absolute_address);
uint8_t BPL(Word absolute_address);
uint8_t BRK(Word absolute_address);
uint8_t BVC(Word absolute_address);
uint8_t BVS(Word absolute_address);
uint8_t CLC(Word absolute_address);

uint8_t CLD(Word absolute_address);
uint8_t CLI(Word absolute_address);
uint8_t CLV(Word absolute_address);
uint8_t CMP(Word absolute_address);
uint8_t CPX(Word absolute_address);
uint8_t CPY(Word absolute_address);
uint8_t DEC(Word absolute_address);
uint8_t DEX(Word absolute_address);
uint8_t DEY(Word absolute_address);
uint8_t EOR(Word absolute_address);
uint8_t INC(Word absolute_address);
uint8_t INX(Word absolute_address);
uint8_t INY(Word absolute_address);
uint8_t JMP(Word absolute_address);

uint8_t JSR(Word absolute_address);
uint8_t LDA(Word absolute_address);
uint8_t LDX(Word absolute_address);
uint8_t LDY(Word absolute_address);
uint8_t LSR(Word absolute_address);
uint8_t NOP(Word absolute_address);
uint8_t ORA(Word absolute_address);
uint8_t PHA(Word absolute_address);
uint8_t PHP(Word absolute_address);
uint8_t PLA(Word absolute_address);
uint8_t PLP(Word absolute_address);
uint8_t ROL(Word absolute_address);
uint8_t ROR(Word absolute_address);
uint8_t RTI(Word absolute_address);

uint8_t RTS(Word absolute_address);
uint8_t SBC(Word absolute_address);
uint8_t SEC(Word absolute_address);
uint8_t SED(Word absolute_address);
uint8_t SEI(Word absolute_address);
uint8_t STA(Word absolute_address);
uint8_t STX(Word absolute_address);
uint8_t STY(Word absolute_address);
uint8_t TAX(Word absolute_address);
uint8_t TAY(Word absolute_address);
uint8_t TSX(Word absolute_address);
uint8_t TXA(Word absolute_address);
uint8_t TXS(Word absolute_address);
uint8_t TYA(Word absolute_address);

uint8_t XXX(Word absolute_address);

/**
 * =======================================
 *           Addressing Modes
 * =======================================
 * 
 * @brief Addressing modes are the various ways that the CPU can access data.
 * The addressing mode is determined by the opcode of the instruction.
 * 
 * @note The 6502 has 13 addressing modes addressing a total of 128 different
 * opcodes. The opcodes are listed below with number of cycles, number of bytes
 * 
 * ! each addressing mode function only returns the address of the operand.
 * Each instruction function is responsible for getting the operand at the given address.
*/

/**
 * @brief For many 6502 instructions the operand is implied in the instruction. 
 * For example CLD (CLear Decimal) sets the decimal flag to 0. There is no
 * additional value required for this instruction.
 *
 */
uint8_t IMP(Word *address);

/**
 * @brief ACC : Accumulator addressing mode is only used when a instructions operates on the 
 * accumulator (A) register. The instruction's operand is the accumulator itself.
 * 
 * Just like IMP this addressing mode does not set any absolute address.
 *
 */
uint8_t ACC(Word *address);

/**
 * @brief IMM : Immediate addressing sets the address to the value of the current PC.
 *
 */
uint8_t IMM(Word *address);

/**
 * @brief ZP0 : Zero Page addressing sets the the address to the value of the next byte in memory. 
 * This byte points to a special page in memory - ZeroPage (0x00 -> 0xFF).
 * 
 */
uint8_t ZP0(Word *address);

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
uint8_t ZPX(Word *absolute_address);

/**
 * @brief Zero Page Y returns the value at a address calculated by adding the
 * 8-bit value of the zero page address and adding it to the current valeu in
 * the Y register.
 *
 * @note PS: This addressing mode is only used with the instructions LDX and
 * STX.
 *
 */
uint8_t ZPY(Word *absolute_address);

/**
 * @brief Addressing mode relative does not return a value and only increments
 * the Program Counter by a specified value.
 *
 * @note PS: This addressing mode is only used by branch instructions.
 *
 */
uint8_t REL(Word *operanbd);

/**
 * @brief Absolute addressing mode returns the value at the given 16-bit address
 * specifeid in the program code.
 *
 */
uint8_t AB0(Word *absolute_address);

/**
 * @brief Absolute X addressing mode returns the value at a given 16-bit address
 * added to the current value in the X register.
 *
 */
uint8_t ABX(Word *absolute_address);

/**
 * @brief Absolute Y addressing mode returns the value at a given 16-bit address
 * added to the current value of the Y register.
 *
 */
uint8_t ABY(Word *absolute_address);

/**
 * @brief JMP is the only 6502 instruction to support indirection. The
 * instruction contains a 16 bit address which identifies the location of the
 * least significant uint8_t of another 16 bit memory address which is the real
 * target of the instruction.
 *
 * @note For example if location $0120 contains $FC and location $0121 contains
 * $BA then the instruction JMP ($0120) will cause the next instruction
 * execution to occur at $BAFC (e.g. the contents of $0120 and $0121).
 *
 */
uint8_t IND(Word *absolute_address);

/**
 * @brief Indexed indirect addressing is normally used in conjunction with a
 * table of address held on zero page. The address of the table is taken from
 * the instruction and the X register added to it (with zero page wrap around)
 * to give the location of the least significant byte of the target address.
 *
 */
uint8_t IIX(Word *absolute_address);

/**
 * @brief Indirect indirect addressing is the most common indirection mode used
 * on the 6502. In instruction contains the zero page location of the least
 * significant byte of 16 bit address. The Y register is dynamically added to
 * this value to generated the actual target address for operation.
 *
 */
uint8_t IIY(Word *absolute_address);

#endif /* INC_INSTRUCTION_H */
