e_prim(2) :-
	!.
e_prim(N) :-
	N > 2,
	nu_are_divizori(N, 2).

nu_are_divizori(N, D) :-
	D * D > N,
	!.

nu_are_divizori(N, D) :-
	N mod D =\= 0,
	DNou is D + 1,
	nu_are_divizori(N, DNou).

duplica_prime([], []).
duplica_prime([H | T], [H | Rez]) :-
	\+ e_prim(H),
	duplica_prime(T, Rez).

duplica_prime([H | T], [H, H | Rez]) :-
	e_prim(H),
	!,
	duplica_prime(T, Rez).


