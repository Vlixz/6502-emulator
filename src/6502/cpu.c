#include "cpu.h"
#include <stdio.h>

#include "memory.h"
#include "instruction.h"

central_processing_unit cpu;

instruction get_instruction(Byte opcode) {
    return instruction_matrix[opcode >> 4][opcode & 0x0F];
}

uint8_t instruction_execute(void) {
    Byte opcode = mem_fetch(cpu.PC);

    instruction ins = get_instruction(opcode);
    // addrmode = ins.addrmode;

    Word address;

    uint8_t additional_cycles_1 = ins.addrmode(&address);
    uint8_t additional_cycles_2 = ins.operation(address);

    return ins.cycles + additional_cycles_1 + additional_cycles_2;
}
