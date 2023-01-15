#include "scpdos.h"
#include "../Headers/io.h"

int umask = 0;   //Global variable which masks which bits we can set 

int _close(int fd){
     //Returns 0 if closed ok and -1 if not
     return CloseFile((HANDLE)fd);
}

int _commit(int fd){
    //Returns 0 if flushed ok and -1 if not
    return FlushFile((HANDLE)fd);
} 
int _creat(const char *filename, int pmode){
    //Returns a fd if ok or -1 if error. Read errno for details
    return CreateFile((LPCSTR)filename, (FILE_ATTRIBUTES)(pmode & umask));
}

int _dup(int fd){
    //Returns a new fd or -1 if fail
    LPHANDLE newHandle = NULL;
    int retVal = (int)DuplicateHandle((HANDLE)fd, newHandle);
    if (!retVal){
        retVal = -1;
    }
    else{
        retVal = *newHandle;    //Get the value from the var
    }
    return retVal;
}
int _dup2(int fd1, int fd2){
    //Returns 0 if success or -1 if fail
    int retVal = (int)ForceDuplicateHandle((HANDLE)fd1, (HANDLE)fd2);
    if (!retVal){
        retVal = -1;
    }
    else{
        retVal = 0;
    }
    return retVal;
}    

int _eof(int fd){
    //Returns 0 if EOF and 1 if not
    //DWORD SetFilePointer(HANDLE hFile, LONG lDistanceToMove, DWORD dwMoveMethod)
    int retVal = 0;
    int curPos = SetFilePointer((HANDLE)fd, 0, FILE_CURRENT);  //Move it distance 0 from where we are
    int endOfFile = SetFilePointer((HANDLE)fd, 0, FILE_END);    //Move it distance 0 from the end
    SetFilePointer((HANDLE)fd, curPos, FILE_BEGIN);  //Return back to original position
    if (curPos != endOfFile){
        retVal = 1;
    }
    return retVal;
}

long _lseek(int fd, long offset, int origin){
    //-1L if unable to seek to address
    long retVal = -1L;
    SetFilePointer((HANDLE)fd, (LONG)origin, FILE_BEGIN);    //Move it to the origin of the move
    return (long)SetFilePointer((HANDLE)fd, offset, FILE_CURRENT);
}

int _open(const char *filename, int oflag){
    //-1 if error, fd otherwise.
    //HANDLE DOSAPI OpenFile(LPCSTR lpFileName, FILE_OPEN_MODE dwOpenMode, FILE_SHARE_MODE dwShareMode)
    return OpenFile((LPCSTR)filename, (FILE_OPEN_MODE)oflag, SHARE_COMPAT);
}
int _read(int const fd, const void *buffer, unsigned const count){
    //Returns number of bytes read or -1 on error
    //BOOL DOSAPI ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,  LPDWORD lpNumberOfBytesRead)
    int retVal = 0;
    LPDWORD bytesRead = NULL;
    retVal = (int)ReadFile((HANDLE)fd, (LPVOID)buffer, (DWORD)count, bytesRead);
    if (!retVal){
        retVal = *bytesRead;    //Get the stored value
    }
    else{
        retVal = -1;
    }
    return retVal;
}

long _tell(int fd){
    //Returns the current position in the file or -1 on error.
    return SetFilePointer((HANDLE)fd, 0, FILE_CURRENT);
}

int _umask(int pmode){
    //Returns the previous pmode
    int oldmask = umask;
    umask = pmode & (_S_IWRITE | _S_IREAD);
    return oldmask;
}

int _write(int fd, const void *buffer, unsigned int count){
    //Returns number of bytes written or -1 on error
    //BOOL DOSAPI ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,  LPDWORD lpNumberOfBytesRead)
    int retVal = 0;
    LPDWORD bytesWritten = NULL;
    retVal = (int)WriteFile((HANDLE)fd, (LPVOID)buffer, (DWORD)count, bytesWritten);
    if (!retVal){
        retVal = *bytesWritten;    //Get the stored value
    }
    else{
        retVal = -1;
    }
    return retVal;
}