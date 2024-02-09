#include <stdio.h>
#include <stdlib.h>

#include "6502.h"
#include "cpu.h"
#include "debug.h"
#include "memory.h"
#include "instruction.h"


/**
 * Runs the 6502 functional test created by Klaus Dormann 
 *      GitHub: https://github.com/Klaus2m5/6502_65C02_functional_tests
 * 
 * decimal mode is disabled.
 * 
 * The test is successful if the program counter reaches 0x336D.
 * 
*/

#define TEST_SUCCESS_ADDRESS 0x336D

const char *BIN_TEST_FILE =
    "../../examples/6502_functional_test.bin";

int main(int argc, char **argv) {

    int result = mem_read_bin_file(BIN_TEST_FILE);

    if (result != 0) {
        printf("Error reading file\n");
        return EXIT_FAILURE;
    }

    printf("File read running test.\n");

    em6502_reset(&cpu, 0x0400);

    execution_information info;

    while(1) {
        info = em6502_execute_instruction();

        if (info.PC == TEST_SUCCESS_ADDRESS) {
            printf("Test passed\n");
            return EXIT_SUCCESS;
        }
    }

    printf("Test failed\n");
    return EXIT_FAILURE;
}
