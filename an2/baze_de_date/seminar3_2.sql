USE ParcDistractii;


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

-- ex1

CREATE PROCEDURE InsereazaSectiune @nume NVARCHAR(10), @descriere NVARCHAR(MAX)	
AS
BEGIN
INSERT INTO Sectiuni VALUES
(@nume, @descriere);

END;

EXEC InsereazaSectiune 'vasile', 'cel mai bun din univers';



-- ex2
CREATE PROCEDURE ActualizeazaVizitatorEmail @cod_v INT, @email NVARCHAR(150)
AS 
BEGIN

UPDATE Vizitatori
SET email=@email
WHERE cod_v=@cod_v;

END;

EXEC ActualizeazaVizitatorEmail 1, 'vasile@grigorescu.com';

--ex3

CREATE PROCEDURE GasesteUtilizatoriCuNote
AS 
BEGIN

SELECT v.nume, v.email, COUNT(v.cod_v) as 'Numarul De Note'
FROM Vizitatori v
JOIN NoteAtractii nt ON nt.cod_v = v.cod_v
GROUP BY v.nume, v.email;

END;


EXEC GasesteUtilizatoriCuNote;


--ex4
CREATE PROCEDURE InsereazaCategorie @nume NVARCHAR(100)
AS
BEGIN

	IF((SELECT nume FROM CategoriiVizitatori WHERE nume = @nume) IS NULL)
		PRINT 'exista deja!!';
	ELSE
		INSERT INTO CategoriiVizitatori VALUES
		(@nume);


END;

EXEC InsereazaCategorie 'mata';