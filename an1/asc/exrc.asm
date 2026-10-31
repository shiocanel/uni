bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    msg db "Da un numar: ", 0
    numar dd 0
    citeste_intreg dd "%d", 0
    
    afis db "Suma este: %d", 13, 10, 0
    
    
; our code starts here
segment code use32 class=code
    start:
        mov ebx, 0
        
        read:
            push msg
            call [printf]
            add esp, 1 * 4
            
            push dword numar ; e pe double word
            push citeste_intreg
            call [scanf]
            add esp, 2 * 4
            
            cmp byte [numar], 0
            je print
            
            mov ecx, 0
            mov cl, [numar]
            
            add ebx, ecx
            
        jmp read
        
        print:

            push ebx
            push afis
            call [printf]
            add esp, 2 * 4

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
