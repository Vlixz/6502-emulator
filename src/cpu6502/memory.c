#include "memory.h"

int readBinaryFile(const char *filename, unsigned char *memory, size_t maxSize) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        perror("Error opening file");
        return -1; // Return an error code
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (fileSize > maxSize) {
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

