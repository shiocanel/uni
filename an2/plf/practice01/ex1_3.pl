% Se dau N puncte în plan (prin coordonatele lor). Se cere să se determine
% toate submulțimile de puncte coliniare.

%                   1. [], daca L = [], si K = 0
% combinari(L, K) = 2. l1 + combinari(l2...ln, K - 1), daca K > 0 odata il pun
%                   3. combinari(l2...ln, K), daca K > 0 odata nu



%    coliniare(P1, P2, P3) = true, daca X1*(Y2 - Y3) + X2*(Y3 - Y1) + X3*(Y1 - Y2) = 0
%                            false, altfel


% combinari(L: list, K: integer, Rez: list) -> (i, i, o) nedeterminist
% coliniare(P1: list, P2: list, P3: list) -> (i, i, i) determinist
% puncte_coliniare(L: list, Rez: list) -> (i, o) nedeterminist

combinari(_, 0, []).
combinari([H | T], K, [H | Rez]) :-
    K > 0,
    K1 is K - 1,
    combinari(T, K1, Rez).

combinari([_ | T], K, Rez) :-
    K > 0,
    combinari(T, K, Rez).

coliniare([X1, Y1], [X2, Y2], [X3, Y3]) :-
    Aria is X1 * (Y2 - Y3) + X2 * (Y3 - Y1) + X3 * (Y1 - Y2),
    Aria =:= 0.

verifica_coliniare([P1, P2, P3]) :-
    coliniare(P1, P2, P3), !.

verifica_coliniare([P1, P2, P3 | T]) :-
    coliniare(P1, P2, P3),
    verifica_coliniare([P2, P3 | T]).

submultime_coliniara(ListaPuncte, Rez) :-
    lungime(ListaPuncte, N),
    N >= 3,
    between(3, N, K),
    combinari(ListaPuncte, K, Rez),
    verifica_coliniare(Rez).

lungime([], 0).
lungime([_ | T], L) :-
    lungime(T, L1),
    L is L1 + 1.


% submultime_coliniara([[1, 1], [2, 1], [3, 1], [5, 5]], Rez).
% [3] 14 ?- submultime_coliniara([[1, 1], [2, 1], [3, 1], [5, 5], [4, 1]], Rez).
% Rez = [[1, 1], [2, 1], [3, 1]] ;
% Rez = [[1, 1], [2, 1], [4, 1]] .

% [3] 15 ?- 