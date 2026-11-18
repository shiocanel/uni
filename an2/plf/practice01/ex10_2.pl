este_putere(1).
este_putere(X) :-
	0 =:= X mod 2,
	XNou is X // 2,
	este_putere(XNou).


adauga([], _, _, []).
adauga([H | T], E, Idx, [H | Rez]) :-
	IdxNou is Idx + 1,
	\+ este_putere(IdxNou),
	!,
	adauga(T, E, IdxNou, Rez).

adauga([H | T], E, Idx, [H, E | Rez]) :-
	IdxNou is Idx + 1,
	este_putere(IdxNou),
	adauga(T, E, IdxNou, Rez).


adauga_eterogen([], _, []).
adauga_eterogen([H | T], E, [RezH | Rez]) :-
	is_list(H),
	!,
	adauga(H, E, 1, RezH),
	adauga_eterogen(T, E, Rez).

adauga_eterogen([H | T], _, [H | Rez]) :-
	\+ is_list(H),
	adauga_eterogen(T, H, Rez).


