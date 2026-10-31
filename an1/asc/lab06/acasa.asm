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

    a dw 1001111100111010b ;...01b
    b dd 0h
        
; our code starts here
segment code use32 class=code
    start:
        ; ...Se da un cuvant A. Sa se obtina dublucuvantul B astfel:
            ;bitii 0-3 ai lui B sunt 0;
            ;bitii 4-7 ai lui B sunt bitii 8-11 ai lui A
            ;bitii 8-9 si 10-11 ai lui B sunt bitii 0-1 inversati ca valoare ai lui A (deci de 2 ori) ;
            ;bitii 12-15 ai lui B sunt biti de 1
            ;bitii 16-31 ai lui B sunt identici cu bitii 0-15 ai lui B.
        
        mov eax, 0 ; 1)
        
        mov ebx, 0
        mov bx, [a]
        
        shr ebx, 8
        and ebx, 1111b ; facem masca
        shl ebx, 4 ; il shiftam la pozitia 4
        
        or eax, ebx ; 2) il salvm

        mov ebx, 0
        mov bx, [a]
        not bx
        and ebx, 11b

        shl ebx, 8
        or eax, ebx ; 3.1)
        
        shl ebx, 2
        or eax, ebx ; 3.2)

        or eax, 1111000000000000b ; 4)
        
        
        mov ebx, 0
        mov bx, ax ; salva prima jumate
        
        mov eax, 0
        or eax, ebx ; punem prima parte in ans
        
        shl eax, 16
        or eax, ebx ; punem 2 parte in ans
        
        mov eax, [b]
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
