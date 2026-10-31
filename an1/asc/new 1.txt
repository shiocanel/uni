bits 32

global _citesteSir

extern _printf

segment data use32
    mesaj db "Citeste sir: ",0

segment code use32
_citesteSir:
    push ebp
    mov ebp, esp

    push mesaj
    call _printf
    add esp, 4

    mov esp, ebp
    pop ebp
    ret
