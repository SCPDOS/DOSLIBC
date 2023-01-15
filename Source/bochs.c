#include "../Headers/bochs.h"

void bochsBreak(){
#if INLINE_ASM
    __asm__ __volatile__(
    "xchg bx, bx"
    );
#endif
}