#ifndef INC_MEMORY_H
#define INC_MEMORY_H

#include <stdlib.h>
#include <stdio.h>

int readBinaryFile(const char *filename, unsigned char *memory, size_t maxSize);

#endif /* INC_MEMORY_H */