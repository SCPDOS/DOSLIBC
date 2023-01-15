#ifndef _DOSTIME_H
#define _DOSTIME_H

#include "basetsd.h"

VOID DOSAPI GetDate(LPCH lpDayOfTheWeek, LPWORD lpYearOffset, LPCH lpMonth, LPCH lpDayOfTheMonth);
BOOL DOSAPI SetDate(WORD year, CHAR month, CHAR day);
VOID DOSAPI GetTime(LPCH lpHour, LPCH lpMinute, LPCH lpSeconds, LPCH lpHSeconds);
BOOL DOSAPI SetTime(CHAR hour, CHAR minute, CHAR seconds, CHAR hSeconds);
#endif
