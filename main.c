#include "scpdos.h"
#include "./Headers/bochs.h"

void main() {
	bochsBreak();
	LPCSTR testString = "Hello World!\n\r";
	WriteString(testString);
	ExitProcess(0);
}