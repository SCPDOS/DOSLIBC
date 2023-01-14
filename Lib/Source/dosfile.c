
/* Start of the low level scpdos library which will be used to build stdlib.*/

/*Uses MS x64 ABI
 * Integer arguments only needed for DOS API so we only highlight them here
 *             Arguments passed in: rcx, rdx, r8, r9 then stack
 *       Return value is passed in: rax
 *              Volatile registers: rax, rcx, r8, r9, r10, r11
 *           Nonvolatile registers: rbx, rsp, rbp, r12, r13, r14, r15, rdi, rsi
 */

#include "../../Headers/scpdos.h"

BOOL WINAPI CreateDirectory(LPCSTR lpDirectoryName){
    ASM(
        "mov rdx, rcx\n\t"
        "mov eax, 0x3900\n\t"
        "xor ecx, ecx\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx"
    );
}

BOOL WINAPI DeleteDirectory(LPCSTR lpDirectoryName){
    ASM(
        "mov rdx, rcx\n\t"
        "mov eax, 0x3A00\n\t"
        "xor ecx, ecx\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx"
    );
}

BOOL WINAPI ChangeCurrentDirectory(LPCSTR lpDirectoryName){
    ASM(
        "mov rdx, rcx\n\t"
        "mov eax, 0x3B00\n\t"
        "xor ecx, ecx\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx"
    );
}

HANDLE WINAPI CreateFile(LPCSTR lpFileName, FILE_ATTRIBUTES dwFileAttributes){
    /*Swap the two parameters to get them in the right registers*/
    ASM (
        "xchg rdx, rcx\n\t"
        "mov eax, 0x3C00\n\t"
            "int 0x41\n\t"
        "mov ecx, -1\n\t"
        "cmovc eax, ecx"
    );  
}

HANDLE WINAPI OpenFile(LPCSTR lpFileName, FILE_OPEN_MODE dwOpenMode, \
    FILE_SHARE_MODE dwShareMode){
    /* rcx -> lpFileName, rdx = dwOpenMode  r8 = dwShareMode*/
    /* First clear bits 2 and 3 on the OpenMode */
    /* Then preserve only share bits in r8b (i.e. bits 4,5,6)*/
    ASM (
        "mov eax, 0x3D00\n\t"
        "and dl, 0xF3\n\t"
        "mov al, dl\n\t"
        "and r8b, 0x70\n\t "
        "or al, r8b\n\t"
        "mov rdx, rcx\n\t"
        "int 0x41\n\t"
        "mov ecx, -1\n\t"
        "cmovc eax, ecx"
    );  
}

BOOL WINAPI CloseFile(HANDLE hFile){
    /*If we return TRUE, then handle was closed*/
    ASM (
        "mov eax, 0x3E00\n\t"
        "push rbx\n\t"
        "mov ebx, ecx\n\t"
        "int 0x41\n\t"
        "pop rbx\n\t"
        "mov ecx, 1\n\t"
        "mov eax, 0\n\t"
        "cmovc eax, ecx"
    );
}

BOOL WINAPI ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, \
    LPDWORD lpNumberOfBytesRead){
        /*rcx = hFile, rdx -> lpBuffer, 
        r8 = nNumberOfBytesToRead, r9 -> NumberOfBytesRead*/
        ASM(
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
        );
    }

BOOL WINAPI WriteFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToWrite, \
    LPDWORD lpNumberOfBytesWritten){
        /*rcx = hFile, rdx -> lpBuffer, 
        r8 = nNumberOfBytesToWrite, r9 -> NumberOfBytesWritten*/
        ASM(
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
        );
    }
    
BOOL WINAPI DeleteFile(LPCSTR lpFileName){
    ASM(
        "mov rdx, rcx\n\t"
        "mov eax, 0x4100\n\t"
        "int 0x41\n\t"
        "mov ecx, 1\n\t"
        "mov eax, 0\n\t"
        "cmovc eax, ecx"
    );
}

DWORD WINAPI SetFilePointer(HANDLE hFile, LONG lDistanceToMove, DWORD dwMoveMethod){
        /* This is the 32 bit version of the function*/
        /* rcx = hFile, rdx = lDistanceToMove, r8 = 0, 1, 2 */
        ASM(
            "push rbx\n\t"
            "mov ebx, ecx\n\t"
            "mov eax, 0x4200\n\t"
            "mov al, r8b\n\t"
            "int 0x41\n\t"
            "pop rbx\n\t"
        );
    }

DWORD WINAPI SetFilePointerL(HANDLE hFile, LONG lDistanceToMove, \
    PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod){
        /* This is the 64 bit version of the function, not yet to be exported */
        /* rcx = hFile, rdx = lDistanceToMove, r8 = lpDistanceToMoveHigh, 
            r9 = 0, 1, 2 */
        /* If r8=NULL then ignore this*/
        ASM(
            "push rbx\n\t"
            "mov ebx, ecx\n\t"
            "xor ecx, ecx\n\t"
            "test r8, r8\n\t"
            "cmovnz ecx, dword ptr [r8]\n\t"
            "mov eax, 0x4200\n\t"
            "mov al, r9b\n\t"
            "int 0x41\n\t"
            "pop rbx\n\t"
        );
    }

DWORD WINAPI GetFileAttributes(LPCSTR lpFileName){
    //If the function fails, we return -1. 
    //Call get last error to get the error code
    ASM(
        "mov rdx, rcx\n\t"
        "mov eax, 0x4300\n\t"
        "int 0x41\n\t"
        "mov ecx, -1\n\t"
        "cmovc eax, ecx"
    );
}

DWORD WINAPI SetFileAttributes(LPCSTR lpFileName, DWORD dwFileAttributes){
    ASM(
        "xchg rdx, rcx\n\t"
        "mov eax, 0x4301\n\t"
        "int 0x41\n\t"
        "mov ecx, -1\n\t"
        "cmovc eax, ecx"
    );
}
//
// IOCTL FUNCTIONS HERE
//

BOOL WINAPI DuplicateHandle(HANDLE hSourceHandle, LPHANDLE lpDestinationHandle){
    ASM(
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
    );
}

BOOL WINAPI ForceDuplicateHandle(HANDLE hSourceHandle, \
    HANDLE hDesiredDestinationHandle){
        //If this function returns true, the user can begin using 
        // hDesiredDestinationHandle as the DUP2 handle
        ASM(
            "push rbx\n\t"
            "mov ebx, ecx\n\t"
            "mov ecx, edx\n\t"
            "mov eax, 0x4600\n\t"
            "int 0x41\n\t"
            "mov eax, 1\n\t"
            "mov ecx, 0\n\t"
            "cmovc eax, ecx\n\t"
            "pop rbx"
        );
}

BOOL WINAPI GetCurrentDirectory(DRIVE_LETTER dlDriveLetter, LPSTR lpDirectoryBuffer){
    //lpDirectoryBuffer must be a 68 byte buffer
    ASM(
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
    );
}

BOOL WINAPI __FindFirst(LPCSTR lpfileName, FILE_ATTRIBUTES dwFileAttributes){
        ASM(
        "xchg rcx, rdx\n\t"
        "and ecx, 0xFFFF\n\t"
        "mov eax, 0x4E00\n\t"
        "int 0x41\n\t"
        "mov ecx, 0\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx"
    );
}


//Be aware that "no more files" is a special error condition. Make sure to
// get the error code after this call!
BOOL WINAPI FindFirstFile(LPCSTR lpfileName, FILE_ATTRIBUTES dwFileAttributes, \
    LPFFBlock lpFindFileBlock){
        LPVOID oldDTA = __getDTA();
        __setDTA(lpFindFileBlock);
        BOOL retVal = __FindFirst(lpfileName, dwFileAttributes);
        __setDTA(oldDTA);
        return retVal;
}

BOOL WINAPI __FindNext(){
    ASM(
        "mov eax, 0x4F00\n\t"
        "xor ecx, ecx\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx"
    );
}

//Continues the search based on the FF Block returned in the DTA
BOOL WINAPI FindNextFile(LPFFBlock lpFindFileBlock){
        LPVOID oldDTA = __getDTA();
        __setDTA(lpFindFileBlock);
        BOOL retVal = __FindNext();
        __setDTA(oldDTA);
        return retVal;
}

//Closes the FindFirstBlock in the DTA. 
BOOL WINAPI FindClose(LPFFBlock lpFindFileBlock){
    return TRUE;
}

BOOL WINAPI RenameFile(LPCSTR lpOldFileName, LPCSTR lpNewFileName){
    ASM(
        "push rdi\n\t"
        "mov rdi, rdx\n\t"
        "mov rdx, rcx\n\t"
        "mov eax, 0x5600\n\t"
        "xor ecx, ecx\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx\n\t"
        "pop rdi\n\t"
    );
}

BOOL WINAPI GetFileDateAndTime(HANDLE hFile, LPFAT_TIME lpFileTime,\
    LPFAT_DATE lpFileDate){
        ASM(
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
        );
    }
BOOL WINAPI SetFileDateAndTime(HANDLE hFile, FAT_TIME ftFileTime, FAT_DATE ftFileDate){
    ASM (
        "push rbx\n\t"
        "mov ebx, ecx\n\t"
        "movzx ecx, dx\n\t"
        "movzx edx, r8w\n\t"
        "mov eax, 0x5701\n\t"
        "xor r8, r8\n\t"
        "int 0x41\n\t"
        "mov eax, 1 \n\t"
        "cmovc eax, r8d"
    );
}

//ASCIIZ Path must be at least 67 chars long and ending in a terminating slash
//If the handle is -1, error occured
HANDLE WINAPI CreateTemporaryFile(LPSTR lpFileNameBuffer, \
    FILE_ATTRIBUTES dwFileAttributes){
        ASM (
            "xchg rdx, rcx\n\t"
            "mov eax, 0x5A00\n\t"
            "int 0x41\n\t"
            "mov ecx, -1\n\t"
            "cmovc eax, ecx"
        );
};

HANDLE WINAPI CreateUniqueFile(LPCSTR lpFileName, FILE_ATTRIBUTES dwFileAttributes){
    ASM (
    "xchg rdx, rcx\n\t"
    "mov eax, 0x3C00\n\t"
    "int 0x41\n\t"
    "mov ecx, -1\n\t"
    "cmovc eax, ecx"
    );  
}

//Buffer MUST be at least 128 bytes!!!
BOOL WINAPI GetFileTrueName(LPCSTR lpFileNameToQualify, LPSTR lpBufferForFileName){
    ASM (
        "push rsi\n\t"
        "push rdi\n\t"
        "mov rsi, rcx\n\t"
        "mov rdi, rdx\n\t"
        "mov eax, 0x6000\n\t"
        "xor ecx, ecx\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx"
    );
}

BOOL WINAPI FlushFile(HANDLE hFile){
    ASM(
        "push rbx\n\t"
        "mov ebx, ecx\n\t"
        "mov eax, 0x6800\n\t"
        "xor ecx, ecx\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx"
    );
}