#include "cpu.h"
#include <stdio.h>

CPU_6502 cpu;

Byte mem_fetch(const Word address) {
    //printf("(cpu_fetch) reading at: 0x%X\n", address);
    Byte data = cpu.memory[address];
    //printf("(cpu_fetch) GOT: 0x%X\n", data);

    if (address == cpu.PC) cpu.PC++;

    return data;
}

void mem_write(const Word address, const Word value) {
    cpu.memory[address] = value;
}

void stack_push_byte(const Byte value) {}
void stack_push_word(const Word value) {}

Byte stack_pop_byte() { return 0; }
Word stack_pop_word() { return 0; }

void stack_push_ps() {}
void stack_pop_ps() {}
