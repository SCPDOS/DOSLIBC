#include <scpdos.h>
#include "../../IO/headers/io.h"
//#include "../../BREAK/headers/bochs.h"

#define DTALEN 128 /*Data Transfer Area Length => Length of the data transfer buffer. Defining a macro to define this "constant"*/

int openFile(char*);
int closeFile(int);
int readFile(int, char*, int);
int writeFile(int, char*, int);
int scanChar(char*, char*);
int strlen(char*);
void printErrorMsg(void);
void writeCon(char*);
void writeDwordAtCursor(int);
void writeByteAtCursor(unsigned char);

/*Global Vars*/
char switchFlags = 0;	/*Not used for now, will set ASCII or Binary comparisons, whitespace treatment etc etc*/
char buffer1[DTALEN];  /*Statically allocate two 128 byte buffers to read chars into*/
char buffer2[DTALEN];

/* Messages */
char* paramString = "\r\n usage: fc [drive:]pathname1 [drive:]pathname2 \r\n";

int main(int argc, char** argv)
{
	argc -= 1; /*Get rid of initial argument (filename) from count*/
	int retVal = 0;
	/*Create two pointers for the filenames*/
	char* pathspec1;
	char* pathspec2;
	if (argc != 2)
	{
		writeCon(paramString);
		retVal = -1;    /*Error exit*/
	}
	else
	{
		pathspec1 = argv[1];
		pathspec2 = argv[2];

		int fHdl1 = -1;
		int fHdl2 = -1; 

		fHdl1 = openFile(pathspec1);
		if (fHdl1 == -1)
		{
			printErrorMsg();
			retVal = -1;
		}
		else /*Only attempt to open the second file if the first file opened successfully*/
		{
			fHdl2 = openFile(pathspec2);
			if (fHdl2 == -1)
			{
				printErrorMsg();
				retVal = -1;
			}
		}

		/*Given things are so far so good, now we wanna read from the files*/
		if (!retVal) 
		{
			char status = -1;
			int cntr = 0;
			int matches = 0;
			while (status)
			{
				int readChars1 = -1;
				int readChars2 = -1;

				readChars1 = readFile(fHdl1, buffer1, DTALEN);
				if (readChars1 == -1)
				{
					retVal = -1;
					status = 0;	/*Turn off the while loop*/
					printErrorMsg();
				}
				else 
				{
					readChars2 = readFile(fHdl2, buffer2, DTALEN);
					if (readChars2 == -1)
					{
						retVal = -1;
						status = 0;	/*Turn off the while loop*/
						printErrorMsg();
					}
				}

				int maxCharsRead = readChars1 <= readChars2 ? readChars1 : readChars2;

				if (!maxCharsRead)
				{
					writeCon("\r\n End of files reached \r\n");
					status = 0; /*Exit loop*/
				}
				if (status)
				{
					/*Now we compare the data in the two buffers*/
					int i;
					for (i = 0; i < DTALEN; i++) 
					{
						cntr++;	/* Increment the counter */
						if (buffer1[i] != buffer2[i])
						{
							matches++;
							/*Get the two different chars*/
							unsigned char x = buffer1[i];
							unsigned char y = buffer2[i];
							writeDwordAtCursor(cntr);
							writeCon(": ");
							writeByteAtCursor(x);
							writeCon(" ");
							writeByteAtCursor(y);
							writeCon(" \r\n");
						}
					}
				}
				if (readChars1 < readChars2) 
				{
					writeCon("\r\n");
					writeCon(pathspec2);
					writeCon(" longer than ");
					writeCon(pathspec1);
					writeCon("\r\n");
					status = 0;
				}

				if (readChars1 > readChars2)
				{
					writeCon("\r\n");
					writeCon(pathspec1);
					writeCon(" longer than ");
					writeCon(pathspec2);
					writeCon("\r\n");
					status = 0;
				}
			}
			if (!matches)
			{
				writeCon("\r\n no differences encountered \r\n");
			}
		}
		
		/*Clean up handles, essentially a ~main*/
		if (fHdl1 != -1) 
		{
			closeFile(fHdl1);
		}
		if (fHdl2 != -1)
		{
			closeFile(fHdl2);
		}
	}
	return retVal;
}

void printErrorMsg()
{
	int errorCode = _get_io_error();

	switch (errorCode)
	{
	case ERROR_ACCESS_DENIED:
		writeCon("\r\n Access Denied \r\n");
		break;
	case ERROR_SHARING_VIOLATION:
		writeCon("\r\n SHARE error \r\n");
		break;
	case ERROR_INVALID_ACCESS:
		writeCon("\r\n Invalid Access Parameters \r\n");
		break;
	case ERROR_NO_MORE_FILES:
		writeCon("\r\n No more files \r\n");
		break;
	case ERROR_FILE_NOT_FOUND:
		writeCon("\r\n File Not Found \r\n");
		break;
	default:
		writeCon("\r\n Error Accessing File \r\n");
		break;
	}
}

int openFile(char* pathspec)
{
	/*Always open with read permissions*/
	return _open(pathspec, OPEN_READ);	/*Open with read permissions in binary mode, we'll talk through ASCII mode eventually*/
}

int closeFile(int fHandle)
{
	return _close(fHandle);
}

int readFile(int fHandle, char* buffer, int readLen)
{
	return _read(fHandle, buffer, readLen);
}

int writeFile(int fHandle, char* buffer, int writeLen)
{
	return _write(fHandle, buffer, writeLen);
}

void writeCon(char* buffer)
{
	int len = strlen(buffer);
	writeFile(1, buffer, len);	/*Write out to STDOUT (these writes are in ASCII mode and mirror DOS :) )*/
}

int scanChar(char* si, char* c) {
	/*
	* If return value 0 => Char found
	* If return value 1 => Char not found.
	* If char found, pointer points to that char
	*/
	int retVal = -1;
	while (*si != '/0') {
		if (*si == *c)
		{
			retVal = 0;
			break;
		}
		else
			si++;
	}
	return retVal;
}

int strlen(char* si) {
	int len = 0;
	while (*si != '\0') {
		si++;
		len++;
	}
	return len;
}

void writeByteAtCursor(unsigned char c)
{
	/*Takes in a ascii character and outputs its ascii digit representation.
	I.E, takes in the number 0xA and out puts the string "10"*/

	/*Works on the fact that a char is a number between 0 - 255*/
	unsigned char numstr[3] = "00\0";	/*String to print*/

	if (c > 15)
	{
		while (c > 15) {
			c -= 16;
			if (numstr[0] == '9')
			{
				numstr[0] = 'A';
			}
			else 
			{
				numstr[0]++;
			}
		}
	}
	if (c > 9)
	{
		c -= 10;
		numstr[1] = c + 'A';
	}
	else
	{
		numstr[1] += c;
	}
	writeCon(numstr);
}

void writeDwordAtCursor(int i)
{
	unsigned char hiByte = (unsigned char)((i & 0xFF000000) >> 24);
	unsigned char midHi = (unsigned char)((i & 0x00FF0000) >> 16);
	unsigned char midLo = (unsigned char)((i & 0x0000FF00) >> 8);
	unsigned char loByte = (unsigned char)(i & 0x000000FF);
	writeByteAtCursor(hiByte);
	writeByteAtCursor(midHi);
	writeByteAtCursor(midLo);
	writeByteAtCursor(loByte);
}