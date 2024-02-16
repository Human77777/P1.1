#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mymalloc.h"

static char memory[5000];
static int isEmpty = 1;

void initialize() {
    *((short*)memory) = -4998; 
}

void* allocateBlock(int size) {
    if (size <= 0 || size > 4998) {
        return NULL;
    }

    int spaceNeeded = size + sizeof(short); 
    char* current = memory;

    while (current - memory < 5000) {
        short blockSize = abs(*(short*)current);
        short isAllocated = *(short*)current > 0;

        if (!isAllocated && blockSize >= spaceNeeded) {
            if (blockSize >= spaceNeeded + sizeof(short) + 1) { // Split block if enough space
                *(short*)(current + spaceNeeded) = -(blockSize - spaceNeeded);
            }
            *(short*)current = spaceNeeded;
            return current + sizeof(short);
        }
        current += blockSize;
    }
    return NULL;
}

void myfree(void* ptr, char* file, int line) {
    if (ptr == NULL || ptr < (void*)&memory[0] || ptr >(void*) & memory[4998]) {
        fprintf(stderr, "ERROR: Attempt to free invalid pointer in FILE: %s LINE: %d\n", file, line);
        return;
    }

    char* blockStart = (char*)ptr - sizeof(short);
    if (*(short*)blockStart <= 0) {
        fprintf(stderr, "ERROR: Double free or corruption in FILE: %s LINE: %d\n", file, line);
        return;
    }

    *(short*)blockStart = -abs(*(short*)blockStart); // Mark as free

    // Attempt to coalesce with next block
    char* nextBlock = blockStart + abs(*(short*)blockStart);
    if (nextBlock - memory < 5000 && *(short*)nextBlock < 0) {
        *(short*)blockStart += *(short*)nextBlock;
    }

    // Attempt to coalesce with previous block (requires traversal from start)
    char* prev = memory;
    while (prev < blockStart) {
        if (prev + abs(*(short*)prev) == blockStart && *(short*)prev < 0) {
            *(short*)prev += *(short*)blockStart;
            break;
        }
        prev += abs(*(short*)prev);
    }
}

void* mymalloc(size_t size, char* file, int line) {
    if (isEmpty) {
        initialize();
        isEmpty = 0;
    }
    void* ptr = allocateBlock((int)size);
    if (ptr == NULL) {
        fprintf(stderr, "ERROR: Not enough free space for malloc in FILE: %s LINE: %d\n", file, line);
    }
    return ptr;
}
