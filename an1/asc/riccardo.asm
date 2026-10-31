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
    sir dd 12AB5678h, 1256ABCDh, 12344344h 
    len equ ($ - sir) / 4
    temp dw 0
    
; our code starts here
segment code use32 class=code
    start:
        ; ...1234 5678h, 1256 ABCDh, 12AB 4344h.
        ;Se da un sir de dublucuvinte. Sa se ordoneze crescator sirul cuvintelor superioare ale acestor dublucuvinte. Cuvintele inferioare raman neschimbate.
        
        mov esi, sir
        cld
        mov ecx, len
        
        fori:
        
            lodsd ; in eax avem tot dd

            mov edx, ecx
            mov ecx, len
            mov edi, 0 ; j meu
            jecxz final
                
            
            
            forj:
                mov ebx, 0
                mov bx, [ax + 2]
                
                mov eax, 0
                mov ax, bx ; am in ax partea superioara
                
                
                mov ebx, 0
                mov bx, [sir + edi - 2]
                
                ; comparam
                cmp bx, ax
                jl e_bine
                
                ; swap
                
                mov word [temp], ax
                mov bx, ax
                mov ax, temp
                
                e_bine:
                
                
                
                add edi, 4
            loop forj
            
            mov ecx, edx        
        loop fori
        
        final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
