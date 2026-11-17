USE Blog225;
GO

DELETE FROM ArticoleCuvinteCheie;
DELETE FROM Comentarii;
DELETE FROM Articole;
DELETE FROM CuvinteCheie;
DELETE FROM Utilizatori;
GO

DBCC CHECKIDENT ('Utilizatori', RESEED, 0);
DBCC CHECKIDENT ('Articole', RESEED, 0);
DBCC CHECKIDENT ('Comentarii', RESEED, 0);
DBCC CHECKIDENT ('CuvinteCheie', RESEED, 0);
GO

INSERT INTO Utilizatori (nume, data_nasterii, email, parola) VALUES
('Ion Popescu', '1990-05-12', 'ion.popescu@email.com', 'Parola123!'),
('Maria Ionescu', '1985-10-22', 'maria.ionescu@email.com', 'Securizat#99'),
('Andrei Georgescu', '1995-03-01', 'andrei.georgescu@email.com', 'ParolaAndrei2026');

INSERT INTO CuvinteCheie (nume) VALUES
('Tehnologie'),
('Programare'),
('Stil de viață'),
('Călătorii'),
('Dezvoltare personală');

INSERT INTO Articole (titlu, continut, data_publicarii, cod_u) VALUES
('Introducere în SQL Server', 'Acest articol prezintă conceptele de bază pentru utilizarea SQL Server.', '2026-01-15 10:30:00', 1),
('Destinații de vacanță în 2026', 'Descoperă cele mai frumoase locuri pe care le poți vizita anul acesta.', '2026-02-10 14:00:00', 2),
('Sfaturi pentru programatori începători', 'Cum să începi o carieră în IT și ce limbaje să înveți.', '2026-03-01 09:15:00', 3);

INSERT INTO Comentarii (continut, data_publicarii, cod_u, cod_a) VALUES
('Foarte util articolul, mulțumesc!', '2026-01-15 11:00:00', 2, 1),
('Aștept partea a doua despre optimizare.', '2026-01-16 08:45:00', 3, 1),
('Foarte frumos, am pus destinația pe listă!', '2026-02-11 16:20:00', 1, 2);

INSERT INTO ArticoleCuvinteCheie (cod_a, cod_cc) VALUES
(1, 1),
(1, 2),
(2, 4),
(3, 1),
(3, 2),
(3, 5);

SELECT * FROM Utilizatori;
SELECT * FROM CuvinteCheie;
SELECT * FROM Articole;
SELECT * FROM Comentarii


