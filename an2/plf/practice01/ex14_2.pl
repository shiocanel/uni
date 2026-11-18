% 14.
% a) Definiti un predicat care determina predecesorul unui numar reprezentat
%    cifra cu cifra intr-o lista. De ex: [1 9 3 6 0 0] => [1 9 3 5 9 9]
% b) Se da o lista eterogena, formata din numere intregi si liste de cifre.
%    Pentru fiecare sublista sa se determine predecesorul numarului reprezentat
%    cifra cu cifra de lista respectiva. De ex:
%    [1, [2, 3], 4, 5, [6, 7, 9], 10, 11, [1, 2, 0], 6] =>
%    [1, [2, 2], 4, 5, [6, 7, 8], 10, 11, [1, 1, 9], 6]

% =========================================================================
% MODELE MATEMATICE
% =========================================================================

% inverseaza_aux(L, Acc) = 1. Acc, daca L = []
%                          2. inverseaza_aux(l2...ln, l1 + Acc), altfel
%
% inverseaza(L) = inverseaza_aux(L, [])

% predecesor_aux(L, Imp) = 1. [], daca L = []
%                          2. (l1 - Imp) + predecesor_aux(l2...ln, 0), daca l1 - Imp >= 0
%                          3. 9 + predecesor_aux(l2...ln, 1), daca l1 - Imp < 0 (adica l1 = 0 si Imp = 1)

% elimina_zero(L) = 1. l2...ln, daca l1 = 0 si n > 1 (ex: [0, 9, 9] -> [9, 9])
%                   2. L, altfel

% predecesor_lista(L) = elimina_zero(inv(predecesor_aux(inv(L), 1)))

% predecesor_eterogen(L) = 1. [], daca L = []
%                          2. predecesor_lista(l1) + predecesor_eterogen(l2...ln), daca is_list(l1)
%                          3. l1 + predecesor_eterogen(l2...ln), altfel

% =========================================================================
% MODELE DE FLUX
% =========================================================================
% inverseaza_aux(L: list, Acc: list, Rez: list) -> (i, i, o) determinist
% inverseaza(L: list, Rez: list) -> (i, o) determinist
% predecesor_aux(L: list, Imp: integer, Rez: list) -> (i, i, o) determinist
% elimina_zero(L: list, Rez: list) -> (i, o) determinist
% predecesor_lista(L: list of digit, Rez: list of digit) -> (i, o) determinist
% predecesor_eterogen(L: list, Rez: list) -> (i, o) determinist

% =========================================================================
% IMPLEMENTARE SWI-PROLOG
% =========================================================================

% --- Predicat auxiliar de inversare ---
inverseaza_aux([], Acc, Acc).
inverseaza_aux([H | T], Acc, Rez) :-
    inverseaza_aux(T, [H | Acc], Rez).

inverseaza(L, Rez) :-
    inverseaza_aux(L, [], Rez).

% --- Punctul 14.a: Predecesorul unui numar-lista ---
% Imp reprezinta imprumutul (borrow): 1 daca trebuie sa scadem 1, 0 altfel
predecesor_aux([], _, []).

% Cazul in care nu mai avem nimic de scazut (Imp = 0) -> copiem cifrele ramase
predecesor_aux([H | T], 0, [H | Rez]) :-
    !,
    predecesor_aux(T, 0, Rez).

% Cazul in care trebuie sa scadem 1 (Imp = 1), iar cifra curenta H > 0 -> nu se propaga imprumutul
predecesor_aux([H | T], 1, [C | Rez]) :-
    H > 0, !,
    C is H - 1,
    predecesor_aux(T, 0, Rez).

% Cazul in care trebuie sa scadem 1 (Imp = 1), iar cifra curenta H = 0 -> devine 9 si imprumutam 1 mai departe
predecesor_aux([0 | T], 1, [9 | Rez]) :-
    predecesor_aux(T, 1, Rez).

% Elimina zeroul nesemnificativ din fata daca numarul scade cu o cifra (ex: [1, 0, 0] -> [0, 9, 9] -> [9, 9])
% Daca lista este doar [0] (adica predecesorul lui [1]), il pastreaza pe 0.
elimina_zero([0, H | T], [H | T]) :- !.
elimina_zero(L, L).

% Predicatul principal pentru 14.a
predecesor_lista(L, Rez) :-
    inverseaza(L, InvL),
    predecesor_aux(InvL, 1, InvRez),
    inverseaza(InvRez, RezBrut),
    elimina_zero(RezBrut, Rez).

% --- Punctul 14.b: Predecesorul pentru fiecare sublista din lista eterogena ---
predecesor_eterogen([], []).

predecesor_eterogen([H | T], [H_pred | Rez]) :-
    is_list(H), !,
    predecesor_lista(H, H_pred),
    predecesor_eterogen(T, Rez).

predecesor_eterogen([H | T], [H | Rez]) :-
    \+ is_list(H),
    predecesor_eterogen(T, Rez).
