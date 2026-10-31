bits 32

global _inverseaza

segment data public data use32

segment code public code use32
    _inverseaza:
        push ebp
        mov ebp, esp

        ; ebp + 8   sir1
        ; ebp + 12  ans

        mov edi, [ebp + 12]
        mov esi, [ebp + 8]
        
        mov eax, 0
        push eax
        for1:
            lodsb
            
            cmp al, ' '
            je spatiu
            
            cmp al, 0
            je done
            
            push eax
            jmp for1
            
            spatiu:
                pop eax
                cmp al, 0
                je gata
                
                stosb
            jmp spatiu
            
            gata:
            mov al, ' '
            stosb
            push 0

        jmp for1
        
        done:
        spatiu2:
            pop eax
            cmp al, 0
            je final
            
            stosb
        jmp spatiu2
        
        final:
        mov al, 0
        stosb
        
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