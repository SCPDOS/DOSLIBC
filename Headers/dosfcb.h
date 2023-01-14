
#include "basetsd.h"
#include "dosfile.h"
#include "dosdisk.h"

#ifndef _DOSFCB_H
#define _DOSFCB_H

typedef struct _fcb{
    union{
        DRIVE_NUMBER dnDriveNumber;
        DRIVE_INDEX diDriveIndex;
    } drive;
    DRIVE_NUMBER bDriveNumber;
    LPCSTR lpFcbName[8];
    LPCSTR lpFcbExtention[3];
    PBYTE reserved[23];
} FCB, *PFCB, *LPFCB;

typedef struct _extended_fcb{
    BYTE bExtendedFlag;  //Must be set to -1
    PBYTE reserved2[5];
    FILE_ATTRIBUTES dwFileAttribute :8;  //Use only low 8 bits of file attribs
    union{
        DRIVE_NUMBER dnDriveNumber;
        DRIVE_INDEX diDriveIndex;
    } drive;
    LPCSTR lpFcbName[8];
    LPCSTR lpFcbExtention[3];
    PBYTE reserved[23];
} EXTENDED_FCB, *PEXTENDED_FCB, *LPEXTENDED_FCB;

typedef CHAR PARSE_MODE, *PPARSE_MODE, *LPPARSE_MODE;

VOID WINAPI __setDTA(LPVOID lpDTA);
LPVOID WINAPI __getDTA();

CHAR WINAPI ParseFileName(LPCSTR lpFileName, LPFCB lpFCB, PARSE_MODE pm);
LPSTR WINAPI GetFQPFileName(LPCSTR lpSourceFileName, LPSTR lpFQFileName);
#endif