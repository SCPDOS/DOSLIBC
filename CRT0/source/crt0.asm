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
    int 0x41
    mov qword [_env], rdx
    mov eax, 0x6101 ;New System Service, get cmdline ptr pls in rdx
    int 0x41
    mov eax, 0x7F   ;Max number of chars in buffer (127)
    movzx ecx, byte ptr [rdx + 36]  ;Get the number of chars in here
    cmp ecx, eax    ;Is the number of chars bigger than 127?
    cmova ecx, eax  ;If so, replace it with 127
    lea rdi, qword ptr [rdx + 37]   ;Get the ptr to the char array
    mov rsi, rdi    ;Save the ptr to the string array in rsi
    xor edx, edx    ;Clear the argc counter
    mov al, " "     ;Search for space
makeCstrings:
    repne scasb     ;Search for first space past name
    jecxz endOfCmdLine ;No more chars, exit and terminate current string
    mov byte [rdi - 1], 0   ;Null terminate this string
    inc edx ;One more string processed
    repe scasb  ;Skip all the spaces
    test ecx, ecx
    jnz makeCstrings
    cmp byte [rdi - 1], " "
    jne endOfCmdLine    ;If the last char was not a space, skip the dec
    dec edx ;Dec the count to balance the below (as we searched thru spaces)
endOfCmdLine:
    inc edx ;Add one more char which we are about to terminate
    mov byte [rdi], 0   ;Store a final null over terminating 0Dh
    mov qword [_argc], rdx  ;Save the number of arguments we have
    mov eax, 0x4800
    lea rbx, qword [8*rdx + 0x11] ;Get the number of bytes to allocate
    shr rbx, 4  ;Divide by 16 to get number of paragraphs
    int 41h
    jc exitBad
    mov rbp, rax    ;Store the ptr to the array here
;argv array must have a qword at _argv[_argc] = 0
    mov qword [_argv], rbp  ;Save the ptr to the char* array

    mov rdi, rsi    ;Get the start of the command line string into rdi
    xor edx, edx    ;Zero the offset register
    xor ecx, ecx
    dec ecx         ;Get -1 in ecx
    xor eax, eax    ;Scan for nulls
    mov ah, " "     ;Prepare for space scanning
buildArgv:
    mov qword [rbp + 8*rdx], rdi  ;Save rdi as the ptr to the string
    repne scasb   ;Scan for the terminating null
    xchg al, ah 
    repe scasb    ;Scan through the spaces to char 1 of the string
    dec rdi     ;Go back to the first char since scasb goes to next char
    xchg al, ah
    inc edx
    cmp rdx, qword [_argc]  ;Are we equal yet?
    jne buildArgv
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
    int 0x41
exitCommon:
    mov ecx, 0xFF
    cmp eax, ecx
    cmova eax, ecx 
    or eax, 0x4C00  ;Add the exit code into AH w/o stall
    int 0x41 ;Return to DOS
;If there is an allocation error, exit
exitBad:
    lea rdx, badMemStr
    mov eax, 0x0900
    int 0x41
    mov eax, 0xFF
    jmp short exitCommon
badMemStr db "CRT: Not enough memory",0Ah,0Dh,"$"
;GCC provides a call to this main constructor. Since we 
; setup everything in assembly in CRT0, we don't need this.
__main:
    ret