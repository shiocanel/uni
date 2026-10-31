--adaugare
INSERT INTO Utilizatori (nume, data_nasterii, email, parola) VALUES
('Antonio', '2000-10-1', 'anton@gmail.com', N'asdjnsdf'),
('Rares', '1988-2-1', 'rares@gmail.com', N'dfsjdsfnkdsjfds'),
('Alex', '2001-8-22', 'alex@gmail.com', N'fdsjfdsnj');

USE Blog225;

SELECT *
FROM Utilizatori;

SELECT nume, email
FROM Utilizatori;

SELECT nume as utilizator
FROM Utilizatori;

--actualizare
UPDATE Utilizatori
SET nume = 'Vasile'
WHERE nume = 'Alex'

--stergerea datelor
DELETE 
FROM Utilizatori
WHERE nume = 'Rares';


--exercitiu 1, 7 inregistrari
INSERT INTO Utilizatori(nume, data_nasterii, email, parola) VALUES
('Max', '2004-10-2', 'max@gmail.com', 'dfsdnkjdd'),
('Vasile', '2004-10-2', 'max@gmail.com', 'dfsdnkjdd'),
('Ion', '2004-10-9', 'max@gmail.com', 'dfsdnkjdd'),
('Giovanni', '2009-7-22', 'max@gmail.com', 'dfsdnkjdd'),
('Denis', '2010-4-11', 'max@gmail.com', 'dfsdnkjdd'),
('Luca', '2014-7-22', 'max@gmail.com', 'dfsdnkjdd'),
('Alexandra', '2009-10-2', 'max@gmail.com', 'dfsdnkjdd'),