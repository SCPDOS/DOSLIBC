#include "../headers/scpdos.h"

#if !INLINE_ASM
#include "../headers/asm/asmtime.h"
#endif


VOID DOSAPI GetDate(LPCH lpDayOfTheWeek, LPWORD lpYearOffset, LPCH lpMonth, LPCH lpDayOfTheMonth){
#if INLINE_ASM
    ASM
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
    END_ASM
#else
    //GetDateA(lpDayOfTheWeek, lpYearOffset, lpMonth, lpDayOfTheMonth);
#endif
}

BOOL DOSAPI SetDate(WORD year, CHAR month, CHAR day){
#if INLINE_ASM
    ASM
        "mov dh, dl\n\t"
        "mov dl, r8b\n\t"
        "mov eax, 0x2B00\n\t"
        "int 0x41\n\t"
        "inc eax"
    END_ASM
#else
    //return SetDateA(year, month, day);
#endif
}

VOID DOSAPI GetTime(LPCH lpHour, LPCH lpMinute, LPCH lpSeconds, LPCH lpHSeconds){
#if INLINE_ASM
    ASM
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
    END_ASM
#else
    //GetTimeA(lpHour, lpMinute, lpSeconds, lpHSeconds);
#endif
}

BOOL DOSAPI SetTime(CHAR hour, CHAR minute, CHAR seconds, CHAR hSeconds){
#if INLINE_ASM
    ASM
        "mov ch, cl\n\t"
        "mov cl, dl\n\t"
        "mov dl, r8b\n\t"
        "mov dh, dl\n\t"
        "mov dl, r9b\n\t"
        "mov eax, 0x2D00\n\t"
        "int 0x41\n\t"
        "inc eax"
    END_ASM
#else
    //return SetTimeA(hour, minute, seconds, hSeconds);
#endif
}