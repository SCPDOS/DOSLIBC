// File related macros and file headers go here

#include "basetsd.h"
#include "dosdisk.h"

#ifndef _DOSFILE_H
#define _DOSFILE_H

#ifndef STDIN
#define STDIN 0x00
#endif

#ifndef STDOUT
#define STDOUT 0x01
#endif

#ifndef STDERR
#define STDERR 0x02
#endif

#ifndef STDAUX
#define STDAUX 0x03
#endif

#ifndef STDPRN
#define STDPRN 0x04
#endif

/*Create Mode/File attribute definitions bit definitions*/
typedef DWORD FILE_ATTRIBUTES, *PFILE_ATTRIBUTES, *LPFILE_ATTRIBUTES;

#ifndef FILE_READ_ONLY
#define FILE_READ_ONLY          0x01
#endif

#ifndef FILE_HIDDEN
#define FILE_HIDDEN             0x02
#endif

#ifndef FILE_SYSTEM
#define FILE_SYSTEM             0x04
#endif

#ifndef FILE_ARCHIVE
#define FILE_ARCHIVE            0x20
#endif

/* The following are defined for file searches but MUST NOT be used for file 
    creations. DOS will return an error if these bits are set */

#ifndef FILE_VOLUME_LABEL
#define FILE_VOLUME_LABEL       0x08
#endif

#ifndef FILE_DIRECTORY
#define FILE_DIRECTORY          0x10
#endif

/*Open Mode bit definitions*/
typedef DWORD FILE_OPEN_MODE, *PFILE_OPEN_MODE, *LPFILE_OPEN_MODE;
typedef DWORD FILE_SHARE_MODE, *PFILE_SHARE_MODE, *LPFILE_SHARE_MODE;

#ifndef OPEN_READ
#define OPEN_READ               0x00
#endif

#ifndef OPEN_WRITE
#define OPEN_WRITE              0x01
#endif

#ifndef OPEN_READ_WRITE
#define OPEN_READ_WRITE         0x02
#endif

#ifndef OPEN_INHERIT        
#define OPEN_INHERIT            0x80
#endif

#ifndef SHARE_COMPAT
#define SHARE_COMPAT            0x00
#endif

#ifndef SHARE_DENY_READ_WRITE
#define SHARE_DENY_READ_WRITE   0x10
#endif

#ifndef SHARE_DENY_WRITE
#define SHARE_DENY_WRITE        0x20
#endif

#ifndef SHARE_DENY_READ
#define SHARE_DENY_READ         0x30
#endif

#ifndef SHARE_DENY_NONE
#define SHARE_DENY_NONE         0x40
#endif


/*LSEEK modes*/
#ifndef FILE_BEGIN
#define FILE_BEGIN    0x0
#endif

#ifndef FILE_CURRENT
#define FILE_CURRENT  0x1
#endif

#ifndef FILE_END
#define FILE_END      0x2
#endif

/*Find First Structure*/

typedef struct _find_first_block{
    BYTE Reserved[21];
    FILE_ATTRIBUTES bFileAttribute : 8;
    FAT_TIME ftFileTime;
    FAT_DATE fdFileDate;
    DWORD dwFileSize;
    CONST CHAR fileName[13];
} FFBlock, *PFFBlock, *LPFFBlock;

BOOL WINAPI CreateDirectory(LPCSTR lpDirectoryName);
BOOL WINAPI DeleteDirectory(LPCSTR lpDirectoryName);
BOOL WINAPI ChangeCurrentDirectory(LPCSTR lpDirectoryName);
HANDLE WINAPI CreateFile(LPCSTR lpFileName, FILE_ATTRIBUTES dwFileAttributes);
HANDLE WINAPI OpenFile(LPCSTR lpFileName, FILE_OPEN_MODE dwOpenMode, FILE_SHARE_MODE dwShareMode);
BOOL WINAPI CloseFile(HANDLE hFile);
BOOL WINAPI ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,  LPDWORD lpNumberOfBytesRead);
BOOL WINAPI WriteFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten);
BOOL WINAPI DeleteFile(LPCSTR lpFileName);
DWORD WINAPI SetFilePointer(HANDLE hFile, LONG lDistanceToMove, DWORD dwMoveMethod);
DWORD WINAPI SetFilePointerL(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
DWORD WINAPI GetFileAttributes(LPCSTR lpFileName);
DWORD WINAPI SetFileAttributes(LPCSTR lpFileName, DWORD dwFileAttributes);
BOOL WINAPI DuplicateHandle(HANDLE hSourceHandle, LPHANDLE lpDestinationHandle);
BOOL WINAPI ForceDuplicateHandle(HANDLE hSourceHandle, HANDLE hDesiredDestinationHandle);
BOOL WINAPI GetCurrentDirectory(DRIVE_LETTER dlDriveLetter, LPSTR lpDirectoryBuffer);
BOOL WINAPI FindFirstFile(LPCSTR lpfileName, FILE_ATTRIBUTES dwFileAttributes, LPFFBlock lpFindFileBlock);
BOOL WINAPI FindNextFile(LPFFBlock lpFindFileBlock);
BOOL WINAPI FindClose(LPFFBlock lpFindFileBlock);
BOOL WINAPI RenameFile(LPCSTR lpOldFileName, LPCSTR lpNewFileName);
HANDLE WINAPI CreateTemporaryFile(LPSTR lpFileNameBuffer, FILE_ATTRIBUTES dwFileAttributes);
HANDLE WINAPI CreateUniqueFile(LPCSTR lpFileName, FILE_ATTRIBUTES dwFileAttributes);
BOOL WINAPI GetFileTrueName(LPCSTR lpFileNameToQualify, LPSTR lpBufferForFileName);
BOOL WINAPI FlushFile(HANDLE hFile);

#endif