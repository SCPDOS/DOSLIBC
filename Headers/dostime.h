#ifndef _DOSTIME_H
#define _DOSTIME_H
#include "basetsd.h"

VOID WINAPI GetDate(LPCH lpDayOfTheWeek, LPWORD lpYearOffset, LPCH lpMonth, LPCH lpDayOfTheMonth);
BOOL WINAPI SetDate(WORD year, CHAR month, CHAR day);
VOID WINAPI GetTime(LPCH lpHour, LPCH lpMinute, LPCH lpSeconds, LPCH lpHSeconds);
BOOL WINAPI SetTime(CHAR hour, CHAR minute, CHAR seconds, CHAR hSeconds);
#endif
