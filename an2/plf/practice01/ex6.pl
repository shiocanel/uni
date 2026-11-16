% 6.
% a. Să se scrie un predicat care elimină dintr-o listă toate elementele care se repetă (ex: [1, 2, 1, 4, 1, 3, 4] devine [2, 3]).
% b. Să se elimine toate aparițiile elementului maxim dintr-o listă de numere întregi.


% elimina(L) = 1. l1 + elimina(l2...ln) daca nr_aparitii(L, l1) = 1
%              2. elimina(l2...ln) daca nr_aparitii(L, l1) > 1
%              3. [], daca L vida

% elimina(L: List, Rez: List) -> (i, o) (determinist) 

% nr_aparitii(L, E) = 1. 0 daca L vida
%                     2. 1 + nr_aparitii(l2...ln, E), daca l1 = E
%                     3. nr_aparitii(l2...ln, E), daca l1 != E


nr_aparitii([], _, 0).
nr_aparitii([E | T], E, Cnt) :-
    !,
    nr_aparitii(T, E, Cnt1),
    Cnt is Cnt1 + 1.

nr_aparitii([H | T], E, Cnt) :-
    H \= E,
    nr_aparitii(T, E, Cnt).

elimina([], []).
elimina([H | T], [H | Rez]) :-
    nr_aparitii([H | T], H, 1),
    !,
    elimina(T, Rez).
    
elimina([H | T], Rez) :-
    nr_aparitii([H | T], H, C),
    C > 1,
    elimina(T, Rez).




% elim_max(L) = 1. l1 + elim_max(l2...ln), daca l1 != max(L)
%               2. elim_max(l2...ln), daca l1 = max(L)
%               3. [], daca L vida


% maxim(L) = 1. x, daca L = [x]
%            2. maxim(l2...ln), daca l1 < maxim(l2...ln)
%            3. l1, altfel



maxim([X], X).
maxim([H | T], Max) :-
    maxim(T, MaxRest),
    (H > MaxRest -> Max = H ; Max = MaxRest).


sterge_tot(_, [], []).
sterge_tot(E, [E | T], Rez) :-
    !,
    sterge_tot(E, T, Rez).

sterge_tot(E, [H | T], [H | Rez]) :-
    E \= H,
    sterge_tot(E, T, Rez).

elim_max([], []).
elim_max(L Rez) :-
    maxim(L, Max),
    sterge_tot(Max, L, Rez).