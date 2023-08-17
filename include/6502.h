#ifndef INC_6502_H
#define INC_6502_H

#include "common.h"
#include "cpu.h"

void reset_6502(CPU_6502 *cpu);

void destroy_6502(CPU_6502 *cpu);

void execute_6502(CPU_6502 *cpu, int cycles);

#endif /* INC_6502_H */