//
// Basic type definitions
//

#ifndef _BASETSD_H
#define _BASETSD_H
//Use standard numerical types for ease of handling multiple compilers
#include <stdint.h>

#include "dosmac.h"

#ifndef VOID
#define VOID void
#endif

#ifndef CONST
#define CONST const
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef NULL
#define NULL ((VOID*)0)
#endif

#ifndef BAD_HANDLE
#define BAD_HANDLE 0xFFFFFFFFFFFFFFFF
#endif

typedef int8_t CHAR;
typedef int16_t SHORT;
typedef int32_t INT;
typedef int64_t LONG;

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint64_t QWORD;

typedef int32_t      BOOL;
typedef float        FLOAT;
typedef FLOAT       *PFLOAT;
typedef BOOL        *PBOOL;
typedef BOOL        *LPBOOL;
typedef BYTE        *PBYTE;
typedef BYTE        *LPBYTE;
typedef int32_t     *PINT;
typedef int32_t     *LPINT;
typedef WORD        *PWORD;
typedef WORD        *LPWORD;
typedef uint64_t    *PLONG;
typedef uint64_t    *LPLONG;
typedef DWORD       *PDWORD;
typedef DWORD       *LPDWORD;
typedef void        *LPVOID;
typedef CONST void  *LPCVOID;

typedef int32_t INT_PTR, *PINT_PTR;
typedef uint32_t UINT_PTR, *PUINT_PTR;

typedef int64_t LONG_PTR, *PLONG_PTR;
typedef uint64_t ULONG_PTR, *PULONG_PTR;

//
// ANSI (Multi-byte Character) types
//
typedef CHAR *PCHAR, *LPCH, *PCH;
typedef CONST CHAR *LPCCH, *PCCH;

typedef  CHAR *NPSTR, *LPSTR, *PSTR;
typedef  PSTR *PZPSTR;
typedef  CONST PSTR *PCZPSTR;
typedef  CONST CHAR *LPCSTR, *PCSTR;
typedef  PCSTR *PZPCSTR;
typedef  CONST PCSTR *PCZPCSTR;

typedef  CHAR *PNZCH;
typedef  CONST CHAR *PCNZCH;

typedef BYTE  BOOLEAN;           
typedef BOOLEAN *PBOOLEAN; 

typedef VOID *HANDLE;
typedef HANDLE *PHANDLE, *LPHANDLE;


//The maximum number of bytes to which a pointer can point. 
//Use for a count that must span the full range of a pointer.
typedef ULONG_PTR SIZE_T, *PSIZE_T;
typedef LONG_PTR SSIZE_T, *PSSIZE_T;

#endif