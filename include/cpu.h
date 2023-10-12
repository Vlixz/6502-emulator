#ifndef INC_CPU_H
#define INC_CPU_H

#include "common.h"

/* 6502 supports a 256 byte stack located between 0x0100 and 0x01FF. */

#define BASE_STACK 0x0100
#define START_OF_STACK 0xFF
#define END_OF_STACK 0x00

/* First 256 byte page of memory is referred to the 'Zero Page' and is focused on creating special addressing modes that result in shorter instructions cycles. */

#define START_ZERO_PAGE 0x0000
#define END_ZERO_PAGE 0x00FF

/**
 * 6502 defenition (registers, etc...);
 * Definitions of all the different instructions;
 *
 * Sources:
 * http://www.6502.org/users/obelisk/6502/registers.html
 *
 */

typedef struct
{

    /**
     * Program counter
     *
     * The program counter is a 16 bit register which points to the next instruction to be executed.
     *
     */
    Word PC;

    /**
     * Stack pointer
     *
     * The processor supports a 256 byte stack located between $0100 and $01FF.
     * The stack pointer is an 8 bit register and holds the low 8 bits of the next free location on the stack.
     *
     * The CPU does not detect if the stack is overflowed by excessive pushing or pulling operations and will most likely result in the program crashing.
     *
     */
    Byte SP;

    /**
     * Accumulator
     *
     * The 8 bit accumulator is used all arithmetic and logical operations (with the exception of increments and decrements).
     *
     */
    Byte A;

    /**
     * Index register X
     *
     * The 8 bit index register is most commonly used to hold counters or offsets for accessing memory.
     * The X register has one special function. It can be used to get a copy of the stack pointer or change its value.
     *
     */
    Byte X;

    /**
     * Index register Y
     *
     * The Y register is similar to the X register in that it is available for holding counter or offsets memory access and supports
     * the same set of memory load, save and compare operations as wells as increments and decrements. It has no special functions.
     *
     */
    Byte Y;

    /**
     * Carry Flag
     *
     * The carry flag is set if the last operation caused an overflow from bit 7 of the result or an underflow from bit 0.
     *
     */
    Byte C : 1;

    /**
     * Zero Flag
     *
     * The zero flag is set if the result of the last operation as was zero.
     */
    Byte Z : 1;

    /**
     * Interrupt Disable
     *
     * The interrupt disable flag is set if the program has executed a 'Set Interrupt Disable' (SEI) instruction.
     * While this flag is set the processor will not respond to interrupts from devices until it is cleared by a 'Clear Interrupt Disable' (CLI) instruction.
     *
     */
    Byte I : 1;

    /**
     * Decimal Mode
     *
     * While the decimal mode flag is set the processor will obey the rules of Binary Coded Decimal (BCD) arithmetic during addition and subtraction.
     * The flag can be explicitly set using 'Set Decimal Flag' (SED) and cleared with 'Clear Decimal Flag' (CLD).
     *
     */
    Byte D : 1;

    /**
     * Break Command
     *
     * The break command bit is set when a BRK instruction has been executed and an interrupt has been generated to process it.
     *
     */
    Byte B : 1;

    /**
     * Overflow Flag
     *
     * The overflow flag is set during arithmetic operations if the result has yielded an invalid 2's complement result
     * (e.g. adding to positive numbers and ending up with a negative result: 64 + 64 => -128). It is determined by looking at the carry between
     * bits 6 and 7 and between bit 7 and the carry flag.
     *
     */
    Byte V : 1;

    /**
     * Negative Flag
     *
     * The negative flag is set if the result of the last operation had bit 7 set to a one.
     *
     */
    Byte N : 1;

    /**
     * Memory of the 6502
     *
     */
    Byte *memory;

} CPU_6502;

// =======================================
//            Addressing Modes
// =======================================

/**
 * Immediate mode returns the value specified during compile time with '#'
 *
 */
Byte AddressingMode_Immediate(const Byte *memory, Word *PC);

/**
 * Zero Page mode returns the value at a specific address in the Zero Page (0x00 -> 0xFF)
 *
 */
Byte AddressingMode_ZeroPage(const Byte *memory, Word *PC);

/**
 * Zero Page X returns the value at a address added to the current value in the X register
 *
 * EX: If the x register contains 0x0F and the given value is 0x80 then the returned value is the
 * value specified at address 0x8F
 *
 * The address calculation wraps around:
 *
 * EX: 0x80 + 0xFF = 0x7F and not 0x017F
 */
Byte AddressingMode_ZeroPageX(const Byte *memory, Word *PC, const Byte X);

/**
 * Zero Page Y returns the value at a address calculated by adding the 8-bit value of the zero
 * page address and adding it to the current valeu in the Y register.
 *
 * PS: This addressing mode is only used with the instructions LDX and STX.
 *
 */
Byte AddressingMode_ZeroPageY(const Byte *memory, Word *PC, const Byte Y);

/**
 * Addressing mode relative does not return a value and only increments the Program Counter by a specified value.
 *
 * PS: This addressing mode is only used by branch instructions.
 *
 */
void AddressingMode_Relative(const Byte *memory, Word *PC, int *cycles);

/**
 * Absolute addressing mode returns the value at the given 16-bit address specifeid in the program code.
 *
 */
Byte AddressingMode_Absolute(const Byte *memory, Word *PC);

/**
 * Absolute X addressing mode returns the value at a given 16-bit address added to the current value in the X register.
 *
 */
Byte AddressingMode_AbsoluteX(const Byte *memory, Word *PC, const Byte X, int *cycles);

/**
 * Absolute Y addressing mode returns the value at a given 16-bit address added to the current value of the Y register.
 *
 */
Byte AddressingMode_AbsoluteY(const Byte *memory, Word *PC, const Byte Y, int *cycles);

/**
 * JMP is the only 6502 instruction to support indirection. The instruction contains a 16 bit address which identifies the
 * location of the least significant byte of another 16 bit memory address which is the real target of the instruction.
 *
 * For example if location $0120 contains $FC and location $0121 contains $BA then the instruction JMP ($0120) will cause the
 * next instruction execution to occur at $BAFC (e.g. the contents of $0120 and $0121).
 *
 */
Byte AddressingMode_Indirect(const Byte *memory, Word *PC);

/**
 * Indexed indirect addressing is normally used in conjunction with a table of address held on zero page.
 * The address of the table is taken from the instruction and the X register added to it (with zero page wrap around) to give the location
 * of the least significant byte of the target address.
 *
 */
Byte AddressingMode_IndexedIndirect(const Byte *memory, Word *PC, Byte X);

/**
 * Indirect indirect addressing is the most common indirection mode used on the 6502.
 * In instruction contains the zero page location of the least significant byte of 16 bit address.
 * The Y register is dynamically added to this value to generated the actual target address for operation.
 *
 */
Byte AddressingMode_IndirectIndexed(const Byte *memory, Word *PC, Byte Y, int *cycles);

// =======================================
//             Add with Carry
// =======================================

/**
 * Add with Carry - Immediate
 *
 * Opcode: 0x69
 * Bytes: 2
 * Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte ADC_IM(CPU_6502 *cpu);

/**
 * Add with Carry - Zero Page
 *
 * Opcode: 0x65
 * Bytes: 2
 * Cycles: 3
 *
 * @return number of cycles executed
 *
 */
Byte ADC_ZP(CPU_6502 *cpu);

/**
 * Add with Carry - Zero Page X
 *
 * Opcode: 0x75
 * Bytes: 2
 * Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte ADC_ZP_X(CPU_6502 *cpu);

/**
 * Add with Carry - Absolute
 *
 * Opcode: 0x6D
 * Bytes: 3
 * Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte ADC_AB(CPU_6502 *cpu);

/**
 * Add with Carry - Absolute X
 *
 * Opcode: 0x7D
 * Bytes: 3
 * Cycles: 4 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte ADC_AB_X(CPU_6502 *cpu);

/**
 * Add with Carry - Absolute Y
 *
 * Opcode: 0x79
 * Bytes: 3
 * Cycles: 4 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte ADC_AB_Y(CPU_6502 *cpu);

/**
 * Add with Carry - Indirect X
 *
 * Opcode: 0x61
 * Bytes: 2
 * Cycles: 6
 *
 * @return number of cycles executed
 *
 */
Byte ADC_IN_X(CPU_6502 *cpu);

/**
 * Add with Carry - Indirect X
 *
 * Opcode: 0x71
 * Bytes: 2
 * Cycles: 5 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte ADC_IN_Y(CPU_6502 *cpu);

// =======================================
//             Logical AND
// =======================================

/**
 * Logical AND - Immediate
 *
 * Opcode: 0x29
 * Bytes: 2
 * Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte AND_IM(CPU_6502 *cpu);

/**
 * Logical AND - Zero Page
 *
 * Opcode: 0x25
 * Bytes: 2
 * Cycles: 3
 *
 * @return number of cycles executed
 *
 */
Byte AND_ZP(CPU_6502 *cpu);

/**
 * Logical AND - Zero Page X
 *
 * Opcode: 0x35
 * Bytes: 2
 * Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte AND_ZP_X(CPU_6502 *cpu);

/**
 * Logical AND - Absolute
 *
 * Opcode: 0x2D
 * Bytes: 3
 * Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte AND_AB(CPU_6502 *cpu);

/**
 * Logical AND - Absolute X
 *
 * Opcode: 0x3D
 * Bytes: 3
 * Cycles: 4 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte AND_AB_X(CPU_6502 *cpu);

/**
 * Logical AND - Absolute Y
 *
 * Opcode: 0x39
 * Bytes: 3
 * Cycles: 4 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte AND_AB_Y(CPU_6502 *cpu);

/**
 * Logical AND - Indirect X
 *
 * Opcode: 0x21
 * Bytes: 2
 * Cycles: 6
 *
 * @return number of cycles executed
 *
 */
Byte AND_IN_X(CPU_6502 *cpu);

/**
 * Logical AND - Indirect Y
 *
 * Opcode: 0x31
 * Bytes: 2
 * Cycles: 5 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte AND_IN_Y(CPU_6502 *cpu);

// =======================================
//        Arithmatic Shift Left
// =======================================

/**
 * Arithmetic Shift Left - Accumulator
 *
 * Opcode: 0x0A
 * Bytes: 1
 * Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte ASL_AC(CPU_6502 *cpu);

/**
 * Arithmetic Shift Left - Zero Page
 *
 * Opcode: 0x06
 * Bytes: 2
 * Cycles: 5
 *
 * @return number of cycles executed
 *
 */
Byte ASL_ZP(CPU_6502 *cpu);

/**
 * Arithmetic Shift Left - Zero Page X
 *
 * Opcode: 0x16
 * Bytes: 2
 * Cycles: 6
 *
 * @return number of cycles executed
 *
 */
Byte ASL_ZP_X(CPU_6502 *cpu);

/**
 * Arithmetic Shift Left - Absolute
 *
 * Opcode: 0x0E
 * Bytes: 3
 * Cycles: 6
 *
 * @return number of cycles executed
 *
 */
Byte ASL_AB(CPU_6502 *cpu);

/**
 * Arithmetic Shift Left - Absolute
 *
 * Opcode: 0x1E
 * Bytes: 3
 * Cycles: 7
 *
 * @return number of cycles executed
 *
 */
Byte ASL_AB_X(CPU_6502 *cpu);

// =======================================
//         Branch if Carry Clear
// =======================================

/**
 * Branch if Carry Clear - Relative
 *
 * Opcode: 0x90
 * Bytes: 2
 * Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BCC_RE(CPU_6502 *cpu);

// =======================================
//          Branch if Carry Set
// =======================================

/**
 * Branch if Carry Set - Relative
 *
 * Opcode: 0xB0
 * Bytes: 2
 * Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BCS_RE(CPU_6502 *cpu);

// =======================================
//           Branch if Equal
// =======================================

/**
 * Branch if Equal - Relative
 *
 * Opcode: 0xF0
 * Bytes: 2
 * Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BEQ_RE(CPU_6502 *cpu);

// =======================================
//              Bit Tests
// =======================================

/**
 * Bit Test - Zero Page
 *
 * Opcode: 0x24
 * Bytes: 2
 * Cycles: 3
 *
 * @return number of cycles executed
 *
 */
Byte BIT_ZP(CPU_6502 *cpu);

/**
 * Bit Test - Absolute
 *
 * Opcode: 0x2C
 * Bytes: 2
 * Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte BIT_AB(CPU_6502 *cpu);

// =======================================
//            Branch if Minus
// =======================================

/**
 * Branch if Minus - Relative
 *
 * Opcode: 0x30
 * Bytes: 2
 * Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BMI_RE(CPU_6502 *cpu);

// =======================================
//            Branch if Not Equal
// =======================================

/**
 * Branch if Not Equal - Relative
 *
 * Opcode: 0xD0
 * Bytes: 2
 * Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BNE_RE(CPU_6502 *cpu);

// =======================================
//            Branch if Positive
// =======================================

/**
 * Branch if Positive - Relative
 *
 * Opcode: 0x10
 * Bytes: 2
 * Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BPL_RE(CPU_6502 *cpu);

// =======================================
//       Branch if Overflow Clear
// =======================================

/**
 * Branch if OVerflow Clear - Relative
 *
 * Opcode: 0x50
 * Bytes: 2
 * Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BVC_RE(CPU_6502 *cpu);

// =======================================
//       Branch if Overflow Set
// =======================================

/**
 * Branch if Overflow Set - Relative
 *
 * Opcode: 0x70
 * Bytes: 2
 * Cycles: 2 (+1 if branch successfull, +2 if to a new page)
 *
 * @return number of cycles executed
 *
 */
Byte BVS_RE(CPU_6502 *cpu);

// =======================================
//            Clear Carry Flag
// =======================================

/**
 * Clear Carry Flag - Implied
 *
 * Opcode: 0x18
 * Bytes: 2
 * Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte CLC_IP(CPU_6502 *cpu);

// =======================================
//          Clear Decimal Mode
// =======================================

/**
 * Clear Decimal Mode - Implied
 *
 * Opcode: 0xD8
 * Bytes: 2
 * Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte CLD_IP(CPU_6502 *cpu);

// =======================================
//        Clear Interrupt Disable
// =======================================

/**
 * Clear Interrupt Disable - Implied
 *
 * Opcode: 0x58
 * Bytes: 2
 * Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte CLI_IP(CPU_6502 *cpu);

// =======================================
//          Clear Overflow Flag
// =======================================

/**
 * Clear Overflow Flag - Implied
 *
 * Opcode: 0xB8
 * Bytes: 2
 * Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte CLV_IP(CPU_6502 *cpu);

// =======================================
//            Set Carry Flag
// =======================================

/**
 * Set Carry Flag - Implied
 *
 * Opcode: 0x38
 * Bytes: 2
 * Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte SEC_IP(CPU_6502 *cpu);

// =======================================
//           Set Decimal Mode
// =======================================

/**
 * Set Decimal Mode - Implied
 *
 * Opcode: 0xF8
 * Bytes: 2
 * Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte SED_IP(CPU_6502 *cpu);

// =======================================
//           Set Interrupt Disable
// =======================================

/**
 * Set Interrupt Disable - Implied
 *
 * Opcode: 0x78
 * Bytes: 2
 * Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte SEI_IP(CPU_6502 *cpu);

// =======================================
//       Transfer Accumulator to X
// =======================================

/**
 * Transfer Accumulator to X - Implied
 *
 * Opcode: 0xAA
 * Bytes: 2
 * Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte TAX_IP(CPU_6502 *cpu);

// =======================================
//       Transfer Accumulator to Y
// =======================================

/**
 * Transfer Accumulator to Y - Implied
 *
 * Opcode: 0xA8
 * Bytes: 2
 * Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte TAY_IP(CPU_6502 *cpu);

// =======================================
//       Transfer X to Accumulator
// =======================================

/**
 * Transfer X to Accumulator - Implied
 *
 * Opcode: 0x8A
 * Bytes: 2
 * Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte TXA_IP(CPU_6502 *cpu);

// =======================================
//       Transfer Y to Accumulator
// =======================================

/**
 * Transfer Y to Accumulator - Implied
 *
 * Opcode: 0x98
 * Bytes: 2
 * Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte TYA_IP(CPU_6502 *cpu);

// =======================================
//            Load Accumulator
// =======================================

/**
 * Load Accumulator - Immediate
 *
 * Opcode: 0xA9
 * Bytes: 2
 * Cycles: 2
 *
 * @return number of cycles executed
 *
 */
Byte LDA_IM(CPU_6502 *cpu);

/**
 * Load Accumulator - Zero Page
 *
 * Opcode: 0xA5
 * Bytes: 2
 * Cycles: 3
 *
 * @return number of cycles executed
 *
 */
Byte LDA_ZP(CPU_6502 *cpu);

/**
 * Load Accumulator - Zero Page X
 *
 * Opcode: 0xB5
 * Bytes: 2
 * Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte LDA_ZP_X(CPU_6502 *cpu);

/**
 * Load Accumulator - Absolute
 *
 * Opcode: 0xAD
 * Bytes: 3
 * Cycles: 4
 *
 * @return number of cycles executed
 *
 */
Byte LDA_AB(CPU_6502 *cpu);

/**
 * Load Accumulator - Absolute X
 *
 * Opcode: 0xBD
 * Bytes: 3
 * Cycles: 4 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte LDA_AB_X(CPU_6502 *cpu);

/**
 * Load Accumulator - Absolute Y
 *
 * Opcode: 0xB9
 * Bytes: 3
 * Cycles: 4 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte LDA_AB_Y(CPU_6502 *cpu);

/**
 * Load Accumulator - Indirect X
 *
 * Opcode: 0xA1
 * Bytes: 2
 * Cycles: 6
 *
 * @return number of cycles executed
 *
 */
Byte LDA_IN_X(CPU_6502 *cpu);

/**
 * Load Accumulator - Indirect Y
 *
 * Opcode: 0xB1
 * Bytes: 2
 * Cycles: 5 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte LDA_IN_Y(CPU_6502 *cpu);

#endif /* INC_CPU_H */