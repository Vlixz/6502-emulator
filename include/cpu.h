#ifndef INC_CPU_H
#define INC_CPU_H

#include "common.h"

/**
 * 6502 supports a 256 byte stack located between 0x0100 and 0x01FF.
 *
 */

#define BASE_STACK 0x0100
#define START_OF_STACK 0xFF
#define END_OF_STACK 0x00

/**
 * First 256 byte page of memory is referred to the 'Zero Page' and is focused
 * on creating special addressing modes that result in shorter instructions
 * cycles.
 *
 */

#define START_ZERO_PAGE 0x0000
#define END_ZERO_PAGE 0x00FF

/**
 * @brief 6502 defenition.
 *
 * @note Sources:
 * http://www.6502.org/users/obelisk/6502/registers.html
 *
 */
typedef struct {

    /**
     * @brief  counter
     *
     * @note The program counter is a 16 bit register which points to the next
     * instruction to be executed.
     *
     */
    Word PC;

    /**
     * @brief Stack pointer
     *
     * @note The processor supports a 256 byte stack located between $0100 and
     * $01FF. The stack pointer is an 8 bit register and holds the low 8 bits of
     * the next free location on the stack.
     *
     * The CPU does not detect if the stack is overflowed by excessive pushing
     * or pulling operations and will most likely result in the program
     * crashing.
     *
     */
    Byte SP;

    /**
     * @brief Accumulator
     *
     * @note The 8 bit accumulator is used all arithmetic and logical operations
     * (with the exception of increments and decrements).
     *
     */
    Byte A;

    /**
     * @brief Index register X
     *
     * @note The 8 bit index register is most commonly used to hold counters or
     * offsets for accessing memory. The X register has one special function. It
     * can be used to get a copy of the stack pointer or change its value.
     *
     */
    Byte X;

    /**
     * @brief Index register Y
     *
     * @note The Y register is similar to the X register in that it is available
     * for holding counter or offsets memory access and supports the same set of
     * memory load, save and compare operations as wells as increments and
     * decrements. It has no special functions.
     *
     */
    Byte Y;

    /**
     * @brief Carry Flag
     *
     * @note The carry flag is set if the last operation caused an overflow from
     * bit 7 of the result or an underflow from bit 0.
     *
     */
    Byte C : 1;

    /**
     * @brief Zero Flag
     *
     * @note The zero flag is set if the result of the last operation as was
     * zero.
     *
     */
    Byte Z : 1;

    /**
     * @brief Interrupt Disable
     *
     * @note The interrupt disable flag is set if the program has executed a
     * 'Set Interrupt Disable' (SEI) instruction. While this flag is set the
     * processor will not respond to interrupts from devices until it is cleared
     * by a 'Clear Interrupt Disable' (CLI) instruction.
     *
     */
    Byte I : 1;

    /**
     * @brief Decimal Mode
     *
     * @note While the decimal mode flag is set the processor will obey the
     * rules of Binary Coded Decimal (BCD) arithmetic during addition and
     * subtraction. The flag can be explicitly set using 'Set Decimal Flag'
     * (SED) and cleared with 'Clear Decimal Flag' (CLD).
     *
     */
    Byte D : 1;

    /**
     * @brief Break Command
     *
     * @note The break command bit is set when a BRK instruction has been
     * executed and an interrupt has been generated to process it.
     *
     */
    Byte B : 1;

    /**
     * @brief Overflow Flag
     *
     * @note The overflow flag is set during arithmetic operations if the result
     * has yielded an invalid 2's complement result (e.g. adding to positive
     * numbers and ending up with a negative result: 64 + 64 => -128). It is
     * determined by looking at the carry between bits 6 and 7 and between bit 7
     * and the carry flag.
     *
     */
    Byte V : 1;

    /**
     * @brief Negative Flag
     *
     * @note The negative flag is set if the result of the last operation had
     * bit 7 set to a one.
     *
     */
    Byte N : 1;

    /**
     * @brief Memory of the 6502
     *
     */
    Byte *memory;

} CPU_6502;

// =======================================
//            Addressing Modes
// =======================================

/**
 * @brief Immediate mode returns the value specified during compile time with
 * '#'
 *
 */
Byte AddressingMode_Immediate(const Byte *memory, Word *PC);

/**
 * @brief Zero Page mode returns the value at a specific address in the Zero
 * Page (0x00 -> 0xFF)
 *
 */
Byte AddressingMode_ZeroPage(const Byte *memory, Word *PC);

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
Byte AddressingMode_ZeroPageX(const Byte *memory, Word *PC, const Byte X);

/**
 * @brief Zero Page Y returns the value at a address calculated by adding the
 * 8-bit value of the zero page address and adding it to the current valeu in
 * the Y register.
 *
 * @note PS: This addressing mode is only used with the instructions LDX and
 * STX.
 *
 */
Byte AddressingMode_ZeroPageY(const Byte *memory, Word *PC, const Byte Y);

/**
 * @brief Addressing mode relative does not return a value and only increments
 * the Program Counter by a specified value.
 *
 * @note PS: This addressing mode is only used by branch instructions.
 *
 */
void AddressingMode_Relative(const Byte *memory, Word *PC, int *cycles);

/**
 * @brief Absolute addressing mode returns the value at the given 16-bit address
 * specifeid in the program code.
 *
 */
Byte AddressingMode_Absolute(const Byte *memory, Word *PC);

/**
 * @brief Absolute X addressing mode returns the value at a given 16-bit address
 * added to the current value in the X register.
 *
 */
Byte AddressingMode_AbsoluteX(const Byte *memory, Word *PC, const Byte X,
                              int *cycles);

/**
 * @brief Absolute Y addressing mode returns the value at a given 16-bit address
 * added to the current value of the Y register.
 *
 */
Byte AddressingMode_AbsoluteY(const Byte *memory, Word *PC, const Byte Y,
                              int *cycles);

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
Byte AddressingMode_Indirect(const Byte *memory, Word *PC);

/**
 * @brief Indexed indirect addressing is normally used in conjunction with a
 * table of address held on zero page. The address of the table is taken from
 * the instruction and the X register added to it (with zero page wrap around)
 * to give the location of the least significant byte of the target address.
 *
 */
Byte AddressingMode_IndexedIndirect(const Byte *memory, Word *PC, Byte X);

/**
 * @brief Indirect indirect addressing is the most common indirection mode used
 * on the 6502. In instruction contains the zero page location of the least
 * significant byte of 16 bit address. The Y register is dynamically added to
 * this value to generated the actual target address for operation.
 *
 */
Byte AddressingMode_IndirectIndexed(const Byte *memory, Word *PC, Byte Y,
                                    int *cycles);

// =======================================
//             Add with Carry
// =======================================

/**
 * @brief Add with Carry - Immediate
 *
 * @note Opcode: 0x69
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte ADC_IM(CPU_6502 *cpu);

/**
 * @brief Add with Carry - Zero Page
 *
 * @note Opcode: 0x65
 * @note Bytes: 2
 * @note Cycles: 3
 *
 * @return number of cycles executed
 *
 */
Byte ADC_ZP(CPU_6502 *cpu);

/**
 * @brief Add with Carry - Zero Page X
 *
 * @note Opcode: 0x75
 * @note Bytes: 2
 * @note Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte ADC_ZP_X(CPU_6502 *cpu);

/**
 * @brief Add with Carry - Absolute
 *
 * @note Opcode: 0x6D
 * @note Bytes: 3
 * @note Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte ADC_AB(CPU_6502 *cpu);

/**
 * @brief Add with Carry - Absolute X
 *
 * @note Opcode: 0x7D
 * @note Bytes: 3
 * @note Cycles: 4 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte ADC_AB_X(CPU_6502 *cpu);

/**
 * @brief Add with Carry - Absolute Y
 *
 * @note Opcode: 0x79
 * @note Bytes: 3
 * @note Cycles: 4 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte ADC_AB_Y(CPU_6502 *cpu);

/**
 * @brief Add with Carry - Indirect X
 *
 * @note Opcode: 0x61
 * @note Bytes: 2
 * @note Cycles: 6
 *
 * @return number of cycles executed
 *
 */
Byte ADC_IN_X(CPU_6502 *cpu);

/**
 * @brief Add with Carry - Indirect X
 *
 * @note Opcode: 0x71
 * @note Bytes: 2
 * @note Cycles: 5 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte ADC_IN_Y(CPU_6502 *cpu);

// =======================================
//             Logical AND
// =======================================

/**
 * @brief Logical AND - Immediate
 *
 * @note Opcode: 0x29
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte AND_IM(CPU_6502 *cpu);

/**
 * @brief Logical AND - Zero Page
 *
 * @note Opcode: 0x25
 * @note Bytes: 2
 * @note Cycles: 3
 *
 * @return number of cycles executed
 *
 */
Byte AND_ZP(CPU_6502 *cpu);

/**
 * @brief Logical AND - Zero Page X
 *
 * @note Opcode: 0x35
 * @note Bytes: 2
 * @note Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte AND_ZP_X(CPU_6502 *cpu);

/**
 * @brief Logical AND - Absolute
 *
 * @note Opcode: 0x2D
 * @note Bytes: 3
 * @note Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte AND_AB(CPU_6502 *cpu);

/**
 * @brief Logical AND - Absolute X
 *
 * @note Opcode: 0x3D
 * @note Bytes: 3
 * @note Cycles: 4 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte AND_AB_X(CPU_6502 *cpu);

/**
 * @brief Logical AND - Absolute Y
 *
 * @note Opcode: 0x39
 * @note Bytes: 3
 * @note Cycles: 4 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte AND_AB_Y(CPU_6502 *cpu);

/**
 * @brief Logical AND - Indirect X
 *
 * @note Opcode: 0x21
 * @note Bytes: 2
 * @note Cycles: 6
 *
 * @return number of cycles executed
 *
 */
Byte AND_IN_X(CPU_6502 *cpu);

/**
 * @brief Logical AND - Indirect Y
 *
 * @note Opcode: 0x31
 * @note Bytes: 2
 * @note Cycles: 5 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte AND_IN_Y(CPU_6502 *cpu);

// =======================================
//        Arithmatic Shift Left
// =======================================

/**
 * @brief Arithmetic Shift Left - Accumulator
 *
 * @note Opcode: 0x0A
 * @note Bytes: 1
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte ASL_AC(CPU_6502 *cpu);

/**
 * @brief Arithmetic Shift Left - Zero Page
 *
 * @note Opcode: 0x06
 * @note Bytes: 2
 * @note Cycles: 5
 *
 * @return number of cycles executed
 *
 */
Byte ASL_ZP(CPU_6502 *cpu);

/**
 * @brief Arithmetic Shift Left - Zero Page X
 *
 * @note Opcode: 0x16
 * @note Bytes: 2
 * @note Cycles: 6
 *
 * @return number of cycles executed
 *
 */
Byte ASL_ZP_X(CPU_6502 *cpu);

/**
 * @brief Arithmetic Shift Left - Absolute
 *
 * @note Opcode: 0x0E
 * @note Bytes: 3
 * @note Cycles: 6
 *
 * @return number of cycles executed
 *
 */
Byte ASL_AB(CPU_6502 *cpu);

/**
 * @brief Arithmetic Shift Left - Absolute
 *
 * @note Opcode: 0x1E
 * @note Bytes: 3
 * @note Cycles: 7
 *
 * @return number of cycles executed
 *
 */
Byte ASL_AB_X(CPU_6502 *cpu);

// =======================================
//         Branch if Carry Clear
// =======================================

/**
 * @brief Branch if Carry Clear - Relative
 *
 * @note Opcode: 0x90
 * @note Bytes: 2
 * @note Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BCC_RE(CPU_6502 *cpu);

// =======================================
//          Branch if Carry Set
// =======================================

/**
 * @brief Branch if Carry Set - Relative
 *
 * @note Opcode: 0xB0
 * @note Bytes: 2
 * @note Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BCS_RE(CPU_6502 *cpu);

// =======================================
//           Branch if Equal
// =======================================

/**
 * @brief Branch if Equal - Relative
 *
 * @note Opcode: 0xF0
 * @note Bytes: 2
 * @note Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BEQ_RE(CPU_6502 *cpu);

// =======================================
//              Bit Tests
// =======================================

/**
 * @brief Bit Test - Zero Page
 *
 * @note Opcode: 0x24
 * @note Bytes: 2
 * @note Cycles: 3
 *
 * @return number of cycles executed
 *
 */
Byte BIT_ZP(CPU_6502 *cpu);

/**
 * @brief Bit Test - Absolute
 *
 * @note Opcode: 0x2C
 * @note Bytes: 2
 * @note Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte BIT_AB(CPU_6502 *cpu);

// =======================================
//            Branch if Minus
// =======================================

/**
 * @brief Branch if Minus - Relative
 *
 * @note Opcode: 0x30
 * @note Bytes: 2
 * @note Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BMI_RE(CPU_6502 *cpu);

// =======================================
//            Branch if Not Equal
// =======================================

/**
 * @brief Branch if Not Equal - Relative
 *
 * @note Opcode: 0xD0
 * @note Bytes: 2
 * @note Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BNE_RE(CPU_6502 *cpu);

// =======================================
//            Branch if Positive
// =======================================

/**
 * @brief Branch if Positive - Relative
 *
 * @note Opcode: 0x10
 * @note Bytes: 2
 * @note Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BPL_RE(CPU_6502 *cpu);

// =======================================
//       Branch if Overflow Clear
// =======================================

/**
 * @brief Branch if OVerflow Clear - Relative
 *
 * @note Opcode: 0x50
 * @note Bytes: 2
 * @note Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BVC_RE(CPU_6502 *cpu);

// =======================================
//       Branch if Overflow Set
// =======================================

/**
 * @brief Branch if Overflow Set - Relative
 *
 * @note Opcode: 0x70
 * @note Bytes: 2
 * @note Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BVS_RE(CPU_6502 *cpu);

// =======================================
//            Clear Carry Flag
// =======================================

/**
 * @brief Clear Carry Flag - Implied
 *
 * @note Opcode: 0x18
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte CLC_IP(CPU_6502 *cpu);

// =======================================
//          Clear Decimal Mode
// =======================================

/**
 * @brief Clear Decimal Mode - Implied
 *
 * @note Opcode: 0xD8
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte CLD_IP(CPU_6502 *cpu);

// =======================================
//        Clear Interrupt Disable
// =======================================

/**
 * @brief Clear Interrupt Disable - Implied
 *
 * @note Opcode: 0x58
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte CLI_IP(CPU_6502 *cpu);

// =======================================
//          Clear Overflow Flag
// =======================================

/**
 * @brief Clear Overflow Flag - Implied
 *
 * @note Opcode: 0xB8
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte CLV_IP(CPU_6502 *cpu);

// =======================================
//            Set Carry Flag
// =======================================

/**
 * @brief Set Carry Flag - Implied
 *
 * @note Opcode: 0x38
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte SEC_IP(CPU_6502 *cpu);

// =======================================
//           Set Decimal Mode
// =======================================

/**
 * @brief Set Decimal Mode - Implied
 *
 * @note Opcode: 0xF8
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte SED_IP(CPU_6502 *cpu);

// =======================================
//           Set Interrupt Disable
// =======================================

/**
 * @brief Set Interrupt Disable - Implied
 *
 * @note Opcode: 0x78
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte SEI_IP(CPU_6502 *cpu);

// =======================================
//       Transfer Accumulator to X
// =======================================

/**
 * @brief Transfer Accumulator to X - Implied
 *
 * @note Opcode: 0xAA
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte TAX_IP(CPU_6502 *cpu);

// =======================================
//       Transfer Accumulator to Y
// =======================================

/**
 * @brief Transfer Accumulator to Y - Implied
 *
 * @note Opcode: 0xA8
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte TAY_IP(CPU_6502 *cpu);

// =======================================
//       Transfer X to Accumulator
// =======================================

/**
 * @brief Transfer X to Accumulator - Implied
 *
 * @note Opcode: 0x8A
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte TXA_IP(CPU_6502 *cpu);

// =======================================
//       Transfer Y to Accumulator
// =======================================

/**
 * @brief Transfer Y to Accumulator - Implied
 *
 * @note Opcode: 0x98
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte TYA_IP(CPU_6502 *cpu);

// =======================================
//            Load Accumulator
// =======================================

/**
 * @brief Load Accumulator - Immediate
 *
 * @note Opcode: 0xA9
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte LDA_IM(CPU_6502 *cpu);

/**
 * @brief Load Accumulator - Zero Page
 *
 * @note Opcode: 0xA5
 * @note Bytes: 2
 * @note Cycles: 3
 *
 * @return number of cycles executed
 *
 */
Byte LDA_ZP(CPU_6502 *cpu);

/**
 * @brief Load Accumulator - Zero Page X
 *
 * @note Opcode: 0xB5
 * @note Bytes: 2
 * @note Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte LDA_ZP_X(CPU_6502 *cpu);

/**
 * @brief Load Accumulator - Absolute
 *
 * @note Opcode: 0xAD
 * @note Bytes: 3
 * @note Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte LDA_AB(CPU_6502 *cpu);

/**
 * @brief Load Accumulator - Absolute X
 *
 * @note Opcode: 0xBD
 * @note Bytes: 3
 * @note Cycles: 4 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte LDA_AB_X(CPU_6502 *cpu);

/**
 * @brief Load Accumulator - Absolute Y
 *
 * @note Opcode: 0xB9
 * @note Bytes: 3
 * @note Cycles: 4 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte LDA_AB_Y(CPU_6502 *cpu);

/**
 * @brief Load Accumulator - Indirect X
 *
 * @note Opcode: 0xA1
 * @note Bytes: 2
 * @note Cycles: 6
 *
 * @return number of cycles executed
 *
 */
Byte LDA_IN_X(CPU_6502 *cpu);

/**
 * @brief Load Accumulator - Indirect Y
 *
 * @note Opcode: 0xB1
 * @note Bytes: 2
 * @note Cycles: 5 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte LDA_IN_Y(CPU_6502 *cpu);

// =======================================
//            No Operation
// =======================================

/**
 * @brief No Operation - Implied
 *
 * @note Opcode: 0xEA
 * @note Bytes: 1
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte NOP_IP(CPU_6502 *cpu);

// =======================================
//            Decrement X
// =======================================

/**
 * @brief Decrement X - Implied
 *
 * @note Opcode: 0xCA
 * @note Bytes: 1
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte DEX_IP(CPU_6502 *cpu);

// =======================================
//            Decrement Y
// =======================================

/**
 * @brief Decrement Y - Implied
 *
 * @note Opcode: 0x88
 * @note Bytes: 1
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte DEY_IP(CPU_6502 *cpu);

// =======================================
//            Load X Register
// =======================================

/**
 * @brief Load X Register - Immediate
 *
 * @note Opcode: 0xA2
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte LDX_IM(CPU_6502 *cpu);

/**
 * @brief Load X Register - Zero Page
 *
 * @note Opcode: 0xA6
 * @note Bytes: 2
 * @note Cycles: 3
 *
 * @return number of cycles executed
 *
 */
Byte LDX_ZP(CPU_6502 *cpu);

/**
 * @brief Load X Register - Zero Page Y
 *
 * @note Opcode: 0xB6
 * @note Bytes: 2
 * @note Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte LDX_ZP_Y(CPU_6502 *cpu);

/**
 * @brief Load X Register - Absolute
 *
 * @note Opcode: 0xAE
 * @note Bytes: 3
 * @note Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte LDX_AB(CPU_6502 *cpu);

/**
 * @brief Load X Register - Absolute Y
 *
 * @note Opcode: 0xBE
 * @note Bytes: 3
 * @note Cycles: 4 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte LDX_AB_Y(CPU_6502 *cpu);

// =======================================
//            Load Y Register
// =======================================

/**
 * @brief Load Y Register - Immediate
 *
 * @note Opcode: 0xA0
 * @note Bytes: 2
 * @note Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte LDY_IM(CPU_6502 *cpu);

/**
 * @brief Load Y Register - Zero Page
 *
 * @note Opcode: 0xA4
 * @note Bytes: 2
 * @note Cycles: 3
 *
 * @return number of cycles executed
 *
 */
Byte LDY_ZP(CPU_6502 *cpu);

/**
 * @brief Load Y Register - Zero Page X
 *
 * @note Opcode: 0xB4
 * @note Bytes: 2
 * @note Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte LDY_ZP_Y(CPU_6502 *cpu);

/**
 * @brief Load Y Register - Absolute
 *
 * @note Opcode: 0xAC
 * @note Bytes: 3
 * @note Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte LDY_AB(CPU_6502 *cpu);

/**
 * @brief Load Y Register - Absolute X
 *
 * @note Opcode: 0xBC
 * @note Bytes: 3
 * @note Cycles: 4 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte LDY_AB_X(CPU_6502 *cpu);

#endif /* INC_CPU_H */
