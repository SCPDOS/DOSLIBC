#ifndef _DOSMAC_H
#define _DOSMAC_H

#ifdef PUBLIC 
#undef PUBLIC
#endif

#ifdef PRIVATE
#undef PRIVATE
#endif

#ifdef COMPILER
#undef COMPILER
#endif

#ifdef CC_MSVC
#undef CC_MSVC
#endif

#ifdef CC_GCC
#undef CC_GCC
#endif

#define EXTERN	extern	

#define CC_MSVC 1
#define CC_GCC 2

#if defined(_MSC_VER)
#define DOSAPI __fastcall
#define COMPILER CC_MSVC
#define NAKED
#elif defined(__GNUC__)
#define DOSAPI __attribute__((ms_abi))
#define COMPILER CC_GCC
#define NAKED __attribute__((naked))
#endif

#if COMPILER==CC_GCC 
#define ASM __asm__ __volatile__ (
#define END_ASM );
#define INLINE_ASM 1

#elif COMPILER==CC_MSVC
#define INLINE_ASM 0
#endif

#endif