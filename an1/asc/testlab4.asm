bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a dw 0110001110110101b
    b dw 1010000100110110b
    c dd 0
    d dq 0
    temp dw 0
    doi dw 2

; our code starts here
; d = ((a / b) + c) / 2 - (c * a)
; d = (2 + 4) / 2 - (4 * 2) = 3 - 8 = -5
segment code use32 class=code
    start:
        ; ...
    mov eax, 0
    mov ebx, 0
    
    mov bx, [a] ; 0110001110110101b
    not bx ;      1001110001001010b ordinea conteaza
    and bx, 111111100b ; 0000000 0010010 00b    
    shr bx, 2 ; 00000000010010b
    OR eax, ebx ; eax = 00000000010010b
    
    mov ebx, 0
    mov bx, [a] ; 0110001110110101b
    and bx, 111b ;0000000000000101b
    shl bx, 7   ; 1010000000b
    or eax, ebx ; oru
    
    mov bx, [b] ; 10 100001 00110110b
    SHR bx, 8   ; 10 100001b
    and bx, 111111b
    SHL bx, 10 
    or eax, ebx ; ebx
    
    mov bx, -1 ; eax = 00 00 FF FF h
    SHL ebx, 16 ; eax = FF FF 00 00 h
    OR eax, ebx
    mov [c], eax
    
    
    
    mov ax, [a]
    cwd ; 
    idiv word [b] ; ax:dx wordu
    
    cwd 
    adc ax, [c] ; ax + 
    adc dx, [c+4]
    
    ; pana aici corect
    div word [doi] ; nu putem cu constante
    
    mov [temp], ax
    mov ax, [a]
    cwd ; schimbar ordinea
    mov ebx, [c]        
    imul ebx ; edx:eax

    mov ebx, eax ; inferior
    mov ecx, edx ; superior
    mov eax, 0
    
    mov ax, [temp]
    cdq ; eax = 00 [temp]
    
    sub eax, ebx ; respectiv
    sbb edx, ecx
    
    mov [d], eax ; inferior 
    mov [d+4], edx ; superior
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
