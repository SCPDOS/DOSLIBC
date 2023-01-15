#ifndef _DOSSTATE_H
#define _DOSSTATE_H

#include "basetsd.h"

VOID DOSAPI SetInterruptVector(DWORD dwInterruptVector, LPVOID lpInterruptHandler);
LPVOID DOSAPI GetInterruptVector(DWORD dwInterruptVector);
VOID DOSAPI SetDiskVerifyState();
VOID DOSAPI ClearDiskVerifyState();
WORD DOSAPI GetDOSVersion();
BOOL DOSAPI GetCtrlBreakState();
VOID DOSAPI SetCtrlBreakState(BOOL bState);
#endif