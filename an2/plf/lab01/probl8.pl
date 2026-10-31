% ==========================================
% a. Testează dacă o listă este mulțime (nu conține duplicate)
% ==========================================
multime([]).
multime([H|T]) :-
    \+ member(H, T),   % Verifică ca H să NU fie în restul listei T
    multime(T).        % Continuă verificarea pentru restul listei

% ==========================================
% b. Elimină primele 3 apariții ale unui element (sau câte sunt, dacă sunt mai puțin de 3)
% ==========================================

% Predicatul principal care pornește numărătoarea de la 3
elim_3(X, Lista, Rezultat) :-
    elim_n(X, 3, Lista, Rezultat).

% Cazul 1: Dacă am ajuns la 0 eliminări rămase, oprim ștergerea și lăsăm restul listei intact
elim_n(_, 0, Lista, Lista).

% Cazul 2: Dacă lista s-a terminat, oprim recursivitatea
elim_n(_, _, [], []).

% Cazul 3: Găsim elementul X și mai avem de eliminat (N > 0)
% Îl sărim (nu îl punem în rezultat) și scădem contorul N cu 1 (N1 is N - 1)
elim_n(X, N, [X|T], Rezultat) :-
    N > 0,
    N1 is N - 1,
    elim_n(X, N1, T, Rezultat).

% Cazul 4: Elementul curent H NU este X. Îl păstrăm în rezultat și mergem mai departe.
elim_n(X, N, [H|T], [H|Rezultat]) :-
    X \= H,
    elim_n(X, N, T, Rezultat).