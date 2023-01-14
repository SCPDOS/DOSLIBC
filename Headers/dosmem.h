#ifndef _DOSMEM_H
#define _DOSMEM_H
#include "basetsd.h"

#define MEMORY_FIRST_FIT    0
#define MEMORY_LAST_FIT     1
#define MEMORY_BEST_FIT     2
#define MEMORY_ERROR        0xFF


LPVOID WINAPI VirtualAllocate(SIZE_T dwNumberOfParagraphs);
BOOL WINAPI VirtualFree(LPVOID lpAddress);
BOOL WINAPI VirtualReallocate(LPVOID lpAddress, SIZE_T dwNumberOfParagraphs);
BYTE WINAPI GetMemoryAllocationStrategy();
BOOL WINAPI SetMemoryAllocationStrategy(BYTE bAllocationStrategy);
//Undocumented but exposed function for now.
LPVOID WINAPI PhysicalAllocate(SIZE_T dwNumberOfParagraphs);
//Undocumented but exposed function for now.
BOOL WINAPI PhysicalFree(LPVOID lpAddress);
//Undocumented but exposed function for now.
BOOL WINAPI PhysicalReallocate(LPVOID lpAddress, SIZE_T dwNumberOfParagraphs);

#endif