bits 32

global _rezolva

segment data public data use32

segment code public code use32

_rezolva:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]
    mov ebx, [ebp + 12]
    mov ecx, [ebp + 16]
    
    add eax, ebx
    add eax, ecx

    mov esp, ebp
    pop ebp

    ret
    
    
    ; cum dam run la toata nebunia asta
    
    ; intri in native x86
    ; intri in d prin (d:)
    ; si intri in pathu de la folder prin (cd uni) (cd asc) (cd folderu tau)
    
    ; 1) nasm modul.asm -fwin32 -o modul.obj
    ; 2) cl main.c /link modul.obj
    
    ; executa main.exe
    
    
    
    
    
    ; nasm modul1.asm -fwin32 -g -o modul1.obj
    ; nasm modul2.asm -fwin32 -g -o modul2.obj
    ; cl main.c /link modul1.obj modul2.obj
    ; main.exe