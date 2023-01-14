#ifndef _DOSINTR_H
#define _DOSINTR_H
#include "basetsd.h"
typedef struct _countryInformation{
    WORD dateTimeFormat;
    CHAR currencyString[5];
    CHAR thousandsSeparator[2];
    CHAR decimalSeparator[2];
    CHAR dateSeparator[2];
    CHAR timeSeparator[2];
    BYTE currencyFormat;
    BYTE numberOfDigitsAfterDecimal;
    BYTE timeFormat;
    LPVOID caseMapPointer;
    CHAR dataSeparator[2];
    CHAR reserved[10];
} COUNTRY_BLOCK, *PCOUNTRY_BLOCK, *LPCOUNTRY_BLOCK;

#define DATE_US 0
#define DATE_EU 1
#define DATE_JP 2

#define CUR_SYMBOL_LEAD_NOSPACE     0
#define CUR_SYMBOL_FOLLOW_NOSPACE   1
#define CUR_SYMBOL_LEAD_ONESPACE    2
#define CUR_SYMBOL_FOLLOW_ONESPACE  3
#define CUR_SYMBOL_REPLACE_DECIMAL  4

#define TIME_FORMAT_12HR    0
#define TIME_FORMAT_24HR    1


VOID WINAPI GetCountryInformation(LPCOUNTRY_BLOCK lpCountryBlock);
#endif