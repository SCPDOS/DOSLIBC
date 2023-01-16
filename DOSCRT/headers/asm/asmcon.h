
#ifndef _ASMCON_H
#define _ASMCON_H

#include "../scpdos.h"

CHAR DOSAPI GetCharA();
VOID DOSAPI PutCharA(CHAR c);
CHAR DOSAPI AuxInputA();
VOID DOSAPI AuxOutputA(CHAR c);
VOID DOSAPI PrnOutputA(CHAR c);
BOOL DOSAPI DirectConInAsyncA(LPCH c);
VOID DOSAPI DirectConOutAsyncA(CHAR c);
CHAR DOSAPI DirectConInA();
CHAR DOSAPI ConInputA();
VOID DOSAPI __WriteStringA(LPCSTR lpString, int len);
VOID DOSAPI __GetBufferedInputA(LPSTR lpString);
BOOL DOSAPI GetConInputStatusA();
VOID DOSAPI ClearInputBufferA();

#endif