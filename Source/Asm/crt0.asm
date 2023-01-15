%use masm
BITS 64
;ASSEMBLE WITH nasm ./Source/Asm/crt0.asm -o ./out/lib/crt0.lib -f win64
;Need to modify slightly to 
extern main
extern _BSS_START_
extern _BSS_END_
extern _argv    ;Argument Vector
extern _argc    ;Argument Count

global start 
    section .text
;TODO:
;1) Paragraph align the stack (downwards ofc)
;2) Clean the BSS
;3) Get a pointer to the command line. Count the number of times 
;   a space/tab region appears, to pass as argc in rcx and the 
;   pointer to start of the command line in rdx.
;   Make sure to null terminate each string 
;       (replace first char in space region with 00).
;
;4) Call main.
;5) If eax > 0FFh, set al = 0FFh and 41h/AH=4Ch exit
;Future expansion:
;Hook Int 00h to prevent termination in the event of such a bug.
; We first print an error message, then pop the RIP value from 
; the stack, decode the instruction and go to the next 
; instruction after it!
start:
;Step 1)
    mov rax, rsp
    shr rax, 5  ;Divide by 16
    shl rax, 5  
    mov rsp, rax
;Step 2)
    mov rdi, _BSS_START_
    mov rax, rdi
    mov rcx, _BSS_END_
    sub rcx, rax
    xor eax, eax
    rep stosb
;Step 3)
    ;We're gonna be proper and ask DOS to give us the PTR to the CMDLINE data
    ;The cmdline is guaranteed to be at ptr + 37 (+36 gives number of chars)
    mov eax, 0x6101 ;New System Service, get cmdline ptr pls in rdx
    int 0x41
    movzx ecx, byte ptr [rdx + 36]  ;Get the number of chars in here
    lea rdi, qword ptr [rdx + 37]   ;Get the ptr to the char array
    push rdi    ;Push the pointer to the start of the char array
    xor edx, edx    ;Clear the argc counter
    mov al, " " ;Replace all spaces with 0's
scanLp:
    repne scasb
    dec rdi ;Return rdi pointing to the space char
    cmp byte [rdi], 0x0D    ;String terminating char?
    mov byte [rdi], 0   ;Always store a terminating null
    je short step4
    jecxz step4
    inc edx ;Argument found
    jmp short scanLp 
step4:
;Step 4) 
    inc edx ;Add one more (if none, for cmdname)
    mov ecx, edx
    pop rdx ;Pop the pointer back
    mov qword [_argc], rcx
    mov qword [_argv], rdx
    call main
;Step 5)
    mov ecx, 0xFF
    cmp eax, ecx
    cmova eax, ecx 
    or eax, 0x4C00  ;Add the exit code into AH w/o stall
    int 0x41 ;Return to DOS