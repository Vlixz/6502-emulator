#include <stdio.h>
#include <stdlib.h>

#include "6502.h"
#include "debug.h"
#include "memory.h"

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

/**
 * To avoid a infinite loop in GitHub actions, set a maximum number of executed instructions.
 * 
 * The number of executed instructions when successful is around 26 765 880.
*/
#define MAX_EXECUTED_INSTRUCTIONS 30000000 


char *BIN_TEST_FILE = 
        "../../bin_files/6502_functional_test.bin";

int main(int argc, char **argv) {

    char* file_path = (argc != 2) ? BIN_TEST_FILE : argv[1];

    int result = mem_read_bin_file(file_path);

    if (result != 0) {
        printf("Error reading file\n");
        return EXIT_FAILURE;
    }

    printf("File read running test.\n");

    uint64_t executed_instructions = 0;
    em6502_reset(&cpu, 0x0400);

    execution_information info;

    while(1) {
        info = em6502_execute_instruction();
        executed_instructions++;

        if (info.lastPC == TEST_SUCCESS_ADDRESS) {
            printf("Test passed\n");
            return EXIT_SUCCESS;
        }

        if (executed_instructions > MAX_EXECUTED_INSTRUCTIONS) {
            printf("Test failed\n");
            return EXIT_FAILURE;
        }
    }
}
