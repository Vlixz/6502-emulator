#include <stdio.h>
#include <stdlib.h>

#include "6502.h"
#include "cpu.h"
#include "memory.h"
#include "instruction.h"

const char *BIN_TEST_FILE =
    "/home/vlixz/Documents/6502_functional_test.bin";

int main(int argc, char **argv) {

    int result = readBinaryFile(BIN_TEST_FILE, cpu.memory, sizeof(cpu.memory));

    if (result != 0)
        return EXIT_FAILURE;

    printf("Successfully read file into cpu memory\n");

    em6502_reset(&cpu);

    while (1) {
        char input = getchar();

        switch (input) {
        case 'q':
            return EXIT_SUCCESS;
        case 'r':
            em6502_reset(&cpu);
            break;
        default:
            Byte opcode = em6502_execute_instruction();
            printf("Executed opcode: %s[%02X]\n", get_instruction(opcode).name, opcode);
            break;
        }
    }

    return EXIT_SUCCESS;
}
