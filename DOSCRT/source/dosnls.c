#include "../headers/scpdos.h"

#if !INLINE_ASM
#include "../headers/asm/asmnls.h"
#endif

VOID DOSAPI GetCountryInformation(LPCOUNTRY_BLOCK lpCountryBlock){
#if INLINE_ASM
    ASM
        "mov eax, 0x3800\n\t"
        "mov rdx, rcx\n\t"
        "int 0x41"
    END_ASM
#else
    //GetCountryInformation(lpCountryBlock);
#endif
}