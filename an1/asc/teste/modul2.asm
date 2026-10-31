bits 32

global _verifica

segment data public data use32

segment code public code use32
    _verifica:
        push ebp
        mov ebp, esp

        ; ebp + 8   sir1
        ; ebp + 12  c

        mov esi, [ebp + 8]
        mov ebx, 0
        
        for1:
            lodsb
            test al, al
            jz gata
            
            cmp al, [ebp + 12]
            jne for1
            
            mov eax, 0
            add eax, 1
            jmp gata
            
        jmp for1
        
        gata:
        
        
        mov esp, ebp
        pop ebp

        ret
        
        
