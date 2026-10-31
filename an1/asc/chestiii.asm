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
    a db 2, 1, 3, 3, 4, 2, 6
    len_a equ $ - a
    b db 4, 5, 7, 6, 2, 1
    len_b equ $ - b
    r times len_a + len_b db 0
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov ecx, len_b
        mov esi, len_b - 1
        mov edi, 0
        jecxz stop
        
        repeta:
            mov al, [b + esi]
            mov [r + edi], al
            dec esi
            inc edi
        loop repeta
       
        mov ecx, len_a
        mov esi, 0
        mov edi, len_b
        jecxz stop
        
        repeta2:
            mov al, [a + esi]
            
            test al, 1
            jne impar
            mov [r + edi], al
            inc edi
            
            impar:
            inc esi

        loop repeta2
        
        stop:
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
