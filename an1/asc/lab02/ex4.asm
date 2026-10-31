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
    b db 23
    c db 33
    d dw 200

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        ;200-[3*(c+b-d/a)-300]
        mov ax, [d]; 
        div byte [a]; d / a  ????                     
        mov bl, [c]
        add bl, [b] ; c + b
        sub bl, al  ; c + a - d / a         
        mov al, 3
        mul bl  ; * 3
        sub ax, 300 
        mov bx, 200
        sub bx, ax ; 200 - (       
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
