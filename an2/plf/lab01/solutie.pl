% a)

%                   1. adevarat, daca L = []
% par_elemente(L) = 2. par_elemente(T), daca L = [x1, x2 | T]
%                   3. fals, daca  L = [x]
% 


par_elemente([]). 
par_elemente([_, _ | T]) :-
    par_elemente(T).



% b)

% 
%               1. x, daca L = [x]
% minim(L) =    2. min(x, minim(T)), daca L = [x | T]
% 

% 
%                       1. [], daca L = []
% elim_prim(v, L) =     2. T, daca L = [v | T]
%                       3. [x, elim_prim(v, T)] 

%       
% elim_minim(L) = elim_prim(minim(L), L)  
% 


minim([X], X).
minim([X|T], M) :-
    minim(T, MT),
    (X < MT -> M = X ; M = MT).

elim_prim(_, [], []).
elim_prim(X, [X|T], T) :- !.
elim_prim(X, [H|T], [H|T1]) :-
    X \= H,
    elim_prim(X, T, T1).

elim_minim(L, Rez) :-
    minim(L, Min),
    elim_prim(Min, L, Rez).
