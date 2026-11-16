% Sa se scrie un predicat care sa testeze daca o lista formata din numere
% intregi are aspect de "vale"(o multime se spune ca are aspect de "vale"
%  daca elementele descresc pana la un moment dat, apoi cresc. De ex. 
% 10 8 6 9 11 13)

% Sa se calculeze suma alternanta a elementelor unei liste
% l1 - l2 + l3 ...).

%              1. adevarat, daca L = [x1, x2], si F = 1 si x1 < x2 
% vale(L, F) = 2. vale(l2...ln, 0), daca f = 0 si x1 > x2 
%              3. vale(l2...ln, 1), daca f = 0 si x1 < x2
%              4. vale(l2...ln, 1), daca f = 1 si x1 < x2
%              5. fals, altfel

% vale_main(L) = 1. vale(L, 0), daca l1 > l2
%                2. altfel

% vale(L: List, F: Element) -> (i, i) determinist


vale([_], 1) :- !.
vale([E1, E2 | T], 0) :-
    E1 > E2,
    !,
    vale([E2 | T], 0).

vale([E1, E2 | T], 0) :-
    E1 < E2,
    !,
    vale([E2 | T], 1).

vale([E1, E2 | T], 1) :-
    E1 < E2,
    !,
    vale([E2 | T], 1).

vale_main([E1, E2 | T]) :-
    E1 > E2,
    vale([E2 | T], 0).



% suma_alt(L) = suma_aux(L, 1, 0)

suma_aux(L, Semn, Acc) = suma_aux(l2...ln, -Semn, Acc + l1 * (Semn))

suma_aux([], _, Acc, Acc).
suma_aux([H | T], Semn, Acc, Rez) :-
    AccNou is Acc + Semn * H,
    SemnNou is -Semn,
    suma_aux(T, SemnNou, AccNou, Rez).

suma_alt(L, Rez) :-
    suma_aux(L, 1, 0, Rez).