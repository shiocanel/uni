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
    a db 1
    b dw 2
    c dd 2
    d dq 3
    
; our code starts here
segment code use32 class=code
    start:
        ; ...(d+d)-a-b-c
        
        mov eax, 0
        mov edx, 0
        
        mov eax, [d]
        mov edx, [d + 4]
        
        add eax, [d]
        adc edx, [d + 4]
        
        mov ebx, 0
        mov ecx, 0
        mov bl, [a]
        
        sub eax, ebx
        sbb edx, ecx
    
    
        mov ebx, 0
        mov ecx, 0
        mov bx, [b]
        
        sub eax, ebx
        sbb edx, ecx
        
        
        mov ebx, 0
        mov ecx, 0
        mov ebx, [c]
        
        sub eax, ebx
        sbb edx, ecx
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
