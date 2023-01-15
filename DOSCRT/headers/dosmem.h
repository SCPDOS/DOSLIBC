#ifndef _DOSMEM_H
#define _DOSMEM_H
#include "basetsd.h"

#define MEMORY_FIRST_FIT    0
#define MEMORY_LAST_FIT     1
#define MEMORY_BEST_FIT     2
#define MEMORY_ERROR        0xFF


LPVOID DOSAPI VirtualAllocate(SIZE_T dwNumberOfParagraphs);
BOOL DOSAPI VirtualFree(LPVOID lpAddress);
BOOL DOSAPI VirtualReallocate(LPVOID lpAddress, SIZE_T dwNumberOfParagraphs);
BYTE DOSAPI GetMemoryAllocationStrategy();
BOOL DOSAPI SetMemoryAllocationStrategy(BYTE bAllocationStrategy);
//Undocumented but exposed function for now.
LPVOID DOSAPI PhysicalAllocate(SIZE_T dwNumberOfParagraphs);
//Undocumented but exposed function for now.
BOOL DOSAPI PhysicalFree(LPVOID lpAddress);
//Undocumented but exposed function for now.
BOOL DOSAPI PhysicalReallocate(LPVOID lpAddress, SIZE_T dwNumberOfParagraphs);

#endif