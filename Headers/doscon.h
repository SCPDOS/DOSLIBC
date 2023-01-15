#ifndef _DOSCON_H
#define _DOSCON_H
#include "basetsd.h"

CHAR DOSAPI GetChar();
VOID DOSAPI PutChar(CHAR c);
CHAR DOSAPI AuxInput();
VOID DOSAPI AuxOutput(CHAR c);
VOID DOSAPI PrnOutput(CHAR c);
BOOL DOSAPI DirectConInAsync(LPCH c);
VOID DOSAPI DirectConOutAsync(CHAR c);
CHAR DOSAPI DirectConIn();
CHAR DOSAPI ConInput();
VOID DOSAPI WriteString(LPCSTR lpString);
VOID DOSAPI GetBufferedInput(LPSTR lpString, BYTE bufferLen);
BOOL DOSAPI GetConInputStatus();
VOID DOSAPI ClearInputBuffer();

#endif