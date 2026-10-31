bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program

; declararea functiilor externe folosite de program
extern exit, printf, scanf ; adaugam printf si scanf ca functii externa            
import exit msvcrt.dll    
import printf msvcrt.dll    ; indicam asamblorului ca functia printf se gaseste in libraria msvcrt.dll
import scanf msvcrt.dll     ; similar pentru scanf

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 0
    b db 0
    
    message1 db "a = ", 0
    message2 db "b = ", 0
    
    format db "%d", 0   
    
    mesaj db "Ai scris a = %d si b = %d", 0
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        push dword message1
        call [printf]
        add esp, 4 * 1
        
        
        push dword a
        push dword format
        call [scanf]
        add esp, 4 * 2
        
        
        
        
        push dword message2
        call [printf]
        add esp, 4 * 1
        
        
        push dword b
        push dword format
        call [scanf]
        add esp, 4 * 2
        
        
        
        mov eax, 0
        mov al, [b]
        push dword eax

        mov eax, 0
        mov al, [a]
        push dword eax

        push dword mesaj
        call [printf]
        add esp, 4 * 3
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
