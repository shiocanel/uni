% Sa se scrie un predicat care transforma o lista intr-o multime, in
%  ordinea ultimei aparitii. Exemplu: [1,2,3,1,2] e transformat in [3,1,2]

apare(E, [E | T]) :- !.
apare(E, [_ | T]) :-
    apare(E, T).

multime_ultim([], []).
multime_ultim([H | T], Rez) :-
    apare(H, T), 
    !,
    multime_ultim(T, Rez).

multime_ultim([H | T], [H | Rez]) :-
    multime_ultim(T, Rez).


% cmmmdc(a, b) = a, daca b = 0
%                cmmdc(b, a mod b), daca b > 0


% cmmdc_lista(L) = 1. x, daca L = [x]
%                  2. cmmdc(l1, cmmdc_lista(l2...ln)), altfel



cmmdc(A, 0, A) :- !.
cmmdc(A, B, Rez) :-
    B > 0,
    D is A mod B,
    cmmdc(B, D, Rez).

cmmdc_lista([X], Rez) :-
    !,
    Rez is abs(X).

cmmdc_lista([H | T], Rez) :-
    cmmdc_lista(T, RezT),
    H_abs is abs(H),
    cmmdc(H_abs, RezT, Rez).