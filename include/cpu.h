#ifndef INC_CPU_H
#define INC_CPU_H

#include "common.h"
#include "memory.h"

/* 6502 supports a 256 byte stack located between 0x0100 and 0x01FF. */

#define BASE_STACK 0x0100
#define START_OF_STACK 0xFF
#define END_OF_STACK 0x00

/* First 256 byte page of memory is referred to the 'Zero Page' and is focused on creating special addressing modes that result in shorter instructions cycles. */

#define START_ZERO_PAGE 0x0000
#define END_ZERO_PAGE 0x00FF

/**
 * 6502 defenition (registers, etc.);
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
    Byte AC;

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
     * This condition is set during arithmetic, comparison and during logical shifts.
     * It can be explicitly set using the 'Set Carry Flag' (SEC) instruction and cleared with 'Clear Carry Flag' (CLC).
     *
     */
    Byte CF : 1;

    /**
     * Zero Flag
     *
     * The zero flag is set if the result of the last operation as was zero.
     */
    Byte ZF : 1;

    /**
     * Interrupt Disable
     *
     * The interrupt disable flag is set if the program has executed a 'Set Interrupt Disable' (SEI) instruction.
     * While this flag is set the processor will not respond to interrupts from devices until it is cleared by a 'Clear Interrupt Disable' (CLI) instruction.
     *
     */
    Byte ID : 1;

    /**
     * Decimal Mode
     *
     * While the decimal mode flag is set the processor will obey the rules of Binary Coded Decimal (BCD) arithmetic during addition and subtraction.
     * The flag can be explicitly set using 'Set Decimal Flag' (SED) and cleared with 'Clear Decimal Flag' (CLD).
     *
     */
    Byte DM : 1;

    /**
     * Break Command
     *
     * The break command bit is set when a BRK instruction has been executed and an interrupt has been generated to process it.
     *
     */
    Byte BC : 1;

    /**
     * Overflow Flag
     *
     * The overflow flag is set during arithmetic operations if the result has yielded an invalid 2's complement result
     * (e.g. adding to positive numbers and ending up with a negative result: 64 + 64 => -128). It is determined by looking at the carry between
     * bits 6 and 7 and between bit 7 and the carry flag.
     *
     */
    Byte OF : 1;

    /**
     * Negative Flag
     *
     * The negative flag is set if the result of the last operation had bit 7 set to a one.
     *
     */
    Byte NF : 1;

    /**
     * Memory of the 6502
     *
     */
    Word *memory;

} CPU_6502;

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
 */
Byte ADC_IM(CPU_6502 cpu);

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
Byte ADC_ZP(CPU_6502 cpu);

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
Byte ADC_ZP_X(CPU_6502 cpu);

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
Byte ADC_AB(CPU_6502 cpu);

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
Byte ADC_AB_X(CPU_6502 cpu);

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
Byte ADC_AB_Y(CPU_6502 cpu);

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
Byte ADC_IN_X(CPU_6502 cpu);

/**
 * Add with Carry - Indirect X
 *
 * Opcode: 0x71
 * Bytes: 2
 * Cycles: 6 (+1 if page crossed)
 *
 * @return number of cycles executed
 *
 */
Byte ADC_IN_Y(CPU_6502 cpu);

#endif /* INC_CPU_H */