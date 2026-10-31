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
    
    sir dw 5678h, 1234h, 4344h 
    len equ ($ - sir) / 2
    b1 times (len / 2) db
    b2 times (len / 2) db

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
        ; 10
        ;Se da un sir A de cuvinte. Construiti doua siruri de octeti  
        ;- B1: contine ca elemente partea superioara a cuvintelor din A
        ;- B2: contine ca elemente partea inferioara a cuvintelor din A
    
        mov esi, sir
        cld
        mov ecx, len
        mov edi, 0
        
        fori:
        
            lodsb ; in al am partea inferioara
            
            mov bl, al
            
            lodsb ; in al am superioara
            
            mov byte [b1 + edi], al
            mov byte [b2 + (edi + len)], bl
            
            inc edi
        
        loop fori;
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
