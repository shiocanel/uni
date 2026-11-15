% 3.
% a. Să se scrie un predicat care transformă o listă într-o mulțime, în 
% ordinea primei apariții. Exemplu: [1, 2, 3, 1, 2] e transformat în [1, 2, 3].

% b. Să se scrie un predicat care descompune o listă de numere într-o listă 
% de forma [ lista-de-numere-pare , lista-de-numere-impare ] (deci o listă cu
%  două elemente care sunt la rândul lor 
% liste de întregi), și va întoarce și numărul elementelor pare și impare.


% modelul matematic

% multime_aux(L, V) = 1. multime_aux(l2...ln, V) daca l1 apartine V
%                     2. multime_aux(l2...ln, V + l1) daca l1 nu apartine V

% multime(L, Rez) = multime_aux(L, V, Rez)

multime_aux([], _, []).
multime_aux([H | T], V, Rez) :-
    member(H, V), !,
    multime_aux(T, V, Rez).

multime_aux([H | T], V, [H | Rez]) :-
    \+ member(H, V),
    multime_aux(T, [H | V], Rez).

multime(L, Rez) :- 
    multime_aux(L, [], Rez).

    
% b)

%                                             1. [], [[], []], 0, 0 daca L vid  
% descompune(L, [A, B], nr_pare, nr_impare) = 2. descompune(l2...ln, [l1 + A, B], nr_pare + 1, nr_impare) daca l1 par
%                                             3. descompune(l2...ln, [A, l2 + B], nr_pare, nr_impare + 1) daca l1 impar

descompune([], [[], []], 0, 0).
descompune([H | T], [[H | A], B], Nr_pare, Nr_impare) :-
    H mod 2 =:= 0, !,
    descompune(T, [A, B], Nr_pare1, Nr_impare),
    Nr_pare is Nr_pare1 + 1.

descompune([H | T], [A, [H | B]], Nr_pare, Nr_impare) :-
    H mod 2 =\= 0,
    descompune(T, [A, B], Nr_pare, Nr_impare1),
    Nr_impare is Nr_impare1 + 1.