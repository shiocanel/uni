% Definiti un predicat care determina suma a doua numere scrise in
% reprezentare de lista.


% Se da o lista eterogena, formata din numere intregi si liste de cifre. Sa
% se calculeze suma tuturor numerelor reprezentate de subliste. De ex:
% [1, [2, 3], 4, 5, [6, 7, 9], 10, 11, [1, 2, 0], 6] =>
% [8, 2, 2].


% suma_lista(L1: list of digit, L2: list of digits, Rez: list of digits) -> (i, i, o) determinist
% suma_aux(L1: list, L2: list, Transport: integer, Rez: list) -> (i, i, i, o) determinist


inverseaza_aux([], Acc, Acc).
inverseaza_aux([H | T], Acc, Rez) :-
    inverseaza_aux(T, [H | Acc], Rez).

inverseaza(L, Rez) :-
    inverseaza_aux(L, [], Rez).

suma_aux([], [], 0, []).
suma_aux([], [], 1, [1]).

suma_aux([H1 | T1], [], T, [C | Rez]) :-
    S is H1 + T,
    C is S mod 10,
    T_nou is S // 10,
    suma_aux(T1, [], T_nou, Rez).

suma_aux([], [H2 | T2], T, [C | Rez]) :-
    S is H2 + T,
    C is S mod 10,
    T_nou is S // 10,
    suma_aux([], T2, T_nou, Rez).

suma_aux([H1 | T1], [H2 | T2], T, [C | Rez]) :-
    S is H1 + H2 + T,
    C is S mod 10,
    T_nou is S // 10,
    suma_aux(T1, T2, T_nou, Rez).

suma_lista(L1, L2, Rez) :-
    inverseaza(L1, Inv1),
    inverseaza(L2, Inv2),
    suma_aux(Inv1, Inv2, 0, InvRez),
    inverseaza(InvRez, Rez).


suma_eterogen([], [0]).
suma_eterogen([H | T], Rez) :-
    is_list(H),
    !,
    suma_eterogen(T, RezT),
    suma_lista(H, RezT, Rez).

suma_eterogen([H | T], Rez) :-
    \+ is_list(H),
    suma_eterogen(T, Rez).