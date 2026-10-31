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
    a dw 10
    b db 2
    c db 2
    d db 2
    
    x dq 10
    
    doi db 2
    
; our code starts here
segment code use32 class=code
    start:
        ; ...a-(7+x)/(b*b-c/d+2); a-doubleword; b,c,d-byte; x-qword
        
        mov al, [c]
        cbw
        div byte [d]
        
        mov bx, ax ; bx = c / d
        
        mov al, [b]
        cbw
        mul byte [b]
        
        cwde
        sub ax, bx
        sbb ax, 0
        
        add al, [doi]
        adc al, 0

        mov ebx, eax ; impartitorul

        mov al, 7
        cbw
        cwde
        cdq
        add eax, [x]
        add edx, [x + 4]
        ; edx:eax = 7 + x
        
        
        
        
           
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
