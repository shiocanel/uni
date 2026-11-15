% 4.a: Să se scrie un predicat care substituie într-o listă un element printr-o altă listă.  
% 4.b: Să se elimine elementul de pe poziția a n-a a unei liste liniare.   

% substituie(L: List, e: Element, X: List, Rez: List)



% substituie(L, e, X) = 1. x1...xn  + substituie(l2...lm, e, X) daca l1 = e
%                       2. substituie(l2...lm, e, X)  altfel
%                       3. [] daca L vida


concatenare([], L, L).
concatenare([H | T], L2, [H | L3]) :-
    concatenare(T, L2, L3).

substituie([], _, _, []).
substituie([E | T], E, X, Rez) :-
    !, 
    substituie(T, E, X, RezSub),
    concatenare(X, RezSub, Rez).

substituie([H | T], E, X, [H | Rez]) :-
    H \= E,
    substituie(T, E, X, Rez).



% elim_poz(L, N) = 1. l1 + elim_poz(l2...ln, N - 1), daca N > 1
%                  2. l2...ln, daca N = 1 


elim_poz([_ | T], 1, T) :- !.
elim_poz([H | T], N, [H | Rez]) :-
    N > 1,
    N1 is N - 1,
    elim_poz(T, N1, Rez).

    
