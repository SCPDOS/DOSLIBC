#include "basetsd.h"

#ifndef _DOSCON_H
#define _DOSCON_H

CHAR WINAPI GetChar();
VOID WINAPI PutChar(CHAR c);
CHAR WINAPI AuxInput();
VOID WINAPI AuxOutput(CHAR c);
VOID WINAPI PrnOut(CHAR c);
BOOL WINAPI DirectConInA(LPCH c);
VOID WINAPI DirectConOutA(CHAR c);
CHAR WINAPI DirectConIn();
CHAR WINAPI ConInput();
VOID WINAPI WriteString(LPCSTR lpString);
VOID WINAPI GetBufferedInput(LPSTR lpString, BYTE bufferLen);
BOOL WINAPI GetConInputStatus();
VOID WINAPI ClearInputBuffer();

#endif