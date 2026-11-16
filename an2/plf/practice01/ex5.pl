% a. Să se scrie un predicat care șterge toate aparițiile unui anumit atom dintr-o listă.
% b. Definiți un predicat care, dintr-o listă de atomi, produce o listă de perechi [atom, n],
%  unde atom apare în lista inițială de $n$ ori. De ex: numar([1, 2, 1, 2, 1, 3, 1], X) va produce X = [[1, 4], [2, 2], [3, 1]].


% sterge(L, e) = 1. [] daca L vida
%                2. l1 + sterge(l2...ln, e) daca l1 != e
%                3. sterge(l2...ln, e) daca l1 = e

% sterge(E: element, L: list, Rez: list) -> (i, i, o) (determinist).

sterge([], _, []).
sterge([H | T], E, [H | Rez]) :-
    !,
    sterge(T, E, Rez).

sterge([H | T], E, Rez) :-
    H \= E,
    sterge(T, E, Rez).





% numar(L: list, Rez: list of lists) -> (i, o) (determinist).

% numar(L, Rez) = numar(sterge_element(l2...ln, l1), numara_aparitii(l1, L))

numara_aparitii(_, [], 0).
numara_aparitii(H, [H | T], C) :-
    numara_aparitii(H, T, C1),
    C is C1 + 1.

numara_aparitii(E, [H | T], C) :-
    E \= H,
    numara_aparitii(E, T, C).

sterge_element(_, [], []).
sterge_element(H, [H | T], Rez) :-
    !,
    sterge_element(H, T, Rez).

sterge_element(E, [H | T], [H | Rez]) :-
    E \= H,
    sterge_element(E, T, Rez).

numar([], []).
numar([H | T], [[H | C] | Rez]) :-
    numara_aparitii(H, [H | T], C),
    sterge_element(H, [H | T], ListaNoua),
    numar(ListaNoua, Rez).