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
segment data use32 class=databits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

    ; ...
    read_name db "input.txt", 0
    read_mode db "r", 0
    read_desc dd 0
    
    x db 0
    citeste_caracter db "%c", 0
    
    scrie db "%c : %d", 13, 10, 0
    
    ans times 50 db 0

; our code starts here
segment code use32 class=code
    start:
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
        
        mov edi, 0
        initi:
            cmp edi, 40
            ja do
            
            mov byte [ans + edi], 0
            inc edi
            jmp initi
        
        do:
            push dword x
            push dword citeste_caracter
            push dword [read_desc]
            call [fscanf]
            add esp, 3 * 4
            
            cmp byte [x], '!'
            je afis
            
            cmp byte [x], ' '
            je do   
            
            cmp byte [x], 'a'
            jl majuscula
            
            mov ebx, 0
            mov bl, [x]
            sub ebx, 'a'
            add byte [ans + ebx], 1
                
            jmp do
            
            majuscula:
            mov ebx, 0
            mov bl, [x]
            sub ebx, 'A'
            add byte [ans + ebx], 1
            
            jmp do
            
        afis:
            
            mov esi, 0
            bucla:
                cmp esi, 48
                jg close
            
                cmp byte [ans + esi], 0
                je nu_avem
            
                mov ebx, esi
                add ebx, 'A'
                
                push dword [ans + esi]
                push ebx
                push dword scrie
                call [printf]
                add esp, 3 * 4
                
                
                nu_avem:
                
                inc esi
                jmp bucla
        
        close: ;dword (descr)
        
            push dword [read_desc]
            call [fclose]
            add esp, 1 * 4
            
        stop:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
