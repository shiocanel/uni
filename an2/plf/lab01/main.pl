male(harry).
female(liz).
parent(phill, chas).
parent(liz, chas).
parent(liz, mary).

parent(chas, harry).
parent(chas, wills).
parent(chas, anabelle).

grandmother(GM, C):-
    mother(GM, P),
    parent(P, C).

mother(M, C):-
    female(M),
    parent(M, C).

siblings(F1, F2):-
    parent(P, F1),
    parent(P, F2).

siblings(F1, F2, F3):-
    parent(P, F1),
    parent(P, F2),
    parent(P, F3).

aunt(A, N):-
    female(A),
    siblings(A, F),
    parent(F, N).

curva(X, Y):-
    female(X),
    siblings(X, Y).