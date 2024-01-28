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
    Byte memory[MEMORY_WORD_COUNT_6502];

} CPU_6502;

extern CPU_6502 cpu;

Byte mem_fetch(const Word address);
void mem_write(const Word address, const Word value);

void stack_push_byte(const Byte value);
void stack_push_word(const Word value);

Byte stack_pop_byte();
Word stack_pop_word();

void stack_push_ps();
void stack_pop_ps();

#endif /* INC_CPU_H */
