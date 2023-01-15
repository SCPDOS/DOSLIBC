#include "../headers/scpdos.h"

#if !INLINE_ASM
#include "../headers/asm/asmfcb.h"
#endif

VOID DOSAPI __setDTA(LPVOID lpDTA){
#if INLINE_ASM
    ASM
        "mov rdx, rcx\n\t"
        "mov eax, 0x1A00\n\t"
        "int 0x41"
    END_ASM
#else
    //__setDTAA(lpDTA);
#endif
}

LPVOID DOSAPI __getDTA(){
#if INLINE_ASM
    ASM
        "push rbx\n\t"
        "mov eax, 0x2F00\n\t"
        "int 0x41\n\t"
        "mov rax, rbx\n\t"
        "pop rbx"
    END_ASM
#else
    //return __getDTA();
#endif
}

//Returns:  00 if no wildcard characters present
//          01 if wildcards present in string
//          FF if drive specifier is invalid
CHAR DOSAPI ParseFileName(LPCSTR lpFileName, LPFCB lpFCB, PARSE_MODE pm){
#if INLINE_ASM
    ASM
        "push rsi\n\t"
        "push rdi\n\t"
        "mov rsi, rcx\n\t"
        "mov rdi, rdx\n\t"
        "mov eax, 0x2900\n\t"
        "mov al, r8b\n\t"
        "int 0x41\n\t"
    END_ASM
#else
    //return ParseFileNameA(lpFileName, lpFCB, pm);
#endif
}