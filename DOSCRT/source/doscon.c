#include "../headers/scpdos.h"

#if !INLINE_ASM
#include "../headers/asm/asmcon.h"
#endif

CHAR DOSAPI GetChar() {
#if INLINE_ASM
	ASM
		"mov eax, 0x0100\n\t"
		"int 0x41\n\t"
		"movzx eax, al"
		END_ASM
#else
	return GetCharA();
#endif
}

VOID DOSAPI PutChar(CHAR c) {
#if INLINE_ASM
	ASM
		"movzx edx, cl\n\t"
		"mov eax, 0x0200\n\t"
		"int 0x41"
		END_ASM
#else
	PutCharA(c);
#endif
}

CHAR DOSAPI AuxInput() {
#if INLINE_ASM
	ASM
		"mov eax, 0x0300\n\t"
		"int 0x41\n\t"
		"movzx eax, al"
		END_ASM
#else
	return AuxInputA();
#endif
}

VOID DOSAPI AuxOutput(CHAR c) {
#if INLINE_ASM
	ASM
		"movzx edx, cl\n\t"
		"mov eax, 0x0400\n\t"
		"int 0x41"
		END_ASM
#else
	AuxOutputA(c);
#endif
}

VOID DOSAPI PrnOutput(CHAR c) {
#if INLINE_ASM
	ASM
		"movzx edx, cl\n\t"
		"mov eax, 0x0500\n\t"
		"int 0x41"
		END_ASM
#else
	PrnOutputA(c);
#endif
}
//Returns FALSE if there are no chars pending
BOOL DOSAPI DirectConInAsync(LPCH c) {
#if INLINE_ASM
	ASM
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
		END_ASM
#else
	return DirectConInAsyncA(c);
#endif
}
//If the char is 0xFF, this function will act as a nop
VOID DOSAPI DirectConOutAsync(CHAR c) {
#if INLINE_ASM
	ASM
		"cmp cl, 0xFF\n\t"
		"je dcoExit\n\t"
		"movzx edx, cl\n\t"
		"mov eax, 0x0600\n\t"
		"int 0x41\n\t"
		"dcoExit:"
		END_ASM
#else
	DirectConOutAsyncA(c);
#endif
}

CHAR DOSAPI DirectConIn() {
#if INLINE_ASM
	ASM
		"mov eax, 0x0700\n\t"
		"int 0x41\n\t"
		"movzx eax, al"
		END_ASM
#else
	return DirectConInA();
#endif
}

CHAR DOSAPI ConInput() {
#if INLINE_ASM
	ASM
		"mov eax, 0x0800\n\t"
		"int 0x41\n\t"
		"movzx eax, al"
		END_ASM
#else
	return ConInputA();
#endif
}

VOID DOSAPI __WriteString(LPCSTR lpString, int len) {
#if INLINE_ASM
	ASM
		"push rbx \n\t"
		"xor ebx, ebx \n\t"
		"inc ebx \n\t"
		"xchg rdx, rcx \n\t"
		"mov eax, 0x4000 \n\t"
		"int 0x41 \n\t"
		"pop rbx"
		END_ASM
#else
	__WriteStringA(lpString, len);
#endif
}

VOID DOSAPI WriteString(LPCSTR lpString) {
	int len;
	for (len = 0; len < 129; len++) {
		if (lpString[len] == '$' || lpString[len] == '\0') {
			break;
		}
	}
	__WriteString(lpString, len);
}

VOID DOSAPI __GetBufferedInput(LPSTR lpString) {
#if INLINE_ASM
	ASM
		"mov rdx, rcx\n\t"
		"mov eax, 0x0A00\n\t"
		"int 0x41"
		END_ASM
#else
	__GetBufferedInputA(lpString);
#endif
}

//The string will be null terminated. 
//Please ensure that your lpString is at least 3 bytes longer than the input and sanitised on first call.
//On return, lpString[0] = Length, lpString[1] = Number of chars in buffer, lpString[2] = Start of char string
VOID DOSAPI GetBufferedInput(LPSTR lpString, BYTE bufferLen) {
	//If the buffer has changed length, overwrite byte bufferLen[1]
	if (lpString[0] != bufferLen) {
		lpString[1] = 0;
	}
	__GetBufferedInput(lpString);
}

//If there is a char available to be read, we return TRUE
BOOL DOSAPI GetConInputStatus() {
#if INLINE_ASM
	ASM
		"mov eax, 0x0B00\n\t"
		"int 0x41\n\t"
		"and al, 1"
		END_ASM
#else
	return GetConInputStatusA();
#endif
}

VOID DOSAPI ClearInputBuffer() {
#if INLINE_ASM
	ASM
		"mov eax, 0x0C00\n\t"
		"int 0x41\n\t"
		END_ASM
#else
	ClearInputBufferA();
#endif
}