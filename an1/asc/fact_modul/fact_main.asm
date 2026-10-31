; asm + asm

bits 32

global start

extern exit, fopen, fscanf, fprintf, fclose, printf, scanf
import exit msvcrt.dll
import fopen msvcrt.dll
import fscanf msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

extern factorial

segment data use32
	afis_factorial db "factorial = %d", 10, 13, 0

segment code use32 public code
    start:
        push dword 6
        call factorial

        push eax
        push afis_factorial
        call [printf]
        add esp, 2*4

        push 0
        call [exit]

        ; pasi de rezolvare si executare
        
        ; pui tot intr-un folder
        ; sa ai un main.asm si un modul.asm
        ; copiezi nasm.exe si alink.exe
        ; intri in pathu de la folder si de acolo intri in cmd
        
        ; 1) nasm -fobj modul.asm
        ; 2) nasm -fobj main.asm
        ; 3) alink main.obj modul.obj -oPE -subsys console -entry start
        
        ; executi main.exe
        ; ...