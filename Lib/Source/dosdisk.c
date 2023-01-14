#include "../../Headers/scpdos.h"

//GLOBAL VARIABLES
WORD rawIOError = 0;    //This is where raw disk IO saves its error code.

VOID WINAPI DiskReset(){
    ASM(
        "mov eax, 0x0D00\n\t"
        "int 0x41"
    );
}

VOID WINAPI SetDefaultDrive(DRIVE_INDEX bDiskIndex){
    ASM(
        "movzx edx, cl\n\t"
        "mov eax, 0x0E00\n\t"
        "int 0x41"
    );
}

DRIVE_INDEX WINAPI GetDefaultDrive(){
    ASM(
        "mov eax, 0x1900\n\t"
        "int 0x41"
    );
}

BOOL WINAPI GetDiskFATInfo(DRIVE_NUMBER bDriveNumber, LPDWORD lpBytesPerSector, \
    LPDWORD lpSectorsPerCluster, LPDWORD lpTotalNumberOfClusters, \
    LPVOID *lpMediaDescriptor){
        return FALSE;
    }

BOOL WINAPI GetDefaultDiskFATInfo(LPDWORD lpBytesPerSector, \
    LPDWORD lpSectorsPerCluster, LPDWORD lpTotalNumberOfClusters, \
    LPVOID *lpMediaDescriptor){
        return FALSE;
    }
    
BOOL WINAPI GetDiskFreeSpace(DRIVE_NUMBER bDriveNumber, LPDWORD lpSectorsPerCluster, \
    LPDWORD lpBytesPerSector, LPDWORD lpNumberOfFreeClusters, \
    LPDWORD lpTotalNumberOfFreeClusters){
        return FALSE;
    }

BYTE WINAPI GetDiskReadVerifyFlag(){
    ASM(
        "mov eax, 0x5400\n\t"
        "int 0x41\n\t"
    );
}

CHAR WINAPI __ReadDiskRaw(LPVOID lpBuffer, DRIVE_INDEX diIndex, QWORD qwStartSector, DWORD dwNumberOfSectors){
    ASM(
        "push rbx\n\t"
        "mov rbx, rcx\n\t"
        "movzx eax, dl\n\t"
        "mov ecx, r9d\n\t"
        "mov rdx, r8\n\t"
        "int 0x45\n\t"
        "jc rawInError\n\t"
        "xor eax, eax\n"
        "rawInError:\n\t"
        "popfq\n\t"
        "pop rbx\n\t"
    );
}

CHAR WINAPI __WriteDiskRaw(LPVOID lpBuffer, DRIVE_INDEX diIndex, QWORD qwStartSector, DWORD dwNumberOfSectors){
    ASM(
        "push rbx\n\t"
        "mov rbx, rcx\n\t"
        "movzx eax, dl\n\t"
        "mov ecx, r9d\n\t"
        "mov rdx, r8\n\t"
        "int 0x46\n\t"
        "jc rawOutError\n\t"
        "xor eax, eax\n"
        "rawOutError:\n\t"
        "and eax, 0xFFFF\n\t"
        "popfq\n\t"
        "pop rbx\n\t"
    );
}

BOOL WINAPI ReadDiskRaw (LPVOID lpBuffer, DRIVE_INDEX diIndex, QWORD qwStartSector, DWORD dwNumberOfSectors){
    BOOL retCode = TRUE;
    WORD errorCode = __ReadDiskRaw(lpBuffer, diIndex, qwStartSector, dwNumberOfSectors);
    if(!errorCode){
        rawIOError = errorCode;
        retCode = FALSE;
    }
}
BOOL WINAPI WriteDiskRaw (LPVOID lpBuffer, DRIVE_INDEX diIndex, QWORD qwStartSector, DWORD dwNumberOfSectors){
    BOOL retCode = TRUE;
    WORD errorCode = __WriteDiskRaw(lpBuffer, diIndex, qwStartSector, dwNumberOfSectors);
    if(!errorCode){
        rawIOError = errorCode;
        retCode = FALSE;
    }
}