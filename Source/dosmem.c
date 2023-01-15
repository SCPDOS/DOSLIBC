#include "../scpdos.h"

#if !INLINE_ASM
#include "../Headers/Asm/asmmem.h"
#endif

//Internal common Allocation function
LPVOID DOSAPI __AllocateMemory(SIZE_T dwNumberOfParagraphs){
#if INLINE_ASM
    ASM
        "push rbx\n\t"
        "mov ebx, ecx\n\t"
        "xor ecx, ecx\n\t"
        "mov eax, 0x4800\n\t"
        "int 0x41\n\t"
        "cmovc eax, ecx\n\t"
        "pop rbx"
    END_ASM
#else
    //return __AllocateMemoryA(dwNumberOfParagraphs);
#endif
}

BOOL DOSAPI __FreeMemory(LPVOID lpAddress){
#if INLINE_ASM
    ASM
        "mov r8, rcx\n\t"
        "mov eax, 0x4900\n\t"
        "xor ecx, ecx\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx"
    END_ASM
#else
    //return __FreeMemoryA(lpAddress);
#endif
}

BOOL DOSAPI __ReallocateMemory(LPVOID lpAddress, SIZE_T dwNumberOfParagraphs){
#if INLINE_ASM
    ASM
        "push rbx\n\t"
        "mov r8, rcx\n\t"
        "mov ebx, edx\n\t"
        "xor ecx, ecx\n\t"
        "mov eax, 0x4A00\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx"
    END_ASM
#else
    //return __ReallocateMemory(lpAddress, dwNumberOfParagraphs);
#endif
}

//Pass the number of paragraphs to allocate in dwSize
//Returns a NULL pointer if fails
LPVOID DOSAPI VirtualAllocate(SIZE_T dwNumberOfParagraphs){
    return __AllocateMemory(dwNumberOfParagraphs);
}

BOOL DOSAPI VirtualFree(LPVOID lpAddress){
    return __FreeMemory(lpAddress);
}

BOOL DOSAPI VirtualReallocate(LPVOID lpAddress, SIZE_T dwNumberOfParagraphs){
    return __ReallocateMemory(lpAddress, dwNumberOfParagraphs);
}

//Undocumented but exposed function for now.
LPVOID DOSAPI PhysicalAllocate(SIZE_T dwNumberOfParagraphs){
    return __AllocateMemory(dwNumberOfParagraphs);
}

//Undocumented but exposed function for now.
BOOL DOSAPI PhysicalFree(LPVOID lpAddress){
    return __FreeMemory(lpAddress);
}

//Undocumented but exposed function for now.
BOOL DOSAPI PhysicalReallocate(LPVOID lpAddress, SIZE_T dwNumberOfParagraphs){
    return __ReallocateMemory(lpAddress, dwNumberOfParagraphs);
}

//If this function returns -1, memory chain error detected
BYTE DOSAPI GetMemoryAllocationStrategy(){
#if INLINE_ASM
    ASM
        "mov eax, 0x5800\n\t"
        "int 0x41\n\t"
    END_ASM
#else
    //return GetMemoryAllocationStrategyA();
#endif
}

//If this function returns FALSE, memory chain error detected
BOOL DOSAPI SetMemoryAllocationStrategy(BYTE bAllocationStrategy){
#if INLINE_ASM
    ASM
        "push rbx\n\t"
        "mov ebx, ecx\n\t"
        "xor ecx, ecx\n\t"
        "mov eax, 0x5801\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx"
    END_ASM
#else
    //return SetMemoryAllocationStrategyA(bAllocationStrategy);
#endif
}
