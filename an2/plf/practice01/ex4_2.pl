% =========================================================================
% PROBLEMA 4.a: Interclasarea a două liste sortate fără păstrarea dublurilor
% =========================================================================

% interclaseaza(L1: list, L2: list, Rez: list)
% Model de flux: (i, i, o) - determinist
interclaseaza(L, [], L) :- !.
interclaseaza([], L, L) :- !.

% Cazul în care elementele sunt egale: păstrăm doar unul (H1) și avansăm în ambele
interclaseaza([H1 | T1], [H2 | T2], [H1 | Rez]) :-
    H1 =:= H2, !,
    interclaseaza(T1, T2, Rez).

% Cazul în care H1 < H2: punem H1 în rezultat
interclaseaza([H1 | T1], [H2 | T2], [H1 | Rez]) :-
    H1 < H2, !,
    interclaseaza(T1, [H2 | T2], Rez).

% Cazul în care H1 > H2: punem H2 în rezultat
interclaseaza([H1 | T1], [H2 | T2], [H2 | Rez]) :-
    H1 > H2,
    interclaseaza([H1 | T1], T2, Rez).


% =========================================================================
% PROBLEMA 4.b: Interclasarea globală a tuturor sublistelor dintr-o listă eterogenă
% =========================================================================

% interclaseaza_toate(L_eterogena: list, Rez: list)
% Model de flux: (i, o) - determinist

% Dacă am ajuns la capătul listei eterogene și nu mai avem subliste, rezultatul inițial al interclasării este []
interclaseaza_toate([], []).

% Cazul 1: Găsim o sublistă H -> o interclasez cu rezultatul obținut din restul listei
interclaseaza_toate([H | T], Rez) :-
    is_list(H), !,
    interclaseaza_toate(T, RezRest),
    interclaseaza(H, RezRest, Rez).

% Cazul 2: Găsim un număr simplu (nu e listă) -> îl ignorăm și trecem mai departe
interclaseaza_toate([H | T], Rez) :-
    \+ is_list(H),
    interclaseaza_toate(T, Rez).

sterge_duplicate([], []).
sterge_duplicate([X], [X]).
sterge_duplicate([H, H | T], Rez) :-
    !,                  % Dacă H se repetă imediat (fiind ordonată lista), îl sărim pe primul
    sterge_duplicate([H | T], Rez).
sterge_duplicate([H1, H2 | T], [H1 | Rez]) :-
    H1 \= H2,
    sterge_duplicate([H2 | T], Rez).

% Interclasare globală finală + curățare duplicate
interclaseaza_toate_curat(L_eterogena, RezFin) :-
    interclaseaza_toate(L_eterogena, RezBrut),
    sterge_duplicate(RezBrut, RezFin).