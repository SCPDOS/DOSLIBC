#include "./../../DOSCRT/headers/scpdos.h"
#include "./../../BREAK/headers/bochs.h"

void main() {
	bochsBreak();
	LPCSTR testString = "Hello World!\n\r";
	WriteString(testString);
	ExitProcess(0);
}