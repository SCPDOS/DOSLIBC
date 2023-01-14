
#include "../../Headers/scpdos.h"

//If this returns True, you can get the task return code
BOOL WINAPI ExecProcess(LPCSTR lpProcessName, LPEPB lpExecuteParameterBlock){
    __asm__ __volatile(
        "push rbx\n\t"
        "mov rbx, rdx\n\t"
        "mov rdx, rcx\n\t"
        "mov eax, 0x4B00\n\t"
        "xor ecx, ecx\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx\n\t"
        "pop rbx\n\t"
    );
};

//Loads a program for execution but doesnt actually execute it
BOOL WINAPI LoadProcess(LPCSTR lpProcessName, LPLPB lpLoadParameterBlock){
    __asm__ __volatile(
        "push rbx\n\t"
        "mov rbx, rdx\n\t"
        "mov rdx, rcx\n\t"
        "mov eax, 0x4B01\n\t"
        "xor ecx, ecx\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx\n\t"
        "pop rbx\n\t"
    );
};

//Called by a task to load a program overlay in the tasks memory space
BOOL WINAPI LoadOverlay(LPCSTR lpOverlayName, LPLOB lpLoadOverlayBlock){
    __asm__ __volatile(
        "push rbx\n\t"
        "mov rbx, rdx\n\t"
        "mov rdx, rcx\n\t"
        "mov eax, 0x4B03\n\t"
        "xor ecx, ecx\n\t"
        "int 0x41\n\t"
        "mov eax, 1\n\t"
        "cmovc eax, ecx\n\t"
        "pop rbx\n\t"
    );
};

VOID WINAPI ExitProcess(BYTE bExitCode){
    ASM (
        "mov eax, 0x4C00\n\t"
        "mov al, cl\n\t"
        "int 0x41"
    );
}

VOID WINAPI ExitProcessAndStayResidentP(BYTE bExitCode, DWORD dwParagraphsToReserve){
    ASM(
        "mov eax, 0x3100\n\t"
        "mov al, cl\n\t"
        "int 0x41\n\t"
    );
}

VOID WINAPI ExitProcessAndStayResidentB(DWORD dwBytesToReserve){
    ASM(
        "mov edx, ecx\n\t"
        "int 0x47"
    );
}


//Gets the return value of the process that last terminated
RETURN_CODE WINAPI GetExitCodeProcess(){
    ASM (
        "mov eax, 0x4D00\n\t"
        "int 0x41\n\t"
    );   
}