
minim([X], X).
minim([H | T], Min) :-
	minim(T, MinT),
	(H < MinT -> Min = H ; Min = MinT).

uneste([], L, L).
uneste([H | T], L, [H | Rez]) :-
	uneste(T, L, Rez).


inlocuieste([], _, _, []).
inlocuieste([H | T], Min, X, [H | Rez]) :-
	H =\= Min,
	!,
	inlocuieste(T, Min, X, Rez).

inlocuieste([H | T], Min, X, Rez) :-
	H =:= Min,
	!,
	inlocuieste(T, Min, X, RezT),
	uneste(X, RezT, Rez).



inlocuieste_main(L, X, Rez) :-
	minim(L, Min),
	inlocuieste(L, Min, X, Rez).
