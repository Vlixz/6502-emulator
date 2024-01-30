#ifndef INC_INSTRUCTION_H
#define INC_INSTRUCTION_H

#include "common.h"
#include <stdint.h>

typedef struct {
    char *name;

    uint8_t (*operation)(Word address);
    uint8_t (*addrmode)(Word *address);

    uint8_t cycles;
} instruction;

instruction get_instruction(Byte opcode);

// =======================================
//             Instructions
// =======================================

uint8_t ins_execute();

uint8_t ADC(Word address);
uint8_t AND(Word address);
uint8_t ASL(Word address);
uint8_t BCC(Word address);
uint8_t BCS(Word address);
uint8_t BEQ(Word address);
uint8_t BIT(Word address);
uint8_t BMI(Word address);
uint8_t BNE(Word address);
uint8_t BPL(Word address);
uint8_t BRK(Word address);
uint8_t BVC(Word address);
uint8_t BVS(Word address);
uint8_t CLC(Word address);

uint8_t CLD(Word address);
uint8_t CLI(Word address);
uint8_t CLV(Word address);
uint8_t CMP(Word address);
uint8_t CPX(Word address);
uint8_t CPY(Word address);
uint8_t DEC(Word address);
uint8_t DEX(Word address);
uint8_t DEY(Word address);
uint8_t EOR(Word address);
uint8_t INC(Word address);
uint8_t INX(Word address);
uint8_t INY(Word address);
uint8_t JMP(Word address);

uint8_t JSR(Word address);
uint8_t LDA(Word address);
uint8_t LDX(Word address);
uint8_t LDY(Word address);
uint8_t LSR(Word address);
uint8_t NOP(Word address);
uint8_t ORA(Word address);
uint8_t PHA(Word address);
uint8_t PHP(Word address);
uint8_t PLA(Word address);
uint8_t PLP(Word address);
uint8_t ROL(Word address);
uint8_t ROR(Word address);
uint8_t RTI(Word address);

uint8_t RTS(Word address);
uint8_t SBC(Word address);
uint8_t SEC(Word address);
uint8_t SED(Word address);
uint8_t SEI(Word address);
uint8_t STA(Word address);
uint8_t STX(Word address);
uint8_t STY(Word address);
uint8_t TAX(Word address);
uint8_t TAY(Word address);
uint8_t TSX(Word address);
uint8_t TXA(Word address);
uint8_t TXS(Word address);
uint8_t TYA(Word address);

uint8_t XXX(Word address);

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
uint8_t ZPX(Word *address);

/**
 * @brief Zero Page Y returns the value at a address calculated by adding the
 * 8-bit value of the zero page address and adding it to the current valeu in
 * the Y register.
 *
 * @note PS: This addressing mode is only used with the instructions LDX and
 * STX.
 *
 */
uint8_t ZPY(Word *address);

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
uint8_t AB0(Word *address);

/**
 * @brief Absolute X addressing mode returns the value at a given 16-bit address
 * added to the current value in the X register.
 *
 */
uint8_t ABX(Word *address);

/**
 * @brief Absolute Y addressing mode returns the value at a given 16-bit address
 * added to the current value of the Y register.
 *
 */
uint8_t ABY(Word *address);

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
uint8_t IND(Word *address);

/**
 * @brief Indexed indirect addressing is normally used in conjunction with a
 * table of address held on zero page. The address of the table is taken from
 * the instruction and the X register added to it (with zero page wrap around)
 * to give the location of the least significant byte of the target address.
 *
 */
uint8_t IIX(Word *address);

/**
 * @brief Indirect indirect addressing is the most common indirection mode used
 * on the 6502. In instruction contains the zero page location of the least
 * significant byte of 16 bit address. The Y register is dynamically added to
 * this value to generated the actual target address for operation.
 *
 */
uint8_t IIY(Word *address);

#endif /* INC_INSTRUCTION_H */
