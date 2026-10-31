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
    read_name db "citire.txt", 0
    read_mode db "r", 0
    read_desc dd 0
 
    write_name db "scrie.txt", 0
    write_mode db "w", 0
    write_desc dd 0
    
    scrie_d dd "%d", 0
    
    x db 0, 0

; our code starts here
segment code use32 class=code
    start:
        ; fopen = (name, mode)
        ; fcloase = (descr)

        ; fscanf = (descr, format, var1, var2...)
        ; fprintf = (descr, format, var1, var2...)

        ; scanf = (format, var1, var2...)
        ; printf = (fromat, var1, var2..)
        
        push read_mode
        push read_name
        call [fopen]
        add esp, 2 * 4
        
        cmp eax, 0
        je stop
        
        mov [read_desc], eax
        
        
        push write_mode
        push write_name
        call [fopen]
        add esp, 2 * 4
        
        cmp eax, 0
        je stop
        
        mov [write_desc], eax
            
        do:
        inc byte [x]
        
        push x
        push dword scrie_d
        call [printf]
        add esp, 2 * 4
        
        
        close: ;dword (descr)
        
            push dword [read_desc]
            call [fclose]
            add esp, 1 * 4
            
            
            push dword [write_desc]
            call [fclose]
            add esp, 1 * 4
        
        stop:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
