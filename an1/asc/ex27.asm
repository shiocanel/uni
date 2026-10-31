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
    read_mode db "r+", 0
    read_desc dd 0
    
    citeste_n dd "%d", 0
    n dd 0
    
    mn dd, -1
 

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
        
        do:
            push dword n
            push dword [read_desc]
            call [fscanf]
            add esp, 2 * 4
            
            cmp dword [n], 0
            jmp close
            cmp dword [n], [mx]
            jl mai_mare
            
            
            
            mai_mare:
        
            jmp do
        
        
        close: ;dword (descr)
        
            push dword [read_desc]
            call [fclose]
            add esp, 1 * 4
            
        stop:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
