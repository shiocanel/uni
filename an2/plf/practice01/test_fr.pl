minim([X], X).
minim([H | T], Min) :-
	minim(T, MinT),
	(H < MinT -> Min = H ; Min = MinT).

uneste([], L, L).
uneste([H | T], L, [H | Rez]) :-
	uneste(T, L, Rez).

inlocuieste_min_aux([], _, _, []).
inlocuieste_min_aux([H | T], X, Min, [H | Rez]) :-
	H =\= Min,
	!,
	inlocuieste_min_aux(T, X, Min, Rez).

inlocuieste_min_aux([H | T], X, Min, Rez) :-
	H =:= Min,
	!,
	inlocuieste_min_aux(T, X, Min, RezT),
	uneste(X, RezT, Rez).


inlocuieste_min(L, X, Rez) :-
	minim(L, Min),
	inlocuieste_min_aux(L, X, Min, Rez).




