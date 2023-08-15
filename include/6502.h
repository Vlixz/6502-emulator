#ifndef INC_6502_H
#define INC_6502_H

#include "opcodes.h"
#include "common.h"
#include "cpu.h"

CPU_6502 cpu;

void reset( void );

void execute( int cycles );

#endif /* INC_6502_H */