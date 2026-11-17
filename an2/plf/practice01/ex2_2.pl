% Sa se sorteze o lista cu pastrarea dublurilor. De ex: [4 2 6 2 3 4] => [2
% 2 3 4 4 6]

% Se da o lista eterogena, formata din numere intregi si liste de numere. Sa 
% se sorteze fiecare sublista cu pastrarea dublurilor. De ex
% [1, 2, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] =>
% [1, 2, [1, 4, 4], 3, 6, [1, 3, 7, 9, 10], 5, [1, 1, 1], 7].



% sorteaza(L) = insereaza(l1, sorteaza(l2...ln))

% insereaza(E, L) = 1. E + l1...ln, daca E <= l1
%                   2. l1 + insereaza(E, l2...ln), altfel
                  % 3. [E], daca L = []

insereaza(E, [], [E]).
insereaza(E, [H | T], [E, H | T]) :-
    E =< H,
    !.
insereaza(E, [H | T], [H | Rez]) :-
    E > H,
    insereaza(E, T, Rez).

sorteaza([], []).
sorteaza([H | T], Rez) :-
    sorteaza(T, RezT),
    insereaza(H, RezT, Rez).



sorteaza_eterogen([], []).
sorteaza_eterogen([H | T], [RezSub | Rez]) :-
    is_list(H),
    !,
    sorteaza(H, RezSub),
    sorteaza_eterogen(T, Rez).

sorteaza_eterogen([H | T], [H | Rez]) :-
    \+ is_list(H),
    sorteaza_eterogen(T, Rez).