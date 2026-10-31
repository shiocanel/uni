bits 32

global _oglindit

segment data public data use32

segment code public code use32
    _oglindit:
        push ebp
        mov ebp, esp

        ; ebp + 8   sir1
        ; ebp + 12  ans

        
        mov edi, [ebp + 12]
        mov esi, [ebp + 8]
        
        mov eax, 0
        push eax
        repeta:
            lodsb
            test al, al
            jz done
            
            push eax 
        jmp repeta
        
        done:
            pop eax
            test al, al
            jz final
            
            stosb
        jmp done
        
        final:
        mov byte [edi], 0
        
        mov eax, edi
        sub eax, [ebp + 12]
        
        mov esp, ebp
        pop ebp

        ret