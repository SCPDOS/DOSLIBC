


GetCharA PROC PUBLIC
    mov eax, 0100h
    int 21h
    movzx eax, al
    ret
GetCharA ENDP

PutCharA PROC PUBLIC
    movzx edx, cl
    mov eax, 0200
    int 21h
    ret
PutCharA ENDP

AuxInputA PROC PUBLIC
    mov eax, 0300h
    int 21h
    movzx eax, al
    ret
AuxInputA ENDP

AuxOutputA PROC PUBLIC
    movzx edx, cl
    mov eax, 0400h
    int 21h
    ret
AuxOutputA ENDP

PrnOutputA PROC PUBLIC
    movzx edx, cl
    mov eax, 0500h
    int 21h
    ret
PrnOutputA ENDP

DirectConInAsyncA PROC PUBLIC
    mov r8, rcx
    mov eax, 0600h
    mov edx, 0FFh
    xor ecx, ecx
    int 21h
    jnz short dciExit
    inc ecx
    mov byte ptr [r8], al
dciExit:
    mov eax, ecx
    ret
DirectConInAsyncA ENDP

DirectConOutAsyncA PROC PUBLIC
    cmp cl, 0FFh
    je dcoExit
    movzx edx, cl
    mov eax, 0600h
    int 21h
dcoExit:
    ret
DirectConOutAsyncA ENDP

DirectConInA PROC PUBLIC
    mov eax, 0700h
    int 21h
    movzx eax, al
    ret
DirectConInA ENDP

ConInputA PROC PUBLIC
    mov eax, 0800h
    int 21h
    movzx eax, al
    ret
ConInputA ENDP

__WriteStringA PROC PUBLIC
    push rbx
    xor ebx, ebx 
    inc ebx
    xchg rdx, rcx 
    mov eax, 4000h
    int 21h
    pop rbx
    ret
__WriteStringA ENDP

__GetBufferedInputA PROC PUBLIC
    mov rdx, rcx
    mov eax, 0A00h
    int 21h
    ret
__GetBufferedInputA ENDP

GetConInputStatusA PROC PUBLIC
    mov eax, 0B00h
    int 21h
    and al, 1
    ret
GetConInputStatusA ENDP

ClearInputBufferA PROC PUBLIC
    mov eax, 0C00h
    int 21h
    ret
ClearInputBufferA ENDP