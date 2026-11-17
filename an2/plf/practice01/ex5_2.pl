% Sa se determine pozitiile elementului maxim dintr-o lista liniara. De ex:
%  poz([10,14,12,13,14], L) va produce L = [2,5].

% poz_max(L, Idx, Max) = 1. Idx + poz_max(l2...ln, Idx + 1, Max), daca l1 == Max
%                   2. poz_max(l2...ln, Idx + 1, Max), altfel
%                   3. [], daca L vida

% poz_max_main(L) = poz_max(L, 1, Max)


% poz_max_main(L: List, Rez: List) -> (i, o) determinist
% poz_max(L: List, Idx: Element, Max: Element, Rez: List) -> (i, i, i, o) determinist

maxim([X], X).
maxim([H | T], Max) :-
    maxim(T, MaxT),
    (H > MaxT -> Max = H ; Max = MaxT).

poz_max([], _, _, []).
poz_max([H | T], Idx, Max, [Idx | Rez]) :-
    H =:= Max,
    !,
    IdxNou is Idx + 1,
    poz_max(T, IdxNou, Max, Rez).

poz_max([_ | T], Idx, Max, Rez) :-
    IdxNou is Idx + 1,
    poz_max(T, IdxNou, Max, Rez).

poz_max_main([], []).
poz_max_main(L, Rez) :-
    maxim(L, Max),
    poz_max(L, 1, Max, Rez).


% Se da o lista eterogena, formata din numere intregi si liste de numere
% intregi. Sa se inlocuiasca fiecare sublista cu pozitiile elementului maxim
% din sublista respectiva. De ex:
% [1, [2, 3], [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] =>
% [1, [2], [1, 3], 3, 6, [2], 5, [1, 2, 3], 7]


% inlocuieste_cu_maxim(L) = 1. poz_max_main(l1) + inlocuieste_cu_maxim(l2...ln), daca is_list(l1)
%                           2. inlocuieste_cu_maxim(l2...ln), altfel


% inlocuieste_cu_maxim(L: List, Rez: List) -> (i, o) determinist


inlocuieste_cu_maxim([], []).
inlocuieste_cu_maxim([H | T], [RezH | Rez]) :-
    is_list(H),
    !,
    poz_max_main(H, RezH),
    inlocuieste_cu_maxim(T, Rez).

inlocuieste_cu_maxim([H | T], [H | Rez]) :-
    \+ is_list(H),
    inlocuieste_cu_maxim(T, Rez).