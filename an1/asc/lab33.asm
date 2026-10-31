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
    b db 2
    c dw 3
    e dd 2
    x dq 2
    doi dd 2
    
; our code starts here
segment code use32 class=code
    start:
        ; (a+b*c+2/c)/(2+a)+e+x;
        
        mov eax, 0
        mov al, [b]
        mul word [c]
        
        push dx
        push ax
        
        pop ebx
        
        
        mov dx, 0
        mov ax, 2
        
        div word [c]
        
        mov ecx, 0        
        mov cx, ax
        
        add ebx, ecx
        
        mov ecx, 0
        mov cl, [a]
        
        add ebx, ecx ; 1()

        push ebx
        
        pop ax
        pop dx ; 1()
        
        
        
        
        
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
