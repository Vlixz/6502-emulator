#include <stdio.h>

#include <6502.h>

int main()
{

    printf("Hello world from example 1!\n");

    CPU_6502 cpu;

    em6502_reset(&cpu); // Reset cpu

    // Start of inline program
    cpu.memory[0xFFFC] = ADC_IM_OPCODE;
    cpu.memory[0xFFFD] = 10;
    // End of inline program

    em6502_execute(&cpu, ADC_IM_CYCLES);

    return 1;
}