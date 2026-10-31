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
    a db 2, 1, 3, -3
    b db 4, 5, -5, 7
    len equ $-a
    r times len db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...Se dau 2 siruri de octeti A si B. Sa se construiasca sirul R care sa contina doar elementele impare si pozitive din cele 2 siruri
        
        mov ecx, len
        mov esi, 0
        mov edi, 0
        jecxz final
        
        forindex:
            mov al, [a + esi]
            
            cmp al, 0
            jl nu_e_bine
            
            test al, 1
            jz nu_e_bine    
            
            ;mov bl, albits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ; "%c" caracter = byte
        ; "%d" intreg cu semn = dword dd
        ; "%u" intreg fara semn = dword dd
        ; "%x" un hexa = dword dd
        ; "%s" un string = dword dd
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

            mov [r + edi], al
            inc edi
            
            nu_e_bine:
            
            inc esi
            
        loop forindex
        
        
        final:
            
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
