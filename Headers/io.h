#ifndef _IO_H
#define _IO_H
#include "../scpdos.h"

#define _S_IREAD  0x0100 // Read permission, owner
#define _S_IWRITE 0x0080 // Write permission, owner

int _close(int fd); //Returns 0 if closed ok and -1 if not
int _commit(int fd); //Returns 0 if flushed ok and -1 if not
int _creat(const char *filename, int pmode);    //Returns a fd if ok or -1 if error. Read errno for details
int _dup(int fd); //Returns a new fd or -1 if fail
int _dup2(int fd1, int fd2);    //Returns 0 if success or -1 if fail
int _eof(int fd);   //Returns 0 if EOF and 1 if not
long _lseek(int fd, long offset, int origin); //-1L if unable to seek to address
int _open(const char *filename, int oflag); //-1 if error, fd otherwise.
int _read(int const fd, const void *buffer, unsigned const count); //Returns number of bytes read or -1 on error
long _tell(int fd); //Returns the current position in the file or -1 on error.
int _umask(int pmode); //Returns the previous pmode
int _write(int fd, const void *buffer, unsigned int count);

#endif