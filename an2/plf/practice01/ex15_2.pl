% 15.
% a) Sa se determine cea mai lunga secventa de numere pare consecutive dintr-o
%    lista (daca sunt mai multe secvente de lungime maxima, una dintre ele).
% b) Se da o lista eterogena, formata din numere intregi si liste de numere
%    intregi. Sa se inlocuiasca fiecare sublista cu cea mai lunga secventa de
%    numere pare consecutive din sublista respectiva. De ex:
%    [1, [2, 1, 4, 6, 7], 5, [1, 2, 3, 4], 2, [1, 4, 6, 8, 3], 2, [1, 5], 3] =>
%    [1, [4, 6], 5, [2], 2, [4, 6, 8], 2, [], 3]

% =========================================================================
% MODELE MATEMATICE
% =========================================================================

% inverseaza_aux(L, Acc) = 1. Acc, daca L = []
%                          2. inverseaza_aux(l2...ln, l1 + Acc), altfel
%
% inverseaza(L) = inverseaza_aux(L, [])

% secv_max_aux(L, SecvCrt, LungCrt, SecvMax, LungMax) =
%    1. inv(SecvCrt), daca L = [] si LungCrt > LungMax
%    2. inv(SecvMax), daca L = [] si LungCrt <= LungMax
%    3. secv_max_aux(l2...ln, l1 + SecvCrt, LungCrt + 1, SecvMax, LungMax), daca l1 mod 2 = 0
%    4. secv_max_aux(l2...ln, [], 0, SecvCrt, LungCrt), daca l1 mod 2 != 0 si LungCrt > LungMax
%    5. secv_max_aux(l2...ln, [], 0, SecvMax, LungMax), daca l1 mod 2 != 0 si LungCrt <= LungMax

% secventa_para_max(L) = secv_max_aux(L, [], 0, [], 0)

% inlocuieste_eterogen(L) =
%    1. [], daca L = []
%    2. secventa_para_max(l1) + inlocuieste_eterogen(l2...ln), daca is_list(l1)
%    3. l1 + inlocuieste_eterogen(l2...ln), altfel

% =========================================================================
% MODELE DE FLUX
% =========================================================================
% inverseaza_aux(L: list, Acc: list, Rez: list) -> (i, i, o) determinist
% inverseaza(L: list, Rez: list) -> (i, o) determinist
% secv_max_aux(L: list, SecvCrt: list, LungCrt: integer, SecvMax: list, LungMax: integer, Rez: list) -> (i, i, i, i, i, o) determinist
% secventa_para_max(L: list of integer, Rez: list of integer) -> (i, o) determinist
% inlocuieste_eterogen(L: list, Rez: list) -> (i, o) determinist

% =========================================================================
% IMPLEMENTARE SWI-PROLOG
% =========================================================================

% --- Predicat auxiliar de inversare ---
inverseaza_aux([], Acc, Acc).
inverseaza_aux([H | T], Acc, Rez) :-
    inverseaza_aux(T, [H | Acc], Rez).

inverseaza(L, Rez) :-
    inverseaza_aux(L, [], Rez).

% --- Punctul 15.a: Cea mai lunga secventa de numere pare consecutive ---
% SecvCrt si SecvMax retin elementele in ordine inversa (ca acumulatori) pentru eficienta O(N)

% Cazul de baza (lista s-a terminat): alegem cea mai lunga dintre secventa curenta si cea maxima
secv_max_aux([], SecvCrt, LungCrt, _, LungMax, Rez) :-
    LungCrt > LungMax, !,
    inverseaza(SecvCrt, Rez).

secv_max_aux([], _, _, SecvMax, _, Rez) :-
    inverseaza(SecvMax, Rez).

% Cazul 1: Elementul curent H este PAR -> il adaugam la secventa curenta si crestem lungimea
secv_max_aux([H | T], SecvCrt, LungCrt, SecvMax, LungMax, Rez) :-
    H mod 2 =:= 0, !,
    LungCrtNou is LungCrt + 1,
    secv_max_aux(T, [H | SecvCrt], LungCrtNou, SecvMax, LungMax, Rez).

% Cazul 2: Elementul curent H este IMPAR si secventa curenta tocmai terminata bate maximul anterior
secv_max_aux([H | T], SecvCrt, LungCrt, _, LungMax, Rez) :-
    H mod 2 =\= 0,
    LungCrt > LungMax, !,
    secv_max_aux(T, [], 0, SecvCrt, LungCrt, Rez).

% Cazul 3: Elementul curent H este IMPAR, dar secventa curenta NU bate maximul anterior
secv_max_aux([H | T], _, _, SecvMax, LungMax, Rez) :-
    H mod 2 =\= 0,
    secv_max_aux(T, [], 0, SecvMax, LungMax, Rez).

% Predicatul principal pentru 15.a
secventa_para_max(L, Rez) :-
    secv_max_aux(L, [], 0, [], 0, Rez).

% --- Punctul 15.b: Inlocuirea sublistelor dintr-o lista eterogena ---
inlocuieste_eterogen([], []).

inlocuieste_eterogen([H | T], [H_secv | Rez]) :-
    is_list(H), !,
    secventa_para_max(H, H_secv),
    inlocuieste_eterogen(T, Rez).

inlocuieste_eterogen([H | T], [H | Rez]) :-
    \+ is_list(H),
    inlocuieste_eterogen(T, Rez).
