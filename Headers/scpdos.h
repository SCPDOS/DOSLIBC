/*
    The start of a DOS low level library upon which stdlib (newlib) will be 
    built!
*/

#ifndef _DOS_H
#define _DOS_H
#pragma pack(1) //Ensure all structs are aligned to 1 byte boundaries

#include "basetsd.h"
#include "dosdisk.h"
#include "doserror.h"
#include "internal.h"
#include "dosdrvr.h"
#include "dosfcb.h"
#include "dosfile.h"
#include "dosexec.h"
#include "dosmem.h"
#include "doscon.h"
#include "dosnet.h"
#include "dostime.h"
#include "dosintr.h"

VOID WINAPI SetInterruptVector(DWORD dwInterruptVector, LPVOID lpInterruptHandler);
LPVOID WINAPI GetInterruptVector(DWORD dwInterruptVector);
VOID WINAPI SetDiskVerifyState();
VOID WINAPI ClearDiskVerifyState();
WORD WINAPI GetDOSVersion();
BOOL WINAPI GetCtrlBreakState();
VOID WINAPI SetCtrlBreakState(BOOL bState);
#endif