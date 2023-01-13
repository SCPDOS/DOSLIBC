#include "../../Headers/scpdos.h"

VOID PUBLIC DiskReset(){
    __asm__ __volatile__(
        "mov eax, 0x0D00\n\t"
        "int 0x41"
    );
}

VOID PUBLIC SetDefaultDrive(DRIVE_INDEX bDiskIndex){
    __asm__ __volatile__(
        "movzx edx, cl\n\t"
        "mov eax, 0x0E00\n\t"
        "int 0x41"
    );
}

DRIVE_INDEX PUBLIC GetDefaultDrive(){
    __asm__ __volatile__(
        "mov eax, 0x1900\n\t"
        "int 0x41"
    );
}

BOOL PUBLIC GetDiskFATInfo(DRIVE_NUMBER bDriveNumber, LPDWORD lpBytesPerSector, \
    LPDWORD lpSectorsPerCluster, LPDWORD lpTotalNumberOfClusters, \
    LPVOID *lpMediaDescriptor){
        return FALSE;
    }

BOOL PUBLIC GetDefaultDiskFATInfo(LPDWORD lpBytesPerSector, \
    LPDWORD lpSectorsPerCluster, LPDWORD lpTotalNumberOfClusters, \
    LPVOID *lpMediaDescriptor){
        return FALSE;
    }
    
BOOL PUBLIC GetDiskFreeSpace(DRIVE_NUMBER bDriveNumber, LPDWORD lpSectorsPerCluster, \
    LPDWORD lpBytesPerSector, LPDWORD lpNumberOfFreeClusters, \
    LPDWORD lpTotalNumberOfFreeClusters){
        return FALSE;
    }

BYTE PUBLIC GetDiskReadVerifyFlag(){
    __asm__ __volatile__(
        "mov eax, 0x5400\n\t"
        "int 0x41\n\t"
    );
}