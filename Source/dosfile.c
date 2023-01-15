
/* Uses MS x64 ABI
 * Integer arguments only needed for DOS API so we only highlight them here
 *             Arguments passed in: rcx, rdx, r8, r9 then stack
 *       Return value is passed in: rax
 *              Volatile registers: rax, rcx, r8, r9, r10, r11
 *           Nonvolatile registers: rbx, rsp, rbp, r12, r13, r14, r15, rdi, rsi
 */

#include "../scpdos.h"

#if !INLINE_ASM
#include "../Headers/Asm/asmfile.h"
#endif

BOOL DOSAPI CreateDirectory(LPCSTR lpDirectoryName) {
#if INLINE_ASM
	ASM
		"mov rdx, rcx\n\t"
		"mov eax, 0x3900\n\t"
		"xor ecx, ecx\n\t"
		"int 0x41\n\t"
		"mov eax, 1\n\t"
		"cmovc eax, ecx"
		END_ASM
#else
	//return CreateDirectory(lpDirectoryName);
#endif
}

BOOL DOSAPI DeleteDirectory(LPCSTR lpDirectoryName) {
#if INLINE_ASM
	ASM
		"mov rdx, rcx\n\t"
		"mov eax, 0x3A00\n\t"
		"xor ecx, ecx\n\t"
		"int 0x41\n\t"
		"mov eax, 1\n\t"
		"cmovc eax, ecx"
		END_ASM
#else
	//return DeleteDirectoryA(lpDirectoryName);
#endif
}

BOOL DOSAPI ChangeCurrentDirectory(LPCSTR lpDirectoryName) {
#if INLINE_ASM
	ASM
		"mov rdx, rcx\n\t"
		"mov eax, 0x3B00\n\t"
		"xor ecx, ecx\n\t"
		"int 0x41\n\t"
		"mov eax, 1\n\t"
		"cmovc eax, ecx"
		END_ASM
#else
	//return ChangeCurrentDirectory(lpDirectoryName);
#endif
}

HANDLE DOSAPI CreateFile(LPCSTR lpFileName, FILE_ATTRIBUTES dwFileAttributes) {
#if INLINE_ASM
	ASM
		"xchg rdx, rcx\n\t"
		"mov eax, 0x3C00\n\t"
		"int 0x41\n\t"
		"mov ecx, -1\n\t"
		"cmovc eax, ecx"
		END_ASM
#else
	//return CreateFileA(lpFileName, dwFileAttributes);
#endif
}

HANDLE DOSAPI OpenFile(LPCSTR lpFileName, FILE_OPEN_MODE dwOpenMode, \
	FILE_SHARE_MODE dwShareMode) {
	/* rcx -> lpFileName, rdx = dwOpenMode  r8 = dwShareMode*/
	/* First clear bits 2 and 3 on the OpenMode */
	/* Then preserve only share bits in r8b (i.e. bits 4,5,6)*/
#if INLINE_ASM
	ASM
		"mov eax, 0x3D00\n\t"
		"and dl, 0xF3\n\t"
		"mov al, dl\n\t"
		"and r8b, 0x70\n\t "
		"or al, r8b\n\t"
		"mov rdx, rcx\n\t"
		"int 0x41\n\t"
		"mov ecx, -1\n\t"
		"cmovc eax, ecx"
		END_ASM
#else
	//return OpenFile(lpFileName, dwOpenMode, dwShareMode);
#endif
}

/*If we return TRUE, then handle was closed*/
BOOL DOSAPI CloseFile(HANDLE hFile) {
#if INLINE_ASM
	ASM
		"mov eax, 0x3E00\n\t"
		"push rbx\n\t"
		"mov ebx, ecx\n\t"
		"int 0x41\n\t"
		"pop rbx\n\t"
		"mov ecx, 1\n\t"
		"mov eax, 0\n\t"
		"cmovc eax, ecx"
		END_ASM
#else
	//return CloseFileA(hFile);
#endif
}

BOOL DOSAPI ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, \
	LPDWORD lpNumberOfBytesRead) {
	/*rcx = hFile, rdx -> lpBuffer,
	r8 = nNumberOfBytesToRead, r9 -> NumberOfBytesRead*/
#if INLINE_ASM
	ASM
		"\t push rbx\n"
		"\t mov ebx, ecx\n"
		"\t mov rcx, r8\n"
		"\t mov eax, 0x3F00\n"
		"\t int 0x41\n"
		"\t pop rbx\n"
		"\t jnc readOk\n"
		"\t mov eax, 0\n"
		"\t jmp short readExit\n"
		"readOk:\n"
		"\t mov dword ptr [r9], eax\n"
		"\t mov eax, 1\n"
		"readExit:"
		END_ASM
#else
	//return ReadFileA(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead);
#endif
}

BOOL DOSAPI WriteFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToWrite, \
	LPDWORD lpNumberOfBytesWritten) {
	/*rcx = hFile, rdx -> lpBuffer,
	r8 = nNumberOfBytesToWrite, r9 -> NumberOfBytesWritten*/
#if INLINE_ASM
	ASM
		"\t push rbx\n"
		"\t mov ebx, ecx\n"
		"\t mov rcx, r8\n"
		"\t mov eax, 0x4000\n"
		"\t int 0x41\n"
		"\t pop rbx\n"
		"\t jnc writeOk\n"
		"\t mov eax, 0\n"
		"\t jmp short writeExit\n"
		"writeOk:\n"
		"\t mov dword ptr [r9], eax\n"
		"\t mov eax, 1\n"
		"writeExit:"
		END_ASM
#else
	//return WriteFileA(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten);
#endif
}

BOOL DOSAPI DeleteFile(LPCSTR lpFileName) {
#if INLINE_ASM
	ASM
		"mov rdx, rcx\n\t"
		"mov eax, 0x4100\n\t"
		"int 0x41\n\t"
		"mov ecx, 1\n\t"
		"mov eax, 0\n\t"
		"cmovc eax, ecx"
		END_ASM
#else
	//return DeleteFile(lpFileName);
#endif
}

DWORD DOSAPI SetFilePointer(HANDLE hFile, LONG lDistanceToMove, DWORD dwMoveMethod) {
	/* This is the 32 bit version of the function*/
	/* rcx = hFile, rdx = lDistanceToMove, r8 = 0, 1, 2 */
#if INLINE_ASM
	ASM
		"push rbx\n\t"
		"mov ebx, ecx\n\t"
		"mov eax, 0x4200\n\t"
		"mov al, r8b\n\t"
		"int 0x41\n\t"
		"pop rbx\n\t"
		END_ASM
#else
	//return SetFilePointer(hFile, lDistanceToMove, dwMoveMethod);
#endif
}

DWORD DOSAPI SetFilePointerL(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod) {
	/*
	This is the 64 bit version of the function, not yet to be documented
	rcx = hFile, rdx = lDistanceToMove, r8 = lpDistanceToMoveHigh, r9 = 0, 1, 2
	If r8=NULL then ignore this
	*/
#if INLINE_ASM
	ASM
		"push rbx\n\t"
		"mov ebx, ecx\n\t"
		"xor ecx, ecx\n\t"
		"test r8, r8\n\t"
		"cmovnz ecx, dword ptr [r8]\n\t"
		"mov eax, 0x4200\n\t"
		"mov al, r9b\n\t"
		"int 0x41\n\t"
		"pop rbx\n\t"
		END_ASM
#else
	//return SetFilePointerLA(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod);
#endif
}

DWORD DOSAPI GetFileAttributes(LPCSTR lpFileName) {
	//If the function fails, we return -1. 
	//Call get last error to get the error code
#if INLINE_ASM
	ASM
		"mov rdx, rcx\n\t"
		"mov eax, 0x4300\n\t"
		"int 0x41\n\t"
		"mov ecx, -1\n\t"
		"cmovc eax, ecx"
		END_ASM
#else
	//return GetFileAttributes(lpFileName);
#endif
}

DWORD DOSAPI SetFileAttributes(LPCSTR lpFileName, DWORD dwFileAttributes) {
#if INLINE_ASM
	ASM
		"xchg rdx, rcx\n\t"
		"mov eax, 0x4301\n\t"
		"int 0x41\n\t"
		"mov ecx, -1\n\t"
		"cmovc eax, ecx"
		END_ASM
#else
	//return SetFileAttributesA(lpFileName, dwFileAttributes);
#endif
}
//
// IOCTL FUNCTIONS HERE
//

BOOL DOSAPI DuplicateHandle(HANDLE hSourceHandle, LPHANDLE lpDestinationHandle) {
#if INLINE_ASM
	ASM
		"push rbx\n\t"
		"mov ebx, ecx\n\t"
		"mov eax, 0x4500\n\t"
		"xor ecx, ecx\n\t"
		"int 0x41\n\t"
		"cmovc eax, ecx\n\t"
		"jc dupExit\n\t"
		"mov dword ptr [rdx], eax\n\t"
		"mov eax, 1\n"
		"dupExit:"
		"pop rbx\n\t"
		END_ASM
#else
	//return DuplicateHandle(hSourceHandle, lpDestinationHandle);
#endif
}

BOOL DOSAPI ForceDuplicateHandle(HANDLE hSourceHandle, \
	HANDLE hDesiredDestinationHandle) {
	//If this function returns true, the user can begin using 
	// hDesiredDestinationHandle as the DUP2 handle
#if INLINE_ASM
	ASM
		"push rbx\n\t"
		"mov ebx, ecx\n\t"
		"mov ecx, edx\n\t"
		"mov eax, 0x4600\n\t"
		"int 0x41\n\t"
		"mov eax, 1\n\t"
		"mov ecx, 0\n\t"
		"cmovc eax, ecx\n\t"
		"pop rbx"
		END_ASM
#else
	//return ForceDuplicateHandleA(hSourceHandle, hDesiredDestinationHandle);
#endif
}

BOOL DOSAPI GetCurrentDirectory(DRIVE_LETTER dlDriveLetter, LPSTR lpDirectoryBuffer) {
	//lpDirectoryBuffer must be a 68 byte buffer
#if INLINE_ASM
	ASM
		"push rsi\n\t"
		"mov rsi, rdx\n\t"
		"mov edx, ecx\n\t"
		"sub edx, 0x41\n\t"
		"mov eax, 0x4700\n\t"
		"xor ecx, ecx\n\t"
		"int 0x41\n\t"
		"mov eax, 1\n\t"
		"cmovc eax, ecx\n\t"
		"pop rsi"
		END_ASM
#else
	//return GetCurrentDirectoryA(dlDriveLetter, lpDirectoryBuffer);
#endif
}

BOOL DOSAPI __FindFirst(LPCSTR lpFileName, FILE_ATTRIBUTES dwFileAttributes) {
#if INLINE_ASM
	ASM
		"xchg rcx, rdx\n\t"
		"and ecx, 0xFFFF\n\t"
		"mov eax, 0x4E00\n\t"
		"int 0x41\n\t"
		"mov ecx, 0\n\t"
		"mov eax, 1\n\t"
		"cmovc eax, ecx"
		END_ASM
#else
	//return __FindFirstA(lpFileName, dwFileAttributes);
#endif
}


//Be aware that "no more files" is a special error condition. Make sure to
// get the error code after this call!
BOOL DOSAPI FindFirstFile(LPCSTR lpFileName, FILE_ATTRIBUTES dwFileAttributes, \
	LPFFBlock lpFindFileBlock) {
	LPVOID oldDTA = __getDTA();
	__setDTA(lpFindFileBlock);
	BOOL retVal = __FindFirst(lpFileName, dwFileAttributes);
	__setDTA(oldDTA);
	return retVal;
}

BOOL DOSAPI __FindNext() {
#if INLINE_ASM
	ASM
		"mov eax, 0x4F00\n\t"
		"xor ecx, ecx\n\t"
		"int 0x41\n\t"
		"mov eax, 1\n\t"
		"cmovc eax, ecx"
		END_ASM
#else
	//return __FindNextA();
#endif
}

//Continues the search based on the FF Block returned in the DTA
BOOL DOSAPI FindNextFile(LPFFBlock lpFindFileBlock) {
	LPVOID oldDTA = __getDTA();
	__setDTA(lpFindFileBlock);
	BOOL retVal = __FindNext();
	__setDTA(oldDTA);
	return retVal;
}

//Closes the FindFirstBlock in the DTA. 
BOOL DOSAPI FindClose(LPFFBlock lpFindFileBlock) {
	return TRUE;
}

BOOL DOSAPI RenameFile(LPCSTR lpOldFileName, LPCSTR lpNewFileName) {
#if INLINE_ASM
	ASM
		"push rdi\n\t"
		"mov rdi, rdx\n\t"
		"mov rdx, rcx\n\t"
		"mov eax, 0x5600\n\t"
		"xor ecx, ecx\n\t"
		"int 0x41\n\t"
		"mov eax, 1\n\t"
		"cmovc eax, ecx\n\t"
		"pop rdi\n\t"
		END_ASM
#else
	//return RenameFileA(lpOldFileName, lpNewFileName);
#endif
}

BOOL DOSAPI GetFileDateAndTime(HANDLE hFile, LPFAT_TIME lpFileTime, LPFAT_DATE lpFileDate) {
#if INLINE_ASM
	ASM
		"push rbx\n\t"
		"mov r9, rdx\n\t"
		"mov ebx, ecx\n\t"
		"mov eax, 0x5700\n\t"
		"int 0x41\n\t"
		"pop rbx\n\t"
		"mov eax, 0\n\t"
		"jc getDateTimeExit\n\t"
		"inc eax\n\t"
		"mov word ptr [r9], cx\n\t"
		"mov word ptr [r8], dx\n"
		"getDateTimeExit:"
		END_ASM
#else
	//return GetFileDateAndTimeA(hFile, lpFileTime, lpFileDate);
#endif
}

BOOL DOSAPI SetFileDateAndTime(HANDLE hFile, FAT_TIME ftFileTime, FAT_DATE ftFileDate) {
#if INLINE_ASM
	ASM
		"push rbx\n\t"
		"mov ebx, ecx\n\t"
		"movzx ecx, dx\n\t"
		"movzx edx, r8w\n\t"
		"mov eax, 0x5701\n\t"
		"xor r8, r8\n\t"
		"int 0x41\n\t"
		"mov eax, 1 \n\t"
		"cmovc eax, r8d"
		END_ASM
#else
	//return SetFileDateAndTimeA(hFile, ftFileTime, ftFileDate);
#endif
}

//ASCIIZ Path must be at least 67 chars long and ending in a terminating slash
//If the handle is -1, error occured
HANDLE DOSAPI CreateTemporaryFile(LPSTR lpFileNameBuffer, FILE_ATTRIBUTES dwFileAttributes) {
#if INLINE_ASM
	ASM
		"xchg rdx, rcx\n\t"
		"mov eax, 0x5A00\n\t"
		"int 0x41\n\t"
		"mov ecx, -1\n\t"
		"cmovc eax, ecx"
		END_ASM
#else
	//return CreateTemporaryFileA(lpFileNameBuffer, dwFileAttributes);
#endif
};

HANDLE DOSAPI CreateUniqueFile(LPCSTR lpFileName, FILE_ATTRIBUTES dwFileAttributes) {
#if INLINE_ASM
	ASM
		"xchg rdx, rcx\n\t"
		"mov eax, 0x3C00\n\t"
		"int 0x41\n\t"
		"mov ecx, -1\n\t"
		"cmovc eax, ecx"
		END_ASM
#else
	//return CreateUniqueFileA(lpFileName, dwFileAttributes);
#endif
}

//lpFQFileName = 128 byte buffer
BOOL DOSAPI GetFQFileName(LPCSTR lpSourceFileName, LPSTR lpFQFileName) {
#if INLINE_ASM
	ASM
		"push rsi\n\t"
		"push rdi\n\t"
		"mov rsi, rcx\n\t"
		"mov rdi, rdx\n\t"
		"xor ecx, ecx\n\t"
		"mov eax, 0x6000\n\t"
		"int 0x41\n\t"
		"mov eax, 1\n\t"
		"cmovc eax, ecx\n\t"
		"pop rdi\n\t"
		"pop rsi"
		END_ASM
#else
	//return GetFQFileNameA(lpSourceFileName, lpFQFileName);
#endif
}

BOOL DOSAPI FlushFile(HANDLE hFile) {
#if INLINE_ASM
	ASM
		"push rbx\n\t"
		"mov ebx, ecx\n\t"
		"mov eax, 0x6800\n\t"
		"xor ecx, ecx\n\t"
		"int 0x41\n\t"
		"mov eax, 1\n\t"
		"cmovc eax, ecx"
		END_ASM
#else
	//return FlushFileA(hFile);
#endif
}