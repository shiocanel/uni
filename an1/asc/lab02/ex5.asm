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
    a db 10
    b db 20
    c db 22
    d db 33
    
    e dw 100
    f dw 202
    g dw 301
    h dw 333

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        ;f+(c-2)*(3+a)/(d-4)
        mov al, [c]
        sub al, 2 ; c - 2
        mov bl, 3
        add bl, [a] ; 3 + a
        mul bl ; (c - 2) * (3 + a)
        mov bl, [d] 
        sub bl, 4 ; d - 4
        div bl ; ax / bl
        mov ax, [f] 
        add ax, ax ; f + ()
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
