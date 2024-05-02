%use masm
BITS 64
;Need to modify slightly to 
extern main
extern _BSS_START_
extern _BSS_END_
extern _argv    ;Argument Vector
extern _argc    ;Argument Count
extern _env     ;Environment

global __start__
global __main
    section .text
;TODO:
;0) Paragraph align the stack
;1) Clean the BSS
;2) Process command line to get argc, argv
;3) Call main.
;4) If eax > 0FFh, set al = 0FFh and 41h/AH=4Ch exit
;Future expansion:
;Hook Int 00h to prevent termination in the event of such a bug.
; We first print an error message, then pop the RIP value from 
; the stack, decode the instruction and go to the next 
; instruction after it!
__start__:
;BREAKPOINT BREAKPOINT BREAKPOINT BREAKPOINT
    ;xchg bx, bx
;BREAKPOINT BREAKPOINT BREAKPOINT BREAKPOINT
    cld ;Ensure the direction is good (DOS does this anyway)
;Step 0)
;Realign the stack 
    mov rax, rsp
    shr rax, 4  ;Divide by 16
    shl rax, 4  
    mov rsp, rax
;Leave rsp alone now
;Step 1)
    mov rdi, _BSS_START_
    mov rcx, _BSS_END_
    sub rcx, rdi
    xor eax, eax
    rep stosb
;Step 2)
    ;We're gonna be proper and ask DOS to give us the ptr to ENV and CMDLINE
    ;The cmdline is guaranteed to be at ptr + 37 (+36 gives number of chars)
    mov eax, 0x6100 ;New System Service, get environment ptr
    int 0x21
    mov qword [_env], rdx
    mov eax, 0x6101 ;New System Service, get cmdline ptr pls in rdx
    int 0x21
    lea rsi, qword ptr [rdx + 37]   ;Get the ptr to the char array
    mov rdi, rsi    ;Save the ptr to the string array in rdi
    mov edx, 1      ;Set the argc counter to 1 (we always have a filename)
makeCstrings:
    call skipDelimiters ;Skip leading delimiters
mcslp:
    lodsb   ;Get the char here
    cmp al, 0Dh         ;Did we get the terminating CR?
    je endOfCmdLine
    call isALdelimiter      ;Else, is this a delimiter?
    jne mcslp               ;If not, keep looking
    mov byte [rsi - 1], 0   ;Null terminate this string
    inc edx                 ;One more string processed
    jmp short makeCstrings  ;Now skip leading delimiters
endOfCmdLine:
    mov byte [rsi - 1], 0   ;Store a final null over terminating 0Dh
    inc edx ;Add one more entry to argv for the command line itself
    mov qword [_argc], rdx  ;Save the number of arguments we have
    mov eax, 0x4800
    lea rbx, qword [8*rdx + 0x11] ;Get the number of bytes to allocate
    shr rbx, 4  ;Divide by 16 to get number of paragraphs
    int 21h
    jc exitBad
    mov rbp, rax    ;Store the ptr to the array here
;argv array must have a qword at _argv[_argc] = 0
    mov qword [_argv], rbp  ;Save the ptr to the char* array
;Place pointer to filename in argv array
    mov eax, 6102h  ;Get pointer in rdx
    int 21h         ;Can fail with CF=CY or RDX=<NUL>
    jnc .nameOk
    test rdx, rdx   
    jnz .nameOk
    lea rdx, noNameStr  ;Get the default 8.3,<NUL> string
.nameOk:
    mov qword [rbp], rdx    ;Store the name pointer here
    cmp qword [_argc], 1    ;Do we just have a file name?
    je short endArgv
;Get pointers to the ASCIIZ command line arguments for argv
    mov rsi, rdi    ;Get the start of the command line string into rsi
    mov rdx, 1      ;Go to the first entry
    ;This cannot start by ending up on a null so we ok!
    xor ecx, ecx
    dec ecx     ;Ensure we can repne scasb 
buildArgv:
    call skipDelimiters             
    mov qword [rbp + 8*rdx], rsi    ;Save rsi as the ptr to the string
    inc edx
    cmp rdx, qword [_argc]          ;Are we equal yet?
    je endArgv
    xor eax, eax
    mov rdi, rsi
    repne scasb     ;Scan off the null
    mov rsi, rdi    ;rdi points past the null
    jmp short buildArgv ;Now skip the delimiters again!
endArgv:
    xor eax, eax
    mov qword [rbp + 8*rdx], rax    ;Store a ptr to NULL
    mov rcx, qword [_argc]  ;Get the regs in for the calling convention
    mov rdx, qword [_argv]  ;Get the regs in for the calling convention
    mov r8, qword [_env]    ;Get the optional, UNPARSED environment
    ;We pass a ptr to the environment but it is unparsed as ANSI doesn't 
    ; request this!
;Step 3) 
    call main
;Step 4)
    mov r8, qword [_argv]   ;Get the pointer to free this block
    mov eax, 0x4900 ;Explicitly try to free
    int 0x21
exitCommon:
    mov ecx, 0xFF
    cmp eax, ecx
    cmova eax, ecx 
    or eax, 0x4C00  ;Add the exit code into AH w/o stall
    int 0x21 ;Return to DOS
;If there is an allocation error, exit
exitBad:
    lea rdx, badMemStr
    mov eax, 0x0900
    int 0x21
    mov eax, 0xFF
    jmp short exitCommon
badMemStr db "CRT: Not enough memory",0Ah,0Dh,"$"
noNameStr db "DOS_PROG.UNK",0   ;Default string, can be anything tbh
;GCC provides a call to this main constructor. Since we 
; setup everything in assembly in CRT0, we don't need this.
__main:
    ret

;This is to parse command tails as passed by COMMAND.COM
skipDelimiters:
;Skips all "standard" command delimiters. This is not the same as FCB 
; command delimiters but a subset thereof. 
;These are the same across all codepages.
;Input: rsi must point to the start of the data string
;Output: rsi points to the first non-delimiter char
    push rax
.l1:
    lodsb
    call isALdelimiter
    jz .l1
.exit:
    pop rax
    dec rsi ;Point rsi back to the char which is not a command delimiter
    ret

isALdelimiter:
;Returns: ZF=NZ if al is not a command separator 
;         ZF=ZE if al is a command separator
    cmp al, " "
    je .exit
    cmp al, ";"
    je .exit
    cmp al, "="
    je .exit
    cmp al, ","
    je .exit
    cmp al, 09h ;TAB
.exit:
    ret