
-- ============================================================================
PRINT '--- TRANSFORMER 1: 1:N to N:1 (Branches & Employees) ---';

-- Adăugăm EmployeeID în Branches (făcând Branch să depindă de un Employee principal)
ALTER TABLE Branches ADD EmployeeID INT NULL;
GO

-- Setăm un angajat pentru fiecare sucursală (luăm primul angajat din sucursală)
UPDATE b
SET b.EmployeeID = e.EmployeeID
FROM Branches b
JOIN Employees e ON b.BranchID = e.BranchID;
GO

-- Ștergem vechea cheie străină din Employees și coloana BranchID
ALTER TABLE Employees DROP CONSTRAINT FK_Employees_Branches;
ALTER TABLE Employees DROP COLUMN BranchID;
GO

-- Adăugăm noua cheie străină în Branches (N sucursale pot aparține unui angajat manager/coordonator sau invers, transformând sensul N:1)
ALTER TABLE Branches ADD CONSTRAINT FK_Branches_Employees FOREIGN KEY (EmployeeID) REFERENCES Employees(EmployeeID);
GO


-- ============================================================================
-- 2. Transformați o relație 1:N în M:N
-- Relație aleasă: AccountTypes (1) -> Accounts (N) devine M:N (prin crearea unui tabel de legătură)
-- ============================================================================
PRINT '--- TRANSFORMER 2: 1:N to M:N (AccountTypes & Accounts) ---';

-- Cream tabelul de legătură M:N
CREATE TABLE AccountTypeMapping (
    AccountTypeID INT NOT NULL,
    AccountID INT NOT NULL,
    PRIMARY KEY (AccountTypeID, AccountID),
    CONSTRAINT FK_ATM_AccountTypes FOREIGN KEY (AccountTypeID) REFERENCES AccountTypes(AccountTypeID),
    CONSTRAINT FK_ATM_Accounts FOREIGN KEY (AccountID) REFERENCES Accounts(AccountID)
);
GO

-- Migrăm datele existente din coloana veche în noul tabel de legătură
INSERT INTO AccountTypeMapping (AccountTypeID, AccountID)
SELECT AccountTypeID, AccountID FROM Accounts;
GO

-- Ștergem vechea cheie străină și coloana AccountTypeID din Accounts
ALTER TABLE Accounts DROP CONSTRAINT FK_Accounts_AccountTypes;
ALTER TABLE Accounts DROP COLUMN AccountTypeID;
GO


-- ============================================================================
-- 3. Transformați o relație M:N în 1:N
-- Relație aleasă: CustomerAccounts (M:N între Customers și Accounts) devine 1:N
-- Reguli aplicate: 
--  - Se păstrează FK corespunzătoare înregistrării cu cea mai mare valoare (MAX(CustomerID)).
--  - Se salvează legăturile șterse în tabelul Legaturi_Eliminate.
-- ============================================================================
PRINT '--- TRANSFORMER 3: M:N to 1:N (Customers & Accounts) ---';

-- Pasul A: Adăugăm coloana CustomerID în tabela Accounts (partea N a relației 1:N)
ALTER TABLE Accounts ADD CustomerID INT NULL;
GO

-- Pasul B: Salvăm în Legaturi_Eliminate legăturile care NU au CustomerID-ul maxim (adică cele ce vor fi șterse)
INSERT INTO Legaturi_Eliminate (NumeTabelSt, IdSt, NumeTabelDr, IdDr)
SELECT 'Customers', ca.CustomerID, 'Accounts', ca.AccountID
FROM CustomerAccounts ca
JOIN (
    SELECT AccountID, MAX(CustomerID) AS MaxCustomerID
    FROM CustomerAccounts
    GROUP BY AccountID
) sub ON ca.AccountID = sub.AccountID
WHERE ca.CustomerID <> sub.MaxCustomerID;
GO

-- Pasul C: Actualizăm Accounts păstrând doar clientul cu cel mai mare ID (MaxCustomerID)
UPDATE a
SET a.CustomerID = sub.MaxCustomerID
FROM Accounts a
JOIN (
    SELECT AccountID, MAX(CustomerID) AS MaxCustomerID
    FROM CustomerAccounts
    GROUP BY AccountID
) sub ON a.AccountID = sub.AccountID;
GO

-- Pentru conturile care nu aveau niciun client în CustomerAccounts, punem un CustomerID default (ex: 1)
UPDATE Accounts SET CustomerID = 1 WHERE CustomerID IS NULL;
GO

-- Facem coloana NOT NULL și adăugăm constrângerea Foreign Key
ALTER TABLE Accounts ALTER COLUMN CustomerID INT NOT NULL;
ALTER TABLE Accounts ADD CONSTRAINT FK_Accounts_Customers FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID);
GO

-- Ștergem tabelul vechi de legătură M:N `CustomerAccounts`
DROP TABLE CustomerAccounts;
GO


-- ============================================================================
-- 4. Transformați o relație 1:N în 1:1
-- Relație aleasă: Branches (1) -> Loans (N) devine 1:1 (prin adăugarea unei constrângeri UNIQUE pe Loan.BranchID)
-- (Notă: Ne asigurăm mai întâi că fiecare branch apare o singură dată în Loans pentru a permite UNICQ)
-- ============================================================================
PRINT '--- TRANSFORMER 4: 1:N to 1:1 (Branches & Loans) ---';

-- Pentru a transforma 1:N în 1:1, restricționăm ca un Branch să poată avea cel mult un singur Loan (UNIQUE pe BranchID în Loans)
-- Dacă un branch are mai multe credite, păstrăm doar primul (ștergem restul din Loans pentru test)
DELETE FROM Loans 
WHERE LoanID NOT IN (
    SELECT MIN(LoanID) 
    FROM Loans 
    GROUP BY BranchID
);
GO

-- Adăugăm constrângerea UNIQUE pe BranchID în tabela Loans, transformând relația din 1:N în 1:1
ALTER TABLE Loans ADD CONSTRAINT UQ_Loans_BranchID UNIQUE (BranchID);
GO


-- ============================================================================
-- 4. INTEROGĂRI DE VERIFICARE FINALĂ
-- ============================================================================
SELECT 'Branches & Employees (N:1)' AS TransformationType, * FROM Branches;
SELECT 'AccountTypeMapping (M:N)' AS TransformationType, * FROM AccountTypeMapping;
SELECT 'Accounts with CustomerID (1:N)' AS TransformationType, AccountID, AccountNumber, CustomerID FROM Accounts;
SELECT 'Legaturi Eliminate (M:N -> 1:N)' AS TransformationType, * FROM Legaturi_Eliminate;
SELECT 'Loans with Unique BranchID (1:1)' AS TransformationType, LoanID, BranchID, LoanAmount FROM Loans;