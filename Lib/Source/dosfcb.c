#include "../../Headers/scpdos.h"

VOID WINAPI __setDTA(LPVOID lpDTA){
    ASM(
        "mov rdx, rcx\n\t"
        "mov eax, 0x1A00\n\t"
        "int 0x41"
    );
}

LPVOID WINAPI __getDTA(){
    ASM(
        "push rbx\n\t"
        "mov eax, 0x2F00\n\t"
        "int 0x41\n\t"
        "mov rax, rbx\n\t"
        "pop rbx"
    );
}

//lpFQFileName = 128 byte buffer
LPSTR WINAPI GetFQPFileName(LPCSTR lpSourceFileName, LPSTR lpFQFileName){
    ASM(
        "push rsi\n\t"
        "push rdi\n\t"
        "mov rsi, rcx\n\t"
        "mov rdi, rdx\n\t"
        "mov eax, 0x6000\n\t"
        "int 0x41\n\t"
        "pop rdi\n\t"
        "pop rsi"
    );
}

//Returns:  00 if no wildcard characters present
//          01 if wildcards present in string
//          FF if drive specifier is invalid
CHAR WINAPI ParseFileName(LPCSTR lpFileName, LPFCB lpFCB, PARSE_MODE pm){
    ASM(
        "push rsi\n\t"
        "push rdi\n\t"
        "mov rsi, rcx\n\t"
        "mov rdi, rdx\n\t"
        "mov eax, 0x2900\n\t"
        "mov al, r8b\n\t"
        "int 0x41\n\t"
    );
}