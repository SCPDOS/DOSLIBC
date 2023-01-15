#include "scpdos.h"

void __main(int argc, char* argv[]) {
	LPCSTR testString = "Hello World!\n\r";
	WriteString(testString);
	ExitProcess(0);
}