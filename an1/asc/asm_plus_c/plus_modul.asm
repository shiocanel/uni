bits 32

; informam asamblorul ca dorim ca functia _sumaNumere sa fie disponibila altor unitati de compilare
global _sumaNumere

; linkeditorul poate folosi segmentul public de date si pentru date din afara
segment data public data use32

; codul scris in asamblare este dispus intr-un segment public, posibil a fi partajat cu alt cod extern
segment code public code use32

; int sumaNumere(int, int)

_sumaNumere:
    ; creare cadru de stiva pentru programul apelat
    push ebp
    mov ebp, esp
    
    ; obtinem argumentele transmise pe stiva functiei sumaNumere
    ; la locatia [ebp+4] se afla adresa de return (valoarea din EIP la momentul apelului)
    ; la locatia [ebp] se afla valoarea ebp pentru apelant
    mov eax, [ebp + 8]        ; eax <- a
    
    mov ebx, [ebp + 12]        ; ebx <- b
    
    add eax, ebx            ; calculam suma
                            ; valoarea de rezulat a functiei este in eax

    ; refacem cadrul de stiva pentru programul apelant
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
    
    
    
    
    
    ; nasm modulUpper.asm -fwin32 -g -o modulUpper.obj
    ; nasm modulConcatenare.asm -fwin32 -g -o modulConcatenare.obj
    ; cl mainConcatenare.c /link modulConcatenare.obj modulUpper.obj
    ; mainConcatenare.exe