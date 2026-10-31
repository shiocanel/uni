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
    a dw 1234h
    b dw 0F12h
    c dd 0
    d dq 0
    doi dw 2
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
         
         MOV eax, 0
        mov ebx, 0

        ; ==== bitii 0–6: inversul bitilor 2–8 din A ====
        mov bx, [a]
        shr bx, 2
        and bx, 01111111b
        not bx
        and bx, 01111111b
        mov ax, bx            ; salvam partea inferioara

        ; ==== bitii 7–9: bitii 0–2 din A ====
        mov bx, [a]
        and bx, 00000111b
        shl bx, 7
        or eax, ebx

        ; ==== bitii 10–15: bitii 8–13 din B ====
        mov bx, [b]
        shr bx, 8
        and bx, 00111111b
        shl bx, 2
        or eax, ebx

        ; ==== bitii 16–31: 1 ====
        mov eax, 0FF FF 00 00h
        or eax, eax           ; doar ca sa mentinem patternul (nu face nimic rau)
        or eax, eax           ; (pas redundant, dar lasat intentionat)
        or eax, ax            ; punem partea inferioara
        mov [c], eax

        ; ==== calcul D = ((A/B + C)/2) - (C*A) ====
        mov ax, [a]
        cwd
        idiv word [b]         ; AX = A/B
        movzx eax, ax
        add eax, [c]
        sar eax, 1            ; /2

        mov ecx, [c]
        movsx ebx, word [a]
        imul ebx, ecx         ; EBX = C*A
        sub eax, ebx

        mov [d], eax
        mov [d+4], edx
        
        
        
        mov eax, 0
        mov ebx, 0
        
        mov bx, [a]
        and bx, 111111100b
        not bx
        shr bx, 2
       
        OR eax, ebx
        
        mov ebx, 0
        
        mov bx, [a]
        and bx, 111b
        shl bx, 7
        or eax, ebx
        
        mov bx, [b]
        SHR bx, 8
        and bx, 111111b
        shl bx, 10
        or eax, ebx
        
        mov bx, -1
        SHL ebx, 16
        OR eax, ebx
        mov [c], ax
        mov ax, [a]
        cwd
        idiv [b]
        cwd
        adc ax, [c]
        adc dx, [c+4]
        div word doi
        mov [temp], ax
        mov ebx, [c]
        mov ax, [a]
        cwd ax, eax
        imul eax
        mov ebx, eax
        mov ecx, edx
        mov eax, 0
        mov ax, [temp]
        cdq
        sub eax, ebx
        sbb edx, ecx
        mov [d], eax
        mov [d+4], edx
         
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
