%use masm
BITS 64

;WARNING WARNING WARNING WARNING WARNING WARNING 
; cmdline MUST be CR terminated!!!
;WARNING WARNING WARNING WARNING WARNING WARNING 

extern main
extern _BSS_START_
extern _BSS_END_
extern _argv    ;Argument Vector
extern _argc    ;Argument Count
extern _env     ;Environment

global __start__
global __main

; Equates used locally in this CRT0
TAB equ 0x09
LF equ 0x0A
CR equ 0x0D
SPC equ 0x20

    section .text
__start__:
;BREAKPOINT BREAKPOINT BREAKPOINT BREAKPOINT
    ;xchg bx, bx
;BREAKPOINT BREAKPOINT BREAKPOINT BREAKPOINT
    cld ;Ensure the direction is good (DOS does this anyway)
;Realign the stack 
    mov rax, rsp
    shr rax, 4  ;Divide by 16
    shl rax, 4  
    mov rsp, rax
;Leave rsp alone now
    mov rdi, _BSS_START_
    mov rcx, _BSS_END_
    sub rcx, rdi
    xor eax, eax
    rep stosb
;We're gonna be proper and ask DOS to give us the ptr to ENV and CMDLINE
;The cmdline is guaranteed to be at ptr + 37 (+36 gives number of chars)
; We ignore the char count (not a great idea but we do this for most apps)
    mov eax, 0x6100 ;New System Service, get environment ptr
    int 0x21
    mov qword [_env], rdx
    mov eax, 0x6101 ;New System Service, get cmdline ptr pls in rdx
    int 0x21
    lea rsi, qword ptr [rdx + 37]   ;Get the ptr to the char array
;Here we gotta ensure the first byte is a value less than 128 and then
; check if @ byte [rsi + val] = CR. If not, fail
    movzx eax, byte [rsi - 1]   ;Get cmdline "len"
    cmp eax, 0x80    
    jnb exitBadCmdLine
    cmp byte [rsi + rax], CR    ;If not a CR here, then bad cmdline
    jne exitBadCmdLine
    mov eax, 0x4800 ;Allocate a block
    mov ebx, 0x8    ;8 paragraphs (128 bytes) in length
    int 21h
    jc exitBadAlloc
    mov rdi, rax    ;Start storing cmdline args in here
    mov rbp, rax    ;Save the string array ptr in rbp
    mov ecx, 1      ;Number of strings cnt (1 for filename)
makeCstrings:
    call skipDelims ;Skip delimiters
    cmp al, CR
    je endStrBuild  ;Terminate the string build
.lp:
    lodsb
    stosb
    call isALDelimOrCR
    jne .lp 
    inc ecx     ;We just finished a string
    mov byte [rdi - 1], 0   ;Store a null over the last char we just copied
    cmp al, CR  ;If we just ended on a terminator finish, else...
    jne makeCstrings    ;...go to next argument or terminator
endStrBuild:
    mov qword [_argc], rcx  ;Store the arg count in rcx
    mov ebx, ecx 
    inc ebx     ;Make space for terminating nullptr too
    shl ebx, 3  ;Multiply by 8 bytes to get number of bytes to allocate
    add ebx, 0x0F   ;Round up
    shr ebx, 4  ;Turn into number of paragraphs to allocate (could optimise?)
    mov eax, 0x4800
    int 21h
    jc exitBadAlloc
    mov qword [_argv], rax
    mov rsi, rax    ;Have rsi point to the array where we will store ptrs
    mov eax, 6102h  ;Get the filename ptr in rdx
    int 21h
    jnc filenameOk
    test rdx, rdx
    jnc filenameOk
    lea rdx, noNameStr
filenameOk:
    mov qword [rsi], rdx    ;Store the ptr here
    add rsi, 8      ;Go to next entry in the array
    mov edx, ecx    ;Get the number of args passed into edx 
    dec edx         ;Decrement the number of entries left to process 
    jz argvDone
    mov rdi, rbp    ;Get back the ptr to the cmd array
    xor eax, eax    ;Make nullptr but also for compare to al
    mov ecx, -1     ;Use for repne scasb
argvProcess:
    mov qword [rsi], rdi
    add rsi, 8      ;Goto next entry in the array
    dec edx
    jz argvDone
    repne scasb     ;Find the next null, rdi points to next string
    jmp short argvProcess
argvDone:
    mov qword [rsi], rax    ;Store the final null ptr we made space for
prepEnter:
    mov rcx, qword [_argc]  ;Get count for the calling convention
    mov rdx, qword [_argv]  ;Get vec ptr for the calling convention
    mov r8, qword [_env]    ;Get the optional, UNPARSED environment ptr
;Call the main function :)
    call main
;Let DOS do any allocation cleanup now
    mov eax, 0x4C00  
    int 0x21 ;Return to DOS
;If there is an allocation error, exit
exitBadAlloc:
    lea rdx, badMemStr
    mov eax, 0x0900
    int 0x21
    mov eax, 0x4CFF     ;Not enough memory error
    int 0x21
exitBadCmdLine:
    lea rdx, badCmdLin
    mov eax, 0x0900
    int 0x21
    mov eax, 0x4CFE     ;Bad command line passed (geq 128 chars or no CR fnd)
    int 0x21 
badMemStr db "CRT: Not enough memory",CR,LF,"$"
badCmdLin db "CRT: Bad command line passed",CR,LF,"$"
noNameStr db "DOS_PROG.UNK",0   ;Default string, can be anything
;GCC provides a call to this main constructor. Since we 
; setup everything in assembly in CRT0, we don't need this.
__main:
    ret

;This is to parse command tails as passed by COMMAND.COM
skipDelims:
;Points rsi to the first non-delimiter char in a string, loads al with value
    lodsb
    call isALDelim
    jz skipDelims
;Else, point rsi back to that char :)
    dec rsi
    ret

findDelimOrCR:
;Point rsi to the first delim or cmdtail terminator, loads al with value
    lodsb
    call isALDelimOrCR
    jnz findDelimOrCR
    dec rsi ;Point back to the delim or CR char
    ret

isALDelimOrCR:
    cmp al, CR
    je isALDelim.exit
isALDelim:
    cmp al, SPC
    je .exit
    cmp al, TAB
    je .exit
    cmp al, "="
    je .exit
    cmp al, ","
    je .exit
    cmp al, ";"
.exit:
    ret