bits 32

global _concateneaza

segment data public data use32

segment code public code use32
    _concateneaza:
        push ebp
        mov ebp, esp

        ; ebp + 8   sir1
        ; ebp + 12  sir2
        ; ebp + 16  sir3
        ; ebp + 20  ans

        mov edi, [ebp + 20]
        
        mov esi, [ebp + 8]
        for1:
            lodsb
            test al, al
            jz sir2
            stosb
        jmp for1

        sir2:
        mov esi, [ebp + 12]
        
        for2:
            lodsb
            test al, al
            jz sir3
            stosb
        jmp for2

        sir3:
        mov esi, [ebp + 16]
        
        for3:
            lodsb
            test al, al
            jz done
            stosb
        jmp for3

        done:
        mov byte [edi], 0 ; foarte important asta
        
        mov eax, edi
        sub eax, [ebp + 20]
        
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