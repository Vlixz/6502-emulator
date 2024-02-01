#include "cpu.h"
#include <stdio.h>

#include "debug.h"
#include "memory.h"
#include "instruction.h"

central_processing_unit cpu;

instruction get_instruction(Byte opcode) {
    return instruction_matrix[opcode >> 4][opcode & 0x0F];
}

execution_information instruction_execute(void) {
    Word old_pc = cpu.PC;
    Byte opcode = mem_fetch(cpu.PC);

    current_instruction = get_instruction(opcode);

    Word address;

    uint8_t additional_cycles_1 = current_instruction.addrmode(&address);
    uint8_t additional_cycles_2 = current_instruction.operation(address);

    return (execution_information){current_instruction, old_pc, address, current_instruction.cycles + additional_cycles_1 + additional_cycles_2};
}
