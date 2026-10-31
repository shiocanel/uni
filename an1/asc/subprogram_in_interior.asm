bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

extern exit, fopen, fscanf, fprintf, fclose, printf, scanf
import exit msvcrt.dll
import fopen msvcrt.dll
import fscanf msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    afis_factorial db "factorial = %d", 10, 13, 0
    
; our code starts here
segment code use32 class=code
    factorial:
        mov eax, 1
        mov ecx, [esp + 4] ; luam primul parametru din functie
                           ; pentru ca la esp avem adresa de returnare
                           ; adresa_ret    --> esp
                           ; 000000006h    --> esp + 4
        
        .repeta:
            mul ecx
        loop .repeta
        
        ret
    
    start:
        ; ...
        
        push dword 6 ; adica pe asta
        call factorial
        
        push eax
        push dword afis_factorial
        call [printf]
        add esp, 2 * 4
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
