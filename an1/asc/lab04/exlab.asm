    bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    
        a dw 0111011101010111b
        b dw 1001101110111110b
        c dw 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
        mov al,       11010001b
        mov bl,       10111101b
        
        and al, bl   ;10010001b
        
        
        mov al, 1100 0011
        sar al, 1 ;al = 1110 0001  aici se completeaza cu 1  CF = 1
        
        mov al, 1100 0011
        sal al, 1; al = 100 00110 deci aici e important sa punem 0 nu 1
        
        
        ; shr -> shiftare la dreapta
        ; shr <reg> / <mem>, <con8> / Cl
        ; 0110 1100 -> 000110 11 shiftare la dreapta
        ; in CF se salveaza bitul care iese CF= 0 si apoi iar CF = 0
     
        ; shl -> shiftare la stanga
        ; shl <reg>/<mem>, <con8>/Cl
        ; 0110 1100 -> 10 110000 shiftare la stanga
        
        ; sar -> shift arithmetic rigt
        ; sar <reg>/<mem>, <con8>/CL
        
        
        ; sal -> shift arithmetic left     practic un simplu shl
        ; sal <reg>/<mem>, <con8>/CL
        
        
        ; ror -> rotire right
        ; ror <reg>/<mem>, <con8>/CL
        
        ; rol -> rotire left
        ; rol <reg>/<mem>, <con8>/CL
     
        mov al, 10110001b
        ror al, 1; 1 1011 000 CF = 1 ala care se roteste
        
        rol al, 1; 1011 0001 Cf = 1 deci inapoi fuuun
        
        ; rcr -> rotate with carry right
        ; rcr <reg>/<mem>, <con8>/CL
        
        ; rcl -> rotate with carry left
        ; rcl <reg>/<mem>, <con8>/CL
        
        shr al, 8; al = 0
        shr ax, 16; Ax = 0
        shr EAX, 32; eax ramane nemodificat 
        ; operatiile se fac mmodulo 32 atent!!!!
        
        rcr al, 9; al ramane nemodificat
        rcr ax, 17; ax ramane nemodificat
        rcr eax, 33; eax se modifica
        
        ; izolarea bitilor
        ; izolarea bitilor 2 - 5, iar restul sa-i zerofie
        
        ; 1 & x = x
        ; 0 & x = 0
        
        ; 1 | x = 1
        ; 0 | x = x
        
        ; 1 ^ x = ~x
        ; 0 ^ x = x
        
        and al, 00111100b
        
        
        mov ax, 0
        mov bx, [b]
        and bx,  1110000000000b ; de la dreapta spre stanga de la o la n
        shr bx, 10 ; vreau sa fie pe pozitia 0-2
        
        or ax = 1111000b 
        
        or ax, bx ; practic duce bx in ax interesant
        ; 3 - 6 sa fie 1
        
        mov bx, [a]
        and bx, 11110b ; am nevoie de 1 - 4
        shl bx, 6 ; vreau sa fie la pozitia 7 - 10
        
        or ax, bx ; acum il am in c
        
        mov bx, [b]
        not bx ; vreau doar inversul bitilor de la 9 - 11 mai intai fac  asa
        and bx, 111000000000b ; si doar dupa masca
        or ax, bx
        
        
        mov [c], eax
        
        ; Saptamana 5 TEST
        ; Saptamana 6 Tema
     
     
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
