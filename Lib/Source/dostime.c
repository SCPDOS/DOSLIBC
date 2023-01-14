#include "../../Headers/scpdos.h"

VOID WINAPI GetDate(LPCH lpDayOfTheWeek, LPWORD lpYearOffset, LPCH lpMonth, LPCH lpDayOfTheMonth){
    ASM(
        "push rsi\n\t"
        "push rdi\n\t"
        "mov rsi, rcx\n\t"
        "mov rdi, rdx\n\t"
        "mov eax,0x2A00\n\t"
        "int 0x41\n\t"
        "mov byte ptr [rsi], al\n\t"
        "mov word ptr [rdi], cx\n\t"
        "mov al, dh\n\t"
        "mov byte ptr [r8], al \n\t"
        "mov byte ptr [r9], dl \n\t"
        "pop rdi\n\t"
        "pop rsi"
    );
}

BOOL WINAPI SetDate(WORD year, CHAR month, CHAR day){
    ASM(
        "mov dh, dl\n\t"
        "mov dl, r8b\n\t"
        "mov eax, 0x2B00\n\t"
        "int 0x41\n\t"
        "inc eax"
    );
}

VOID WINAPI GetTime(LPCH lpHour, LPCH lpMinute, LPCH lpSeconds, LPCH lpHSeconds){
    ASM(
        "push rsi\n\t"
        "push rdi\n\t"
        "mov rsi, rcx\n\t"
        "mov rdi, rdx\n\t"
        "mov eax,0x2C00\n\t"
        "int 0x41\n\t"
        "mov byte ptr [rsi], ch\n\t"
        "mov byte ptr [rdi], cl\n\t"
        "mov al, dh\n\t"
        "mov byte ptr [r8], al \n\t"
        "mov byte ptr [r9], dl \n\t"
        "pop rdi\n\t"
        "pop rsi"
    );
}

BOOL WINAPI SetTime(CHAR hour, CHAR minute, CHAR seconds, CHAR hSeconds){
    ASM(
        "mov ch, cl\n\t"
        "mov cl, dl\n\t"
        "mov dl, r8b\n\t"
        "mov dh, dl\n\t"
        "mov dl, r9b\n\t"
        "mov eax, 0x2D00\n\t"
        "int 0x41\n\t"
        "inc eax"
    );
}