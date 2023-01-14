//
// Basic type definitions
//

#ifndef _BASETSD_H
#define _BASETSD_H

#ifdef PUBLIC 
#undef PUBLIC
#endif

#ifdef PRIVATE
#undef PRIVATE
#endif

#ifdef COMPILER
#undef COMPILER
#endif

#ifdef CC_MSVC
#undef CC_MSVC
#define CC_MSVC 1
#endif

#ifdef CC_GCC
#undef CC_GCC
#define CC_GCC 2
#endif

#if defined(_MSC_VER)
#define WINAPI __fastcall
#define COMPILER CC_MSVC
#elif defined(__GNUC__)
#define WINAPI __attribute__((ms_abi))
#define COMPILER CC_GCC
#endif

#define ASM __asm__ __volatile__

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

typedef char CHAR;
typedef short SHORT;
typedef int INT;
typedef long LONG;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned long QWORD;

typedef int          BOOL;
typedef float        FLOAT;
typedef FLOAT       *PFLOAT;
typedef BOOL        *PBOOL;
typedef BOOL        *LPBOOL;
typedef BYTE        *PBYTE;
typedef BYTE        *LPBYTE;
typedef int         *PINT;
typedef int         *LPINT;
typedef WORD        *PWORD;
typedef WORD        *LPWORD;
typedef long        *PLONG;
typedef long        *LPLONG;
typedef DWORD       *PDWORD;
typedef DWORD       *LPDWORD;
typedef void        *LPVOID;
typedef CONST void  *LPCVOID;

typedef long INT_PTR, *PINT_PTR;
typedef unsigned long UINT_PTR, *PUINT_PTR;

typedef long LONG_PTR, *PLONG_PTR;
typedef unsigned long ULONG_PTR, *PULONG_PTR;

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