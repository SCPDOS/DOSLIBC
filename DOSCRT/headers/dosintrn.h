// This is a file used for specifying DOS internal data structures and 
// prototypes for special functions such as 41h/AH=52h etc.

#ifndef _INTERNAL_H
#define _INTERNAL_H

#include "basetsd.h"
#include "dosdisk.h"
#include "dosdrvr.h"

typedef QWORD PROCESS_ID;

typedef struct _drive_parameter_block{
    DRIVE_INDEX bDriveIndex;
    BYTE bDriverUnitNumber;
    WORD wBytesPerSector;
    BYTE bMaxSectorInCluster;
    BYTE bSectorPerClusterShift;
    WORD wFATOffset;
    BYTE bNumberOfFATs;
    WORD wNumberOfRootDirectoryEntries;
    DWORD dwClusterHeapOffset;
    DWORD dwFATLength;
    union{
        WORD wSectorOfRootDirectory;
        DWORD dwClusterOfRootDirectory;
    } dwFirstUnitOfRootDirectory;
    LPDEVDRV_HEADER lpDeviceDriverHeader;
    BYTE bMediaDescriptor;
    BYTE bAccessFlag;
    struct _drive_parameter_block *lpNextDPB;
    DWORD dwFirstFreeCluster;
    DWORD dwNumberOfFreeClusters;
} DPB, *PDPB, *LPDPB;


BOOL DOSAPI GetDefaultDiskDPBPointer(LPDPB lpDPB);
BOOL DOSAPI GetDPBPointer(DRIVE_NUMBER bNumber, LPDPB lpDPB);
VOID DOSAPI SetCurrentProcessId(PROCESS_ID pid);
PROCESS_ID DOSAPI GetCurrentProcessId();
LPVOID DOSAPI GetPointerToDosSysVars();
VOID DOSAPI GenerateDPB(LPVOID lpBPB, LPDPB lpDPB);
VOID DOSAPI GeneratePartialPSP(LPVOID lpPSPAddress);
VOID DOSAPI GenerateNewPSP(LPVOID lpPSPAddress, DWORD dwSizeOfPSPAllocation);
LPCH DOSAPI GetPtrToInDOSFlag();
CHAR GetSwitchChar();
VOID SetSwitchChar(CHAR switchChar);
#endif