bits 32
global start

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    msg db "Dati un cuvant: ", 0
    current_word times 50 db 0
    read_format db "%s", 0
    print_format db "Cuvantul %s are %d litere", 13, 10, 0

; 1. Scrieti un program care citeste de la tastatura, in mod repetat, cuvinte
; si care afiseaza pe ecran cuvantul citit si numarul de litere pe care le contine.
; Citirea se termina la introducerea caracterului '!'.
segment code use32 class=code
    start:     
    read:
        ; print a message to the user
        ; printf(msg)
        push msg
        call [printf]
        add esp, 1*4
        
        ; read the word
        ; scanf(read_format, &current_word)
        push current_word
        push read_format
        call [scanf]
        add esp, 2*4
        
        ; check the stop condition
        cmp byte [current_word], '!'
        je stop
        
        ; count the number of chars in the current word
        mov ebx, 0      ; counter
        mov esi, 0      ; index
        count:
            cmp byte [current_word+esi], 0 ; daca e la sfarsit gata
            je print
            inc ebx     ; count the letter
            inc esi     ; go to the next letter
            jmp count

    print:
        ; print the result on the screen
        ; printf(print_format, current_word, count)
        push ebx
        push current_word
        push print_format
        call [printf]
        add esp, 3*4
        
        jmp read
        
    stop:
        ; exit(0)
        push dword 0        ; push the parameter for exit onto the stack
        call [exit]         ; call exit to terminate the program
