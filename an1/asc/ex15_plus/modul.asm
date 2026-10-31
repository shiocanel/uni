bits 32

global _rezolva

extern _printf
extern _citesteSir

segment data use32
    sirCitit times 256 db 0

segment code use32
    _rezolva:
        push ebp
        mov ebp, esp

        ; ebp + 8  -> n
        ; ebp + 12 -> ans
        
        push dword sirCitit
        call _citesteSir
        add esp, 1 * 4
        
        mov esp, ebp
        pop ebp
        ret
