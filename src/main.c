#include <stdio.h>
#include <stdlib.h>

#include "6502.h"
#include "cpu.h"
#include "debug.h"
#include "memory.h"
#include "instruction.h"

const char *BIN_TEST_FILE =
    "../../examples/6502_functional_test.bin";

int main(int argc, char **argv) {

    int result = mem_read_bin_file(BIN_TEST_FILE);

    if (result != 0)
        return EXIT_FAILURE;

    printf("Successfully read file into cpu memory\n");

    em6502_reset(&cpu, 0x0400);

    Word old_pc;
    execution_information info;
    while (1) {
        char input = ' ';

        switch (input) {
        case 'q':
            return EXIT_SUCCESS;
        case 'r':
            em6502_reset(&cpu, 0x400);
            mem_read_bin_file(BIN_TEST_FILE);
            break;
        default:
            info = em6502_execute_instruction();
            printf("Executed opcode: %s, cycles: %d\n", info.ins.name, info.ins.cycles);
            printf("PC: 0x%04X\n", info.PC);
            printf("A: 0x%02X\n", cpu.A);
            printf("X: 0x%02X\n", cpu.X);
            printf("Y: 0x%02X\n", cpu.Y);
            printf("SP: 0x%02X\n", cpu.SP);
            printf("Flags: C[%d] Z[%d] I[%d] D[%d] B[%d] V[%d] N[%d]\n" , cpu.C, cpu.Z, cpu.I, cpu.D, cpu.B, cpu.V, cpu.N);

            break;
        }

        if (old_pc == info.PC)
            break;
            
        old_pc = info.PC;
    }

    return EXIT_SUCCESS;
}
