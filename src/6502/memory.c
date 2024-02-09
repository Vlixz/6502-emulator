#include "cpu.h"
#include "memory.h"

#include <string.h>

Byte memory[MEMORY_WORD_COUNT_6502];

void mem_reset(void) {
    memset(memory, 0, sizeof(memory));
}

Byte mem_fetch(const Word address) {
    Byte data = memory[address];
    
    cpu.PC += (address == cpu.PC);

    return data;
}

Byte mem_read(const Word address) {
    return memory[address];
}

void mem_write(const Word address, const Word value) {
    memory[address] = value;
}

void stack_push_byte(const Byte value) {
    memory[STACK_START + cpu.SP--] = value;
}

void stack_push_word(const Word value) {
    memory[STACK_START + cpu.SP--] = value >> 8;   // MSB
    memory[STACK_START + cpu.SP--] = value & 0xFF; // LSB
}

Byte stack_pop_byte() {
    return memory[STACK_START + ++cpu.SP];
}

Word stack_pop_word() {
    Word value = 0;

    value |= memory[STACK_START + ++cpu.SP];      // LSB
    value |= memory[STACK_START + ++cpu.SP] << 8; // MSB

    return value;
}

void stack_push_ps() {
    Byte ps = 0;

    SET_BIT_PSR(ps, cpu.C, PSR_C);
    SET_BIT_PSR(ps, cpu.Z, PSR_Z);
    SET_BIT_PSR(ps, cpu.I, PSR_I);
    SET_BIT_PSR(ps, cpu.D, PSR_D);
    SET_BIT_PSR(ps, 1, PSR_B); // Always set to 1 when pushed to stack
    SET_BIT_PSR(ps, 1, PSR_RESERVED);
    SET_BIT_PSR(ps, cpu.V, PSR_V);
    SET_BIT_PSR(ps, cpu.N, PSR_N);

    stack_push_byte(ps);
}

void stack_pop_ps() {
    Byte ps = stack_pop_byte();

    GET_BIT_PSR(cpu.C, ps, PSR_C);
    GET_BIT_PSR(cpu.Z, ps, PSR_Z);
    GET_BIT_PSR(cpu.I, ps, PSR_I);
    GET_BIT_PSR(cpu.D, ps, PSR_D);
    GET_BIT_PSR(cpu.B, ps, PSR_B);
    GET_BIT_PSR(cpu.V, ps, PSR_V);
    GET_BIT_PSR(cpu.N, ps, PSR_N);
}

int mem_read_bin_file(const char *filename) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        return -1;
    }

    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (fileSize > sizeof(memory)) {
        fclose(file);
        return -1;
    }

    size_t bytesRead = fread(memory, 1, fileSize, file);

    if (bytesRead != fileSize) {
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
}
