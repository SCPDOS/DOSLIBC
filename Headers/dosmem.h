#ifndef DOSMEM_H
#define DOSMEM_H
#include "basetsd.h"

#define MEMORY_FIRST_FIT    0
#define MEMORY_LAST_FIT     1
#define MEMORY_BEST_FIT     2
#define MEMORY_ERROR        0xFF
#endif
LPVOID PUBLIC VirtualAllocate(SIZE_T dwNumberOfParagraphs);

BOOL PUBLIC VirtualFree(LPVOID lpAddress);

BOOL PUBLIC VirtualReallocate(LPVOID lpAddress, SIZE_T dwNumberOfParagraphs);

BYTE PUBLIC GetMemoryAllocationStrategy();

BOOL PUBLIC SetMemoryAllocationStrategy(BYTE bAllocationStrategy);

//Undocumented but exposed function for now.
LPVOID PUBLIC PhysicalAllocate(SIZE_T dwNumberOfParagraphs);

//Undocumented but exposed function for now.
BOOL PUBLIC PhysicalFree(LPVOID lpAddress);

//Undocumented but exposed function for now.
BOOL PUBLIC PhysicalReallocate(LPVOID lpAddress, SIZE_T dwNumberOfParagraphs);