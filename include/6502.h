#ifndef INC_6502_H
#define INC_6502_H

#include "cpu.h"

/**
 * @brief Resets the CPU to its initial state
 *
 */
void em6502_reset(CPU_6502 *cpu);

/**
 * @brief Executes a number of cycles on the CPU
 *
 * @return The number of cycles the CPU executed.
 *
 * @note The number of cycles executed is most likely the same as the number of
 * cycles passed in. However I use this return value to make it easier to write
 * unit tests, as I can check if I correctly calculate the page boundary
 * crossings etc.
 *
 */
int em6502_execute(CPU_6502 *cpu, int cycles);

Byte em6502_execute_instruction(void);

#endif /* INC_6502_H */
