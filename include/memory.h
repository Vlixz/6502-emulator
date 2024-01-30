#ifndef INC_MEMORY_H
#define INC_MEMORY_H

#include <stdlib.h>
#include <stdio.h>
#include "common.h"

/**
 * @brief Set all memory to 0.
 * 
*/
void mem_reset(void);

/**
 * @brief Fetches a byte from memory.
 * 
 * @param address The address to fetch the byte from.
 * 
 * @return The byte at the specified address.
 * 
 * @note This function also increments the program counter if the address being read from
 * is the same as the program counter.
 * 
*/
Byte mem_fetch(const Word address);

/**
 * @brief Writes a byte to memory.
 * 
 * @param address The address to write the byte to.
 * @param value The byte to write.
 * 
*/
void mem_write(const Word address, const Word value);

/**
 * @brief Pushes a byte to the stack.
 * 
 * @param value The byte to push to the stack.
 * 
*/
void stack_push_byte(const Byte value);

/**
 * @brief Pushes a word to the stack.
 * 
 * @param value The word to push to the stack.
 * 
 * @note The word is pushed to the stack in little endian format.
 * 
*/
void stack_push_word(const Word value);

/**
 * @brief Pops a byte from the stack.
 * 
 * @return The byte popped from the stack.
 * 
*/
Byte stack_pop_byte();

/**
 * @brief Pops a word from the stack.
 * 
 * @return The word popped from the stack.
 * 
*/
Word stack_pop_word();

/**
 * @brief Pushes the processor status register to the stack.
 * 
 * @note Layout of the processor status register:
 * 0 - Carry Flag
 * 1 - Zero Flag
 * 2 - Interrupt Disable
 * 3 - Decimal Mode
 * 4 - Break Command
 * 5 - Unused
 * 6 - Overflow Flag
 * 7 - Negative Flag
 * 
*/
void stack_push_ps();

/**
 * @brief Pops the processor status register from the stack.
 * 
*/
void stack_pop_ps();

/**
 * @brief Reads a binary file into memory.
 * 
 * @param filename The name of the file to read.
 * 
 * @return 0 if the file was read successfully, 1 otherwise.
 * 
*/
int mem_read_bin_file(const char *filename);

#endif /* INC_MEMORY_H */