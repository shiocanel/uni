bits 32
global start

extern exit, fopen, fscanf, fprintf, fclose, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fscanf msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
	file_name db "numere.txt", 0
    file_mode db "r", 0
    file_desc dd 0
    
    file_name2 db "rezultat.txt", 0
    file_mode2 db "w", 0
    file_desc2 dd 0
    
    n dd 0
    read_format db "%d", 0
    print_format db "Suma este %d", 0
    
; 3. Scrieti un program care citeste numere intregi dintr-un
; fisier dat si care afiseaza pe ecran, la final, suma acestora.
segment code use32 class=code
    start:
        ; open the file
        ; EAX = fopen(file_name, file_mode)
        push file_mode
        push file_name
        call [fopen]
        add esp, 2*4
        
        cmp eax, 0
        je open_error
		
		mov [file_desc], eax  

        
        
        push file_mode2
        push file_name2
        call [fopen]
        add esp, 2 * 4
        
        cmp eax, 0
        je open_error
        
        mov [file_desc2], eax
        
        ; do the sum
        xor ebx, ebx			; sum in EBX
    do:
        ; read a number
        ; EAX = fscanf(file_desc, read_format, &n)
        push n
        push read_format
        push dword [file_desc]
        call [fscanf]
        add esp, 3*4
        
        ; check if number was read successfully
        cmp eax, 1
        jne close
        
        ; add the number
        add ebx, [n]
    
        jmp do
        
    close:
  
        
        ; print the sum
        ; printf(print_format, sum)
        push ebx
        push print_format
        call [printf]
        add esp, 2*4
        

        push ebx
        push dword print_format
        push dword [file_desc2]
        call [fprintf]
        add esp, 3 * 4
        
        
        ; close the file
        ; fclose(file_desc)
        push dword [file_desc]
        call [fclose]
        add esp, 1*4
        
        push dword [file_desc2]
        call [fclose]
        add esp, 1 * 4
        
    open_error:
        ; exit(0)
        push dword 0
        call [exit]
