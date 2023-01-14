#include "../../Headers/scpdos.h"
#include "doserror.c"
#include "internal.c"
#include "dosfcb.c"
#include "dosfile.c"
#include "dosexec.c"
#include "dosmem.c"
#include "doscon.c"
#include "dosnet.c"
#include "dostime.c"
#include "dosintr.c"

/*
	DO NOT EXPOSE: INT 21,2F  Get disk transfer address
Gotta do the following:
	INT 21,36  Get disk free space (ALL FREESPACE FUNCTIONS NEED TO BE WORKED ON)

    and 

    INT 21,5C  Lock/unlock file access (3.x+)
	INT 21,5D  Critical error information (undocumented 3.x+)
	INT 21,5E  Network services (3.1+)
	INT 21,5F  Network redirection (3.1+)
*/

VOID WINAPI SetInterruptVector(DWORD dwInterruptVector, LPVOID lpInterruptHandler){
    ASM(
        "movzx eax, cl\n\t"
        "mov ah, 0x25\n\t"
        "int 0x41"
    );
}

LPVOID WINAPI GetInterruptVector(DWORD dwInterruptVector){
    ASM(
        "push rbx\n\t"
        "movzx eax, cl\n\t"
        "mov ah, 0x35\n\t"
        "int 0x41\n\t"
        "mov rax, rbx\n\t"
        "pop rbx"
    );
}

VOID WINAPI SetDiskVerifyState(){
	ASM(
		"mov eax, 0x2E01\n\t"
		"int 0x41"
	);
}

VOID WINAPI ClearDiskVerifyState(){
	ASM(
		"mov eax, 0x2E00\n\t"
		"int 0x41"
	);
}

WORD WINAPI GetDOSVersion(){
	ASM(
		"mov eax, 0x3000\n\t"
		"int 0x41"
	);
}

BOOL WINAPI GetCtrlBreakState(){
	ASM(
		"mov eax, 0x3300\n\t"
		"int 0x41\n\t"
		"movzx eax, dl"
	);
}

VOID WINAPI SetCtrlBreakState(BOOL bState){
	ASM(
		"mov eax, 0x3301\n\t"
		"mov dl, cl\n\t"
		"int 0x41"
	);
}