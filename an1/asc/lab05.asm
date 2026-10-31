bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...; Se dau doua cuvinte A si B. Sa se obtina dublucuvantul C:
; bitii 0-6 ai lui C au valoarea inversului bitilor 2-8 ai lui A
; bitii 7-9 ai lui C coincid cu bitii 0-2 ai lui A
; bitii 10-15 ai lui C coincid cu bitii 8-13 ai lui B
; bitii 16-31 ai lui C au valoarea 1

; Dupa crearea dublucuvantului C, quadwordul D va avea valoarea urmatoarei expresii in interpretarea cu semn:
;d = [(a/b + c) / 2] - (c*a)
bits 32
global  start

extern  exit
import  exit msvcrt.dll

segment  data use32 class=data
    a dw 0110001110110101b
    b dw 1010000100110110b
    c dd 0
    d dq 0
    temp dw 0
    doi dw 2
segment  code use32 class=code
start:
    mov eax, 0
    mov ebx, 0
    
    mov bx, [a] ; 0110001110110101b
    not bx ;      1001110001001010b ordinea conteaza
    and bx, 111111100b ; 0000000 0010010 00b    
    shr bx, 2 ; 00000000010010b
    OR eax, ebx ; eax = 00000000010010b
    
    mov ebx, 0
    mov bx, [a] ; 0110001110110101b
    and bx, 111b ;0000000000000101b
    shl bx, 7   ; 1010000000b
    or eax, ebx ; oru
    
    mov bx, [b] ; 10 100001 00110110b
    SHR bx, 8   ; 10 100001b
    and bx, 111111b
    SHL bx, 10 
    or eax, ebx ; ebx
    
    mov bx, -1 ; eax = 00 00 FF FF h
    SHL ebx, 16 ; eax = FF FF 00 00 h
    OR eax, ebx
    mov [c], eax
    
    mov ax, [a]
    cwd ; 
    idiv word [b] ; ax:dx
    
    cwd 
    adc ax, [c] ; ax + 
    adc dx, [c+4]
    
    div 2
    ; div word doi ; nu putem cu constante
    
    ;mov [temp], ax
    ;mov ebx, [c]
    ;mov ax, [a]
    ;cwd ax, eax
    ;imul eax
    ;mov ebx, eax
    ;mov ecx, edx
    ;mov eax, 0
    ;mov ax, [temp]
    ;cdq
    ;sub eax, ebx
    ;sbb edx, ecx
    ;mov [d], eax
    ;mov [d+4], edx
    push dword 0
    call [exit]
