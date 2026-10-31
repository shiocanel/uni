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
    ; ... toate var si apoi mesajele/formatele
    n dd 0 ; vezi sa pui mereu variabilele ca dd astfel sa nu ai problemeeee
    
    mesaj_n db "n = ", 0
    format_n db "%d", 0
    afis_n db "Numarul citit este: %d !!", 0
    
    

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        push dword mesaj_n ; punem mereu dword (asta inseamna 1 parametru)
        call [printf]
        add esp, 1 * 4
        
        push dword n
        push dword format_n
        call [scanf]
        add esp, 2 * 4
        
        push dword [n]
        push dword afis_n
        call [printf]
        add esp, 2 * 4
        
        
        
        
        ; daca vrei sa salvezi ceea ce ai in registrii, mai intai ii pui pe stiva si apoi le dai pop, pentru ca functiile modifica valorile registrilor
        ; deci faci asa
        
        ; pushad
        ; apelezi functia
        ; popad
        
        ; ezzzz
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
