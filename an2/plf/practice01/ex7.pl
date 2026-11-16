% Sa se scrie un predicat care intoarce reuniunea a doua multimi.


% Sa se scrie un predicat care, primind o lista, intoarce multimea
% tuturor perechilor din lista. De ex, cu [a, b, c, d] va produce
% [[a, b], [a, c], [a, d], [b, c], [b, d], [c, d]].


% reuniune(L1, L2) = sterge_duplicate(uneste(L1, L2))


% sterge_duplicate(L) = 1. [], daca L vida
%                       2. l1 + sterge_duplicate(sterge(l2...ln, l1))

% sterge(L, E) = 1. [], daca L vida
%                2. l1 + sterge(l2...ln), daca l1 != E
%                3. sterge(l2...ln), daca l1 == E

% uneste(A, B) = 1. B, daca A vida
%                2. a1 + uneste(a2...an, B) altfel


% reuniune(L1: List, L2: List, Rez: List) -> (i, i, o) determinist


uneste([], L2, L2).
uneste([H | T], L2, [H | Rez]) :-
    uneste(T, L2, Rez).

sterge([], _, []).
sterge([E | T], E, Rez) :-
    !,
    sterge(T, E, Rez).

sterge([H | T], E, [H | Rez]) :-
    H \= E,
    sterge(T, E, Rez).

sterge_duplicate([], []).
sterge_duplicate([H | T], [H | Rez]) :-
    sterge(T, H, ListaNou),
    sterge_duplicate(ListaNou, Rez).

reuniune(L1, L2, Rez) :-
    uneste(L1, L2, ListaUnita),
    sterge_duplicate(ListaUnita, Rez).



%              1. [], daca L vida
% multime(L) = 2. uneste(perechi(l1, l2...ln) + multime(l2...ln))


% perechi(E, L) = 1. [] daca L vida
%                 2. [E, l1] + perechi(E, l2...ln), altfel

% multime(L: List, Rez: List) -> (i, o) determinist


perechi(_, [], []).
perechi(E, [H | T], [[E, H] | Rez]) :-
    perechi(E, T, Rez).


multime([], []).
multime([H | T], Rez) :-
    perechi(H, T, L1),
    multime(T, L2),
    uneste(L1, L2, Rez).