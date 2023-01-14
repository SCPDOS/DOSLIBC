#include "../../Headers/scpdos.h"

BOOL WINAPI GetDefaultDiskDPBPointer(LPDPB lpDPB){
    ASM(
        "push rbx\n\t"
        "mov eax, 0x1F00\n\t"
        "int 0x41\n\t"
        "not al\n\t"
        "jz gdddpExit\n\t"
        "mov qword [rcx], rbx\n\t"
        "mov eax, 1\n"
        "gdddpExit:\n\t"
        "pop rbx"
    );
}

BOOL WINAPI GetDPBPointer(DRIVE_NUMBER bNumber, LPDPB lpDPB){
    ASM(
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
    );
}

VOID WINAPI SetCurrentProcessId(PROCESS_ID pid){
    ASM(
        "push rbx\n\t"
        "mov rbx, rcx\n\t"
        "mov eax, 0x5000\n\t"
        "int 0x41"
    );
}

PROCESS_ID WINAPI GetCurrentProcessId(){
    ASM(
        "push rbx\n\t"
        "mov eax, 0x5100\n\t"
        "int 0x41\n\t"
        "mov rax, rbx\n\t"
        "pop rbx"
    );
}

LPVOID WINAPI GetPointerToDosSysVars(){
    __asm__ __volatile(
        "push rbx\n\t"
        "mov eax, 0x5200\n\t"
        "int 0x41\n\t"
        "mov rax, rbx\n\t"
        "pop rbx"
    );
}

VOID WINAPI GenerateDPB(LPVOID lpBPB, LPDPB lpDPB){
    ASM(
        "push rsi\n\t"
        "push rbp\n\t"
        "mov rsi, rcx\n\t"
        "mov rbp, rdx\n\t"
        "mov eax, 0x5300\n\t"
        "int 0x41\n\t"
        "pop rbp\n\t"
        "pop rsi"
    );
}

VOID WINAPI GeneratePartialPSP(LPVOID lpPSPAddress){
    ASM(
        "mov rdx, rcx\n\t"
        "mov eax, 0x2600\n\t"
        "int 0x41\n\t"
    );
}
VOID WINAPI GenerateNewPSP(LPVOID lpPSPAddress, DWORD dwSizeOfPSPAllocation){
    ASM(
        "push rsi\n\t"
        "mov rsi, rdx\n\t"
        "mov rdx, rcx\n\t"
        "mov eax, 0x5500\n\t"
        "int 0x41\n\t"
        "pop rsi"
    );
}

LPCH WINAPI GetPtrToInDOSFlag(){
    ASM(
        "push rbx\n\t"
        "mov eax, 0x3400\n\t"
        "int 0x41\n\t"
        "mov rax, rbx\n\t"
        "pop rbx\n\t"
    );
}

VOID GetSwitchChar(LPCH lpSwitchChar){
    ASM(
        "mov eax, 0x3700\n\t"
        "int 0x41\n\t"
        "mov byte ptr [rcx], dl"
    );
}

VOID SetSwitchChar(CHAR switchChar){
    ASM(
        "mov eax, 0x3701\n\t"
        "mov dl, cl\n\t"
        "int 0x41"
    );
}