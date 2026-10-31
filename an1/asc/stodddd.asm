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
    sir DD 12AB5678h, 1256ABCDh, 12344344h
    ;      12345678h, 1256ABCDh, 12AB4344h.
    ;      1234, 1256, 12AB.
    len equ ($ - sir) / 4
    aux times len dw 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov esi, sir
        mov ecx, len
        mov edi, 0
        cld
        
        bucla:
            lodsw
            lodsw ; ax = cuvantul superior
            
            mov [aux + edi], ax
            add edi, 2
        loop bucla
        
        mov ecx, 0
        
        for1:
            mov ebx, ecx
         
            for2:
                mov ax, [aux + ecx]
                mov dx, [aux + ebx]
                
                cmp ax, dx
                jl mai_mic
                mov word [aux + ebx], ax
                mov word [aux + ecx], dx
                
                mai_mic:
                add ebx, 2
                cmp ebx, 2 * len
                jl for2

                
            add ecx, 2
            cmp ecx, 2 * len
            jl for1
        
        
        mov esi, 0
        mov edi, 0
        
        for3:
            mov ax, [aux + edi]
            mov word [sir + esi + 2], ax
            
            add esi, 4
            add edi, 2
            cmp edi, 2 * len
            jl for3
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
