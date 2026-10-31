CREATE DATABASE ParcDistractii;
GO

USE ParcDistractii;
GO

CREATE TABLE CategoriiVizitatori (
    cod_cv INT IDENTITY(1,1),
    nume NVARCHAR(100) NOT NULL,
    CONSTRAINT pk_CategoriiVizitatori PRIMARY KEY (cod_cv)
);
GO

CREATE TABLE Sectiuni (
    cod_s INT IDENTITY(1,1),
    nume NVARCHAR(100) NOT NULL,
    descriere NVARCHAR(MAX),
    CONSTRAINT pk_Sectiuni PRIMARY KEY (cod_s)
);
GO

CREATE TABLE Vizitatori (
    cod_v INT IDENTITY(1,1),
    nume NVARCHAR(100) NOT NULL,
    email NVARCHAR(150) NOT NULL,
    cod_cv INT NOT NULL,
    CONSTRAINT pk_Vizitatori PRIMARY KEY (cod_v),
    CONSTRAINT fk_Vizitatori_Categorii FOREIGN KEY (cod_cv) 
        REFERENCES CategoriiVizitatori(cod_cv) 
        ON UPDATE CASCADE 
        ON DELETE CASCADE
);
GO

CREATE TABLE Atractii (
    cod_a INT IDENTITY(1,1),
    nume NVARCHAR(100) NOT NULL,
    descriere NVARCHAR(MAX),
    varsta_minima_recomandata INT,
    cod_s INT NOT NULL,
    CONSTRAINT pk_Atractii PRIMARY KEY (cod_a),
    CONSTRAINT fk_Atractii_Sectiuni FOREIGN KEY (cod_s) 
        REFERENCES Sectiuni(cod_s) 
        ON UPDATE CASCADE 
        ON DELETE CASCADE
);
GO

CREATE TABLE NoteAtractii (
    cod_v INT,
    cod_a INT,
    nota DECIMAL(3,1) NOT NULL,
    CONSTRAINT pk_NoteAtractii PRIMARY KEY (cod_v, cod_a),
    CONSTRAINT fk_Note_Vizitatori FOREIGN KEY (cod_v) 
        REFERENCES Vizitatori(cod_v) 
        ON UPDATE CASCADE 
        ON DELETE CASCADE,
    CONSTRAINT fk_Note_Atractii FOREIGN KEY (cod_a) 
        REFERENCES Atractii(cod_a) 
        ON UPDATE CASCADE 
        ON DELETE CASCADE
);
GO

ALTER TABLE Vizitatori
ADD CONSTRAINT uq_Vizitatori_email UNIQUE (email);
GO

ALTER TABLE NoteAtractii
ADD CONSTRAINT ck_NoteAtractii_valoare CHECK (nota >= 1 AND nota <= 10);
GO