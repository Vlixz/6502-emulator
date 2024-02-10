#ifndef INC_DEBUG_H
#define INC_DEBUG_H

#include <stdint.h>

#include "common.h"
#include "instruction.h"

typedef struct {
    instruction ins;
    Word hex;
    Word lastPC;
    uint8_t cycles;
} execution_information;

#endif /* INC_DEBUG_H */