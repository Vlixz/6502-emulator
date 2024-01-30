#ifndef INC_CPU_H
#define INC_CPU_H

#include <stdint.h>

#include "common.h"

/**
 * 6502 reset values.
 * 
*/

#define RESET_VALUE_A 0
#define RESET_VALUE_X 0
#define RESET_VALUE_Y 0

#define RESET_VALUE_C 0
#define RESET_VALUE_Z 0
#define RESET_VALUE_I 0
#define RESET_VALUE_D 0
#define RESET_VALUE_B 0
#define RESET_VALUE_V 0
#define RESET_VALUE_N 0

#define RESET_VECTOR_LSB 0xFFFC
#define RESET_VECTOR_MSB 0xFFFD

/**
 * 6502 supports a 256 byte stack located between 0x0100 and 0x01FF.
 *
 */

#define STACK_START 0x0100
#define STACK_END 0x01FF

/**
 * First 256 byte page of memory is referred to the 'Zero Page' and is focused
 * on creating special addressing modes that result in shorter instructions
 * cycles.
 *
 */

#define ZERO_PAGE_START 0x0000
#define ZERO_PAGE_END 0x00FF

/**
 * 6502 memory map.
 * 
*/

#define MEMORY_WORD_COUNT_6502 0x10000

/**
 * Processor Status Register (PSR) flags.
 * 
*/

#define PSR_C 0
#define PSR_Z 1
#define PSR_I 2
#define PSR_D 3
#define PSR_B 4
#define PSR_V 6
#define PSR_N 7

/**
 * @brief 6502 defenition.
 *
 * @note Sources:
 * http://www.6502.org/users/obelisk/6502/registers.html
 *
 */
typedef struct {

    /**
     * @brief program counter
     *
     */
    Word PC;

    /**
     * @brief Stack pointer
     *
     */
    Word SP;

    /**
     * @brief Accumulator
     *
     */
    Byte A;

    /**
     * @brief Index register X
     *
     */
    Byte X;

    /**
     * @brief Index register Y
     *
     */
    Byte Y;

    /**
     * @brief Carry Flag
     *
     */
    Byte C : 1;

    /**
     * @brief Zero Flag
     *
     */
    Byte Z : 1;

    /**
     * @brief Interrupt Disable
     *
     */
    Byte I : 1;

    /**
     * @brief Decimal Mode
     *
     */
    Byte D : 1;

    /**
     * @brief Break Command
     *
     */
    Byte B : 1;

    /**
     * @brief Overflow Flag
     *
     */
    Byte V : 1;

    /**
     * @brief Negative Flag
     *
     */
    Byte N : 1;

} central_processing_unit;

extern central_processing_unit cpu;

uint8_t instruction_execute(void);

#endif /* INC_CPU_H */
