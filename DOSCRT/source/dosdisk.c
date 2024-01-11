#include "../headers/scpdos.h"

#if !INLINE_ASM
#include "../headers/asm/asmdisk.h"
#endif

//GLOBAL VARIABLES
WORD rawIOError = 0;    //This is where raw disk IO saves its error code.

VOID DOSAPI DiskReset(){
#if INLINE_ASM
    ASM
        "mov eax, 0x0D00\n\t"
        "int 0x21"
    END_ASM
#else
    //DiskResetA();
#endif
}

VOID DOSAPI SetDefaultDrive(DRIVE_INDEX bDiskIndex){
#if INLINE_ASM
    ASM
        "movzx edx, cl\n\t"
        "mov eax, 0x0E00\n\t"
        "int 0x21"
    END_ASM
#else
    //SetDefaultDriveA(bDiskIndex);
#endif
}

DRIVE_INDEX DOSAPI GetDefaultDrive(){
#if INLINE_ASM
    ASM
        "mov eax, 0x1900\n\t"
        "int 0x21"
    END_ASM
#else
    //return GetDefaultDriveA();
#endif
}

BOOL DOSAPI GetDiskFATInfo(DRIVE_NUMBER bDriveNumber, LPDWORD lpBytesPerSector, \
    LPDWORD lpSectorsPerCluster, LPDWORD lpTotalNumberOfClusters, \
    LPVOID *lpMediaDescriptor){
        return FALSE;
    }

BOOL DOSAPI GetDefaultDiskFATInfo(LPDWORD lpBytesPerSector, \
    LPDWORD lpSectorsPerCluster, LPDWORD lpTotalNumberOfClusters, \
    LPVOID *lpMediaDescriptor){
        return FALSE;
    }
    
BOOL DOSAPI GetDiskFreeSpace(DRIVE_NUMBER bDriveNumber, LPDWORD lpSectorsPerCluster, \
    LPDWORD lpBytesPerSector, LPDWORD lpNumberOfFreeClusters, \
    LPDWORD lpTotalNumberOfFreeClusters){
        return FALSE;
    }

BYTE DOSAPI GetDiskReadVerifyFlag(){
#if INLINE_ASM
    ASM
        "mov eax, 0x5400\n\t"
        "int 0x21\n\t"
    END_ASM
#else
    //GetDiskReadVerifyFlagA();
#endif
}

CHAR DOSAPI __ReadDiskRaw(LPVOID lpBuffer, DRIVE_INDEX diIndex, QWORD qwStartSector, DWORD dwNumberOfSectors){
#if INLINE_ASM
    ASM
        "push rbx\n\t"
        "mov rbx, rcx\n\t"
        "movzx eax, dl\n\t"
        "mov ecx, r9d\n\t"
        "mov rdx, r8\n\t"
        "int 0x25\n\t"
        "jc rawInError\n\t"
        "xor eax, eax\n"
        "rawInError:\n\t"
        "popfq\n\t"
        "pop rbx\n\t"
    END_ASM
#else
    //return __ReadDiskRawA(lpBuffer, diIndex, qwStartSector, dwNumberOfSectors);
#endif
}

CHAR DOSAPI __WriteDiskRaw(LPVOID lpBuffer, DRIVE_INDEX diIndex, QWORD qwStartSector, DWORD dwNumberOfSectors){
#if INLINE_ASM
    ASM
        "push rbx\n\t"
        "mov rbx, rcx\n\t"
        "movzx eax, dl\n\t"
        "mov ecx, r9d\n\t"
        "mov rdx, r8\n\t"
        "int 0x26\n\t"
        "jc rawOutError\n\t"
        "xor eax, eax\n"
        "rawOutError:\n\t"
        "and eax, 0xFFFF\n\t"
        "popfq\n\t"
        "pop rbx\n\t"
    END_ASM
#else
    //return __WriteDiskRawA(lpBuffer, diIndex, qwStartSector, dwNumberOfSectors);
#endif
}

BOOL DOSAPI ReadDiskRaw (LPVOID lpBuffer, DRIVE_INDEX diIndex, QWORD qwStartSector, DWORD dwNumberOfSectors){
    BOOL retCode = TRUE;
    WORD errorCode = __ReadDiskRaw(lpBuffer, diIndex, qwStartSector, dwNumberOfSectorsEND_ASM
    if(!errorCode){
        rawIOError = errorCode;
        retCode = FALSE;
    }
}
BOOL DOSAPI WriteDiskRaw (LPVOID lpBuffer, DRIVE_INDEX diIndex, QWORD qwStartSector, DWORD dwNumberOfSectors){
    BOOL retCode = TRUE;
    WORD errorCode = __WriteDiskRaw(lpBuffer, diIndex, qwStartSector, dwNumberOfSectorsEND_ASM
    if(!errorCode){
        rawIOError = errorCode;
        retCode = FALSE;
    }
}