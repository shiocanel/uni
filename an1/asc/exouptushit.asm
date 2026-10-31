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
    sir db "abcdefghij", 0

    file_name db "output-0.txt", 0
    file_mode db "a", 0
    file_desc dd 0

    n dd 0
    msg db "n= ", 0
    citeste_n dd "%d", 0
    
    scrie_c db "%c", 0
    
    
    scrie_s dd "%s", 0
    eroare_mesaj db "Nu e bine tati", 0
    la_revedere db "La revedere!", 0
    
    
; our code starts here
segment code use32 class=code
    start:
        ; fopen = (name, mode)
        ; fcloase = (descr)

        ; fscanf = (descr, format, var1, var2...)
        ; fprintf = (descr, format, var1, var2...)

        ; scanf = (format, var1, var2...)
        ; printf = (fromat, var1, var2..)
        
        push msg
        call [printf]
        add esp, 1 * 4
        
        push dword n
        push citeste_n
        call [scanf]
        add esp, 2 * 4
        
        cmp dword [n], 255
        jg eroare
        
        
        mov ebx, 0 ; contor i
        do:
            cmp ebx, [n]
            ja stop
            
            add ebx, '0'
            mov [file_name + 7], ebx
            sub ebx, '0'
            
            push file_mode
            push file_name
            call [fopen]
            add esp, 2 * 4
            
            cmp eax, 0
            je stop
            
            mov [file_desc], eax

            mov esi, 0

            bucla:
                cmp esi, ebx
                jg inchide
                
                push dword [sir + esi]
                push dword scrie_c
                push dword [file_desc]
                call [fprintf]
                add esp, 3 * 4
                
                inc esi
                jmp bucla
            
            inchide:
            
            push dword [file_desc]
            call [fclose]
            add esp, 1 * 4
            
            inc ebx
            jmp do
        
        
        stop:
            push la_revedere
            call [printf]
            add esp, 1 * 4
            
            jmp gata
        
        eroare:
            push eroare_mesaj
            call [printf]
            add esp, 1 * 4
            
        gata
            ;..
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
