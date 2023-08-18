#ifndef INC_6502_H
#define INC_6502_H

#include "common.h"
#include "cpu.h"

void em6502_reset(CPU_6502 *cpu);

void em6502_destroy(CPU_6502 *cpu);

int em6502_execute(CPU_6502 *cpu, int cycles);

#endif /* INC_6502_H */