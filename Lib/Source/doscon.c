#include "../../Headers/scpdos.h"

CHAR WINAPI GetChar(){
    ASM(
        "mov eax, 0x0100\n\t"
        "int 0x41\n\t"
        "movzx eax, al"
    );
}

VOID WINAPI PutChar(CHAR c){
    ASM(
        "movzx edx, cl\n\t"
        "mov eax, 0x0200\n\t"
        "int 0x41"
    );
}

CHAR WINAPI AuxInput(){
    ASM(
        "mov eax, 0x0300\n\t"
        "int 0x41\n\t"
        "movzx eax, al"
    );
}

VOID WINAPI AuxOutput(CHAR c){
    ASM(
        "movzx edx, cl\n\t"
        "mov eax, 0x0400\n\t"
        "int 0x41"
    );
}

VOID WINAPI PrnOut(CHAR c){
    ASM(
        "movzx edx, cl\n\t"
        "mov eax, 0x0500\n\t"
        "int 0x41"
    );
}
//Returns FALSE if there are no chars pending
BOOL WINAPI DirectConInA(LPCH c){
    ASM(
        "mov r8, rcx\n\t"
        "mov eax, 0x0600\n\t"
        "mov edx, 0xFF\n\t"
        "xor ecx, ecx\n\t"
        "int 0x41\n\t"
        "jnz short dciExit\n\t"
        "inc ecx\n\t"
        "mov byte ptr [r8], al\n"
        "dciExit:\n\t"
        "mov eax, ecx"
    );
}
//If the char is 0xFF, this function will act as a nop
VOID WINAPI DirectConOutA(CHAR c){
    ASM(
        "cmp cl, 0xFF\n\t"
        "je dcoExit\n\t"
        "movzx edx, cl\n\t"
        "mov eax, 0x0600\n\t"
        "int 0x41\n\t"
        "dcoExit:"
    );
}

CHAR WINAPI DirectConIn(){
    ASM(
        "mov eax, 0x0700\n\t"
        "int 0x41\n\t"
        "movzx eax, al"
    );
}

CHAR WINAPI ConInput(){
    ASM(
        "mov eax, 0x0800\n\t"
        "int 0x41\n\t"
        "movzx eax, al"
    );
}

VOID WINAPI __WriteString(LPCSTR lpString, int len){
    ASM (
        "push rbx \n\t"
        "xor ebx, ebx \n\t"
        "xchg rdx, rcx \n\t"
        "mov eax, 0x4000 \n\t"
        "int 0x41 \n\t"
        "pop rbx"
    );
}

VOID WINAPI WriteString(LPCSTR lpString){
    int len;
    for(len = 0; len < 129; len++){
        if(lpString[len] == '$' || lpString[len]=='\0'){
            break;
        }
    }
    __WriteString(lpString, len);
}

VOID WINAPI __GetBufferedInput(LPSTR lpString){
        ASM(
        "mov rdx, rcx\n\t"
        "mov eax, 0x0A00\n\t"
        "int 0x41"
    );
}

//The string will be null terminated. 
//Please ensure that your lpString is at least 3 bytes longer than the input and sanitised on first call.
//On return, lpString[0] = Length, lpString[1] = Number of chars in buffer, lpString[2] = Start of char string
VOID WINAPI GetBufferedInput(LPSTR lpString, BYTE bufferLen){
    //If the buffer has changed length, overwrite byte bufferLen[1]
    if(lpString[0] != bufferLen ){
        lpString[1] = 0;
    }
    __GetBufferedInput(lpString);
}

//If there is a char available to be read, we return TRUE
BOOL WINAPI GetConInputStatus(){
    ASM(
        "mov eax, 0x0B00\n\t"
        "int 0x41\n\t"
        "and al, 1"
    );
}

VOID WINAPI ClearInputBuffer(){
    ASM(
        "mov eax, 0x0C00\n\t"
        "int 0x41\n\t"
    );
}