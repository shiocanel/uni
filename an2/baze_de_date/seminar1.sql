--BAZA de date caca
CREATE DATABASE Blog225;
GO 

--conectare la baza
USE Blog225;

CREATE TABLE Utilizatori
(cod_u INT PRIMARY KEY IDENTITY(1,1),
nume VARCHAR(100) NOT NULL,
data_nasterii DATE,
email VARCHAR(100) UNIQUE,
parola NVARCHAR(200)
);

CREATE TABLE Articole
(cod_a INT PRIMARY KEY IDENTITY,
titlu VARCHAR(100) NOT NULL,
continut VARCHAR(MAX),
data_publicarii DATETIME,
cod_u INT FOREIGN KEY REFERENCES Utilizatori(cod_u)
);

CREATE TABLE Comentarii
(cod_c INT PRIMARY KEY IDENTITY,
continut NVARCHAR(500),
data_publicarii DATETIME,
cod_u INT FOREIGN KEY REFERENCES Utilizatori(cod_u),
cod_a INT FOREIGN KEY REFERENCES Articole(cod_a)
);

CREATE TABLE CuvinteCheie
(cod_cc INT PRIMARY KEY IDENTITY,
nume VARCHAR(100) NOT NULL
);

CREATE TABLE ArticoleCuvinteCheie
(cod_a INT FOREIGN KEY REFERENCES Articole(cod_a),
cod_cc INT FOREIGN KEY REFERENCES CuvinteCheie(cod_cc)
CONSTRAINT pk_ArticoleCuvinteCheie
PRIMARY KEY (cod_a, cod_cc)
);