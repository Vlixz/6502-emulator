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

void mem_write(const Word address, const Word value) {
    memory[address] = value;
}

void stack_push_byte(const Byte value) {
    memory[cpu.SP++] = value;
}

void stack_push_word(const Word value) {
    memory[cpu.SP++] = value & 0xFF; // LSB
    memory[cpu.SP++] = value >> 8;   // MSB
}

Byte stack_pop_byte() {
    return memory[--cpu.SP];
}

Word stack_pop_word() {
    Word value = 0;

    value |= memory[--cpu.SP];      // MSB
    value |= memory[--cpu.SP] << 8; // LSB

    return value;
}

void stack_push_ps() {
    Byte ps = 0;

    ps |= cpu.C << 0;
    ps |= cpu.Z << 1;
    ps |= cpu.I << 2;
    ps |= cpu.D << 3;
    ps |= cpu.B << 4;
    ps |= cpu.V << 6;
    ps |= cpu.N << 7;

    stack_push_byte(ps);
}

void stack_pop_ps() {
    Byte ps = stack_pop_byte();

    // cpu.C = ps & (1 << 0);
    // cpu.Z = ps & (1 << 1);
    // cpu.I = ps & (1 << 2);
    // cpu.D = ps & (1 << 3);
    // cpu.B = ps & (1 << 4);
    // cpu.V = ps & (1 << 6);
    // cpu.N = ps & (1 << 7);
}

int readBinaryFile(const char *filename) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        perror("Error opening file");
        return -1; // Return an error code
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (fileSize > sizeof(memory)) {
        fclose(file);
        fprintf(stderr, "File size exceeds the maximum allowed size\n");
        return -1; // Return an error code
    }

    // Read the file into the specified byte array
    size_t bytesRead = fread(memory, 1, fileSize, file);

    if (bytesRead != fileSize) {
        fclose(file);
        perror("Error reading file");
        return -1; // Return an error code
    }

    fclose(file);
    return 0; // Return success
}
