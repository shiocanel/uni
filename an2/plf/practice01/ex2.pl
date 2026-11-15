% a. Să se scrie un predicat care determină cel mai mic multiplu comun al elementelor unei liste formate din numere întregi.
% b. Să se scrie un predicat care adaugă după 1-ul, al 2-lea, al 4-lea, al 8-lea... element al unei liste o valoare $v$ dată.


% cmmmc_lista(L: lista, Rez: integer) -> (i, o)
% determinist

% modelul matematic
% cmmmc = abs(a * b) / cmmdc(a, b)


% cmmmc_lista(L) = 1. x daca L = [x]
            %      2. cmmmc(x, cmmmc_lista(T)) daca L = [x | T]

    
cmmdc(A, 0, A) :- !. % si ne oprim
cmmdc(A, B, Rez) :-
    B > 0,
    R is A mod B,
    cmmdc(B, R, Rez).

cmmmc(0, 0, 0) :- !.
cmmmc(A, B, Rez) :-
    A \= 0,
    B \= 0,
    cmmdc(A, B, D),
    Rez is abs(A * B) div D.

cmmmc_lista([X], X).
cmmmc_lista([H|T], Rez) :-
    cmmmc_lista(T, RezT),
    cmmmc(H, RezT, Rez).




% b)

%  adauga(L, v, p) = 1. l1 + v + adauga(l2...ln, v, p + 1) daca putere(p)
%                    2. l1 + adauga(l2...ln v, p + 1) altfel


% putere(p) = 1. True daca p putere de 2
            % 2. False altfel

% adauga_main(L, v, Rez) = adauga(L, v, p, Rez)


este_putere(1) :- !.
este_putere(N) :- 
    N > 1,
    0 is N mod 2,
    N1 is N div 2,
    este_putere(N1).

adauga_aux([], _, _, []).
adauga_aux([H|T], V, Pos, [H, V | Rez]) :-
    este_putere(Pos), !, % ! inseamna ca mergi pe mathcul asta ca e important
    Pos1 is Pos + 1,
    adauga_aux(T, V, Pos1, Rez).

adauga_aux([H | T], V, Pos, [H | Rez]) :-
    Pos1 is Pos + 1,
    adauga_aux(T, V, Pos1, Rez).

adauga(L, V, Rez) :- 
    adauga_aux(L, V, 1, Rez).

