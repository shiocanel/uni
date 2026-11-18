
divizori(E, D, []) :-
	D + D > E,
	!.

divizori(E, D, [D | Rez]) :-
	E mod D =:= 0,
	!,
	DNou is D + 1,
	divizori(E, DNou, Rez).

divizori(E, D, Rez) :-
	E mod D =\= 0,
	DNou is D + 1,          % <--- Corectat: DNou cu litera mare!
	divizori(E, DNou, Rez).

divizori_main(E, Rez) :-
	divizori(E, 1, Rez).

adauga_divizori([], []).
adauga_divizori([H | T], [RezD | Rez]) :-
	divizori_main(H, RezD),
	adauga_divizori(T, Rez).
