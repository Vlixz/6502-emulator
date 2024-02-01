#ifndef INC_DEBUG_H
#define INC_DEBUG_H

#include <stdint.h>

#include "common.h"
#include "instruction.h"

typedef struct {
    instruction ins;
    Word PC;
    Word address;
    uint8_t cycles;
} execution_information;


#endif /* INC_DEBUG_H */