
-- proceduri

USE Blog225;

CREATE PROCEDURE AdaugaCuvantCheie @nume VARCHAR(100)
AS
BEGIN
IF(EXISTS(SELECT * FROM CuvinteCheie WHERE nume=@nume))
	PRINT 'Acest cuvant cheie exista deja in tabel';
ELSE
	INSERT INTO CuvinteCheie (nume) VALUES (@nume);
END;


EXEC AdaugaCuvantCheie 'flori'
SELECT * FROM CuvinteCheie;

EXEC AdaugaCuvantCheie 'muzica';

