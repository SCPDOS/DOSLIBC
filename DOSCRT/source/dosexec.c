#include "../headers/scpdos.h"

#if !INLINE_ASM
#include "../headers/asm/asmexec.h"
#endif

//If this returns True, you can get the task return code
BOOL DOSAPI ExecProcess(LPCSTR lpProcessName, LPEPB lpExecuteParameterBlock){
#if INLINE_ASM
    ASM
        "push rbx\n\t"
        "mov rbx, rdx\n\t"
        "mov rdx, rcx\n\t"
        "mov eax, 0x4B00\n\t"
        "xor ecx, ecx\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx\n\t"
        "pop rbx\n\t"
    END_ASM
#else
    //return ExecProcessA(lpProcessName, lpExecuteParameterBlock);
#endif
}

//Loads a program for execution but doesnt actually execute it
BOOL DOSAPI LoadProcess(LPCSTR lpProcessName, LPLPB lpLoadParameterBlock){
#if INLINE_ASM
    ASM
        "push rbx\n\t"
        "mov rbx, rdx\n\t"
        "mov rdx, rcx\n\t"
        "mov eax, 0x4B01\n\t"
        "xor ecx, ecx\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx\n\t"
        "pop rbx\n\t"
    END_ASM
#else
    //return LoadProcessA(lpProcessName, lpLoadParameterBlock);
#endif
}

//Called by a task to load a program overlay in the tasks memory space
BOOL DOSAPI LoadOverlay(LPCSTR lpOverlayName, LPLOB lpLoadOverlayBlock){
#if INLINE_ASM
    ASM
        "push rbx\n\t"
        "mov rbx, rdx\n\t"
        "mov rdx, rcx\n\t"
        "mov eax, 0x4B03\n\t"
        "xor ecx, ecx\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx\n\t"
        "pop rbx\n\t"
    END_ASM
#else
    //return LoadOverlayA(lpOverlayName, lpLoadOverlayBlock);
#endif
}

VOID DOSAPI ExitProcess(BYTE bExitCode){
#if INLINE_ASM
    ASM
        "mov eax, 0x4C00\n\t"
        "mov al, cl\n\t"
        "int 0x41"
    END_ASM
#else
    //ExitProcessA(bExitCode);
#endif
}

VOID DOSAPI ExitProcessAndStayResidentP(BYTE bExitCode, DWORD dwParagraphsToReserve){
#if INLINE_ASM
    ASM
        "mov eax, 0x3100\n\t"
        "mov al, cl\n\t"
        "int 0x41\n\t"
    END_ASM
#else
    //ExitProcessAndStayResidentPA(bExitCode, dwParagraphsToReserve);
#endif
}

VOID DOSAPI ExitProcessAndStayResidentB(DWORD dwBytesToReserve){
#if INLINE_ASM
    ASM
        "mov edx, ecx\n\t"
        "int 0x47"
    END_ASM
#else
    //ExitProcessAndStayResidentBA(dwBytesToReserve);
#endif
}


//Gets the return value of the process that last terminated
RETURN_CODE DOSAPI GetExitCodeProcess(){
#if INLINE_ASM
    ASM
        "mov eax, 0x4D00\n\t"
        "int 0x41\n\t"
    END_ASM   
#else
    //return GetExitCodeProcessA();
#endif
}