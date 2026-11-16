%  Sa se scrie un predicat care testeaza daca o lista este multime.

%  Sa se scrie un predicat care elimina primele 3 aparitii ale unui element
%  intr-o lista. Daca elementul apare mai putin de 3 ori, se va elimina de
%  cate ori apare.

apare(E, [E | T]) :- !.
apare(E, [_ | T]) :-
    apare(E, T).

este_multime([]).
este_multime([H | T]) :- 
    \+ apare(H, T),
    este_multime(T).


%                     1. L, daca K = 0
% elimina_k(E, L, K) =2. [], daca L = [] si K > 0
%                     3. elimina_k(E, l2...ln, K - 1), daca l1 == E si K > 0
%                     4. elimina_k(E, l2...ln, K), daca l1 != E si K > 0

% elimina_3(E, L) = elimina_k(E, L, 3)


elimina_k(_, L, 0, L) :- !.
elimina_k(_, [], _, []) :- !.

elimina_k(E, [E | T], K, Rez) :-
    K > 0,
    !,
    K1 is K - 1,
    elimina_k(E, T, K1, Rez).

elimina_k(E, [H | T], K, [H | Rez]) :-
    H \= E,
    elimina_k(E, T, K, Rez).


elimina_3(E, L, Rez) :-
    elimina_k(E, L, 3, Rez).