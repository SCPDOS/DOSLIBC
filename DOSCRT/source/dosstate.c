#include "../headers/scpdos.h"

#if !INLINE_ASM
#include "../headers/asm/asmstate.h"
#endif

/*
	DO NOT EXPOSE: INT 21,2F  Get disk transfer address
Gotta do the following:
	ALL DISK SPACE FUNCTIONS NEED TO BE WORKED ON
	INT 21,44  IOCTL 

	INT 21,5C  Lock/unlock file access (3.x+)
	INT 21,5D  Critical error information (undocumented 3.x+)
	INT 21,5E  Network services (3.1+)
	INT 21,5F  Network redirection (3.1+)
*/

VOID DOSAPI SetInterruptVector(DWORD dwInterruptVector, LPVOID lpInterruptHandler) {
#if INLINE_ASM
	ASM
		"movzx eax, cl\n\t"
		"mov ah, 0x25\n\t"
		"int 0x21"
		END_ASM
#else
	//SetInterruptVectorA(dwInterruptVector, lpInterruptHandler);
#endif
}

LPVOID DOSAPI GetInterruptVector(DWORD dwInterruptVector) {
#if INLINE_ASM
	ASM
		"push rbx\n\t"
		"movzx eax, cl\n\t"
		"mov ah, 0x35\n\t"
		"int 0x21\n\t"
		"mov rax, rbx\n\t"
		"pop rbx"
		END_ASM
#else
	//return GetInterruptVectorA(dwInterruptVector);
#endif
}

VOID DOSAPI SetDiskVerifyState() {
#if INLINE_ASM
	ASM
		"mov eax, 0x2E01\n\t"
		"int 0x21"
		END_ASM
#else
	//SetDiskVerifyStateA();
#endif
}

VOID DOSAPI ClearDiskVerifyState() {
#if INLINE_ASM
	ASM
		"mov eax, 0x2E00\n\t"
		"int 0x21"
		END_ASM
#else
	//ClearDiskVerifyStateA();
#endif
}

WORD DOSAPI GetDOSVersion() {
#if INLINE_ASM
	ASM
		"mov eax, 0x3000\n\t"
		"int 0x21"
		END_ASM
#else
	//return GetDOSVersionA();
#endif
}

BOOL DOSAPI GetCtrlBreakState() {
#if INLINE_ASM
	ASM
		"mov eax, 0x3300\n\t"
		"int 0x21\n\t"
		"movzx eax, dl"
		END_ASM
#else
	//return GetCtrlBreakStateA();
#endif
}

VOID DOSAPI SetCtrlBreakState(BOOL bState) {
#if INLINE_ASM
	ASM
		"mov eax, 0x3301\n\t"
		"mov dl, cl\n\t"
		"int 0x21"
		END_ASM
#else
	//SetCtrlBreakState(bState);
#endif
}