%succesor(L) = inverseaza(aduna(inverseaza(L), 1, 0))
%
%aduna(L, E, Tr) = l1 + E + Tr mod 10 + aduna(l2...ln, E, S // 10)
%

inverseaza_aux([], Acc, Acc).
inverseaza_aux([H | T], Acc, Rez) :-
	inverseaza_aux(T, [H | Acc], Rez).

inverseaza(L, Rez) :-
	inverseaza_aux(L, [], Rez).

aduna([], 0, []).
aduna([], Tr, [Tr]).

aduna([H | T], Tr, [Hnou | Rez]) :-
	Sum is H + Tr,
	Hnou is Sum mod 10,
	TrNou is Sum // 10,
	aduna(T, TrNou, Rez).

succesor(L, Rez) :-
	inverseaza(L, Inv1),
	aduna(Inv1, 1, Rez2),
	inverseaza(Rez2, Rez).



succesor_lista([], []).
succesor_lista([H | T], [RezH | Rez]) :-
	is_list(H),
	!,
	succesor(H, RezH),
	succesor_lista(T, Rez).


succesor_lista([H | T], [H | Rez]) :-
	\+ is_list(H),
	succesor_lista(T, Rez).
