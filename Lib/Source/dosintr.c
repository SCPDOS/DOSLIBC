#include "../../Headers/scpdos.h"


VOID WINAPI GetCountryInformation(LPCOUNTRY_BLOCK lpCountryBlock){
    ASM(
        "mov eax, 0x3800\n\t"
        "mov rdx, rcx\n\t"
        "int 0x41"
    );
}