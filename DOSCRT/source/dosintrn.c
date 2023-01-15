#include "../headers/scpdos.h"

#if !INLINE_ASM
#include "../headers/asm/asmintrn.h"
#endif

BOOL DOSAPI GetDefaultDiskDPBPointer(LPDPB lpDPB){
#if INLINE_ASM
    ASM
        "push rbx\n\t"
        "mov eax, 0x1F00\n\t"
        "int 0x41\n\t"
        "not al\n\t"
        "jz gdddpExit\n\t"
        "mov qword [rcx], rbx\n\t"
        "mov eax, 1\n"
        "gdddpExit:\n\t"
        "pop rbx"
    END_ASM
#else
    //return GetDefaultDiskDPBPointerA(lpDPB);
#endif
}

BOOL DOSAPI GetDPBPointer(DRIVE_NUMBER bNumber, LPDPB lpDPB){
#if INLINE_ASM
    ASM
        "push rbx\n\t"
        "mov r8, rdx\n\t"
        "mov dl, cl\n\t"
        "xor ecx, ecx\n\t"
        "mov eax, 0x3200\n\t"
        "int 0x41\n\t"
        "cmp al, -1\n\t"
        "cmove eax, ecx\n\t"
        "je getDPBExit\n\t"
        "mov eax, ecx\n\t"
        "inc eax\n\t"
        "mov qword ptr [r8], rbx\n"
        "getDPBExit:\n\t"
        "pop rbx"
    END_ASM
#else
    //return GetDPBPointerA(bNumber, lpDPB);
#endif
}

VOID DOSAPI SetCurrentProcessId(PROCESS_ID pid){
#if INLINE_ASM
    ASM
        "push rbx\n\t"
        "mov rbx, rcx\n\t"
        "mov eax, 0x5000\n\t"
        "int 0x41"
    END_ASM
#else
    //SetCurrentProcessIdA(pid);
#endif
}

PROCESS_ID DOSAPI GetCurrentProcessId(){
#if INLINE_ASM
    ASM
        "push rbx\n\t"
        "mov eax, 0x5100\n\t"
        "int 0x41\n\t"
        "mov rax, rbx\n\t"
        "pop rbx"
    END_ASM
#else
    //return GetCurrentProcessIdA();
#endif
}

LPVOID DOSAPI GetPointerToDosSysVars(){
#if INLINE_ASM
    ASM
        "push rbx\n\t"
        "mov eax, 0x5200\n\t"
        "int 0x41\n\t"
        "mov rax, rbx\n\t"
        "pop rbx"
    END_ASM
#else
    //return GetPointerToDosSysVarsA();
#endif
}

VOID DOSAPI GenerateDPB(LPVOID lpBPB, LPDPB lpDPB){
#if INLINE_ASM
    ASM
        "push rsi\n\t"
        "push rbp\n\t"
        "mov rsi, rcx\n\t"
        "mov rbp, rdx\n\t"
        "mov eax, 0x5300\n\t"
        "int 0x41\n\t"
        "pop rbp\n\t"
        "pop rsi"
    END_ASM
#else
    //GenerateDPBA(lpBPB, lpDPB);
#endif
}

VOID DOSAPI GeneratePartialPSP(LPVOID lpPSPAddress){
#if INLINE_ASM
    ASM
        "mov rdx, rcx\n\t"
        "mov eax, 0x2600\n\t"
        "int 0x41\n\t"
    END_ASM
#else
    //GeneratePartialPSPA(lpPSPAddress);
#endif
}
VOID DOSAPI GenerateNewPSP(LPVOID lpPSPAddress, DWORD dwSizeOfPSPAllocation){
#if INLINE_ASM
    ASM
        "push rsi\n\t"
        "mov rsi, rdx\n\t"
        "mov rdx, rcx\n\t"
        "mov eax, 0x5500\n\t"
        "int 0x41\n\t"
        "pop rsi"
    END_ASM
#else
    //GenerateNewPSPA(lpPSPAddress, dwSizeOfPSPAllocation);
#endif
}

LPCH DOSAPI GetPtrToInDOSFlag(){
#if INLINE_ASM
    ASM
        "push rbx\n\t"
        "mov eax, 0x3400\n\t"
        "int 0x41\n\t"
        "mov rax, rbx\n\t"
        "pop rbx\n\t"
    END_ASM
#else
    //return GetPtrToInDOSFlagA();
#endif
}

CHAR GetSwitchChar(){
#if INLINE_ASM
    ASM
        "mov eax, 0x3700\n\t"
        "int 0x41\n\t"
        "movzx eax, dl"
    END_ASM
#else
    //return GetSwitchCharA();
#endif
}

VOID SetSwitchChar(CHAR switchChar){
#if INLINE_ASM
    ASM
        "mov eax, 0x3701\n\t"
        "mov dl, cl\n\t"
        "int 0x41"
    END_ASM
#else
    //SetSwitchChar(switchChar);
#endif
}