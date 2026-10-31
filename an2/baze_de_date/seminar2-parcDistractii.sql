INSERT INTO CategoriiVizitatori(nume) VALUES
(N'Copii (sub 12 ani)'),
(N'Adolescenti (12-18 ani)'),
(N'Adulti (18-60 ani)'),
(N'Seniori (peste 60 ani)'),
(N'VIP'),
(N'Grupuri scolare'),
(N'Persoane cu dizabilitati');

INSERT INTO Sectiuni(nume, descriere) VALUES
(N'Blah Blah Blah', N'Zona dedicata pentru yapp'),
(N'Aventura', N'Zona cu roller-coastere'),
(N'Parcul Acvatic', N'Piscine'),
(N'Spooky scary', N'Case bantuite skibbidi sends shivvesrs down my gyat'),
(N'Dinozauri', N'Expozitii tematice'),
(N'Zona SF', N'Simulatoare de zbor'),
(N'Targul', N'Carusele clasice, standuri cu dulciuri');


INSERT INTO Vizitatori (nume, email, cod_cv) VALUES 
(N'Popescu Andrei', N'andrei.popescu@email.com', 1),
(N'Ionescu Maria', N'maria.ionescu@email.com', 2),
(N'Georgescu Mihai', N'mihai.georgescu@email.com', 3),
(N'Dumitrescu Elena', N'elena.dumitrescu@email.com', 4),
(N'Constantin Radu', N'radu.constantin@email.com', 5),
(N'Stoica Ana', N'ana.stoica@email.com', 6),
(N'Vasile Ion', N'ion.vasile@email.com', 7);

INSERT INTO Atractii (nume, descriere, varsta_minima_recomandata, cod_s) VALUES 
(N'Caruselul Magic', N'magic', 3, 1),
(N'Dragonul', N'Denery Targaryan si Ion Zapada', 12, 2),
(N'Cascada', N'cu barca daca vrei', 8, 3),
(N'Labirintul spookios', N'spookyy', 10, 4),
(N'T-Rex', N'uuuuuu', 6, 5),
(N'Zbor', N'zbor spatial cu naveta', 14, 6),
(N'Roata', N'roataaaa', 0, 7);

INSERT INTO NoteAtractii (cod_v, cod_a, nota) VALUES 
(1, 1, 9.5),
(2, 2, 8.0),
(3, 3, 7.5),
(4, 4, 10.0),
(5, 5, 8.5),
(6, 6, 9.0),
(7, 7, 6.5);

-- exercitiu 2

UPDATE Atractii
SET descriere = 'Magic cel mai wow'
WHERE cod_a = 1;

UPDATE CategoriiVizitatori
SET nume = 'Premium'
WHERE cod_cv = 5;

UPDATE NoteAtractii
SET nota = 5.0
WHERE cod_v = 1 AND cod_a = 1;

UPDATE Sectiuni
SET nume = 'Blah'
WHERE nume = 'Blah Blah Blah';

UPDATE Vizitatori
SET cod_cv = 2
WHERE email = 'andrei.popescu@email.com';

-- exercitiu 3

DELETE 
FROM NoteAtractii
WHERE nota BETWEEN 9.0 AND 10;

DELETE 
FROM Atractii
WHERE varsta_minima_recomandata BETWEEN 0 AND 3;

--EXERCITIU 4

SELECT *
FROM CategoriiVizitatori
WHERE nume = 'Seniori (peste 60 ani)' OR nume = 'Copii (sub 12 ani)';

SELECT *
FROM Sectiuni
WHERE descriere LIKE 'C%';

SELECT *
FROM Sectiuni
WHERE nume LIKE  '%h' and nume LIKE '__%';

-- EXERCITIU 5

SELECT *
FROM Vizitatori
WHERE cod_v NOT IN (
	SELECT cod_v
	FROM NoteAtractii
);

SELECT Vizitatori.nume, NoteAtractii.nota, Atractii.nume
FROM Vizitatori
WHERE Vizitatori.cod_v IN (
	SELECT NoteAtractii.cod_a 
	FROM NoteAtractii
	WHERE NoteAtractii.cod_a IN (
		SELECT Atractii.cod_a
		FROM Atractii
	)
);


SELECT *
FROM Atractii;

SELECT *
FROM CategoriiVizitatori;

SELECT *
FROM NoteAtractii;

SELECT *
FROM Sectiuni;

SELECT *
FROM Vizitatori;
