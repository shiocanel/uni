%  a se scrie un predicat care intoarce diferenta a doua multimi.
%  b. Sa se scrie un predicat care adauga intr-o lista dupa fiecare element par
%  valoarea 1.


% a)

diferenta([], _, []).
diferenta([H|T], L2, Rez) :- 
    member(H, L2), !,
    diferenta(T, L2, Rez).

diferenta([H|T], L2, [H|Rez]) :-
    \+ member(H, L2), 
    diferenta(T, L2, Rez).



% b)

adauga_unu_par([], []).
adauga_unu_par([H|T], [H, 1 | Rez]) :-
    H mod 2 =:= 0, !,
    adauga_unu_par(T, Rez).

adauga_unu_par([H|T], [H|Rez]) :-
    adauga_unu_par(T, Rez).