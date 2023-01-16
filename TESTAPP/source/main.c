#include <scpdos.h>
#include "./../../BREAK/headers/bochs.h"

int main(int argc, char* argv[]) {
	LPCSTR testString = "Hello World!\n\r";
	WriteString(testString);
	return 0;
}