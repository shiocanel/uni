USE BankManagement;
GO

-- tabelul de versionare
IF OBJECT_ID('DatabaseVersion', 'U') IS NOT NULL
    DROP TABLE DatabaseVersion;
GO

CREATE TABLE DatabaseVersion (
    VersionID INT PRIMARY KEY
);

INSERT INTO DatabaseVersion (VersionID) VALUES 
(0);
GO

-- modificarea tipului unei coloane
GO
CREATE PROCEDURE sp_UpgradeToV1 AS
BEGIN
    ALTER TABLE Branches ALTER COLUMN PhoneNumber VARCHAR(30);
    PRINT 'Upgraded to V1: Modified Branches.PhoneNumber to VARCHAR(30).';
END;
GO

CREATE PROCEDURE sp_DowngradeToV0 AS
BEGIN
    ALTER TABLE Branches ALTER COLUMN PhoneNumber VARCHAR(20);
    PRINT 'Downgraded to V0: Reverted Branches.PhoneNumber to VARCHAR(20).';
END;
GO


-- adauga constrangere
CREATE PROCEDURE sp_UpgradeToV2 AS
BEGIN
    ALTER TABLE Customers ADD CONSTRAINT DF_Customers_CustomerAddress DEFAULT 'Not Provided' FOR CustomerAddress;
    PRINT 'Upgraded to V2: Added DEFAULT constraint on Customers.CustomerAddress.';
END;
GO

CREATE PROCEDURE sp_DowngradeToV1 AS
BEGIN
    ALTER TABLE Customers DROP CONSTRAINT DF_Customers_CustomerAddress;
    PRINT 'Downgraded to V1: Dropped DEFAULT constraint on Customers.CustomerAddress.';
END;
GO


-- crearea stergere auditlogs
CREATE PROCEDURE sp_UpgradeToV3 AS
BEGIN
    CREATE TABLE AuditLogs (
        LogID INT IDENTITY(1,1) PRIMARY KEY,
        ActionDescription NVARCHAR(255) NOT NULL,
        LogDate DATETIME DEFAULT GETDATE()
    );
    PRINT 'Upgraded to V3: Created table AuditLogs.';
END;
GO

CREATE PROCEDURE sp_DowngradeToV2 AS
BEGIN
    DROP TABLE AuditLogs;
    PRINT 'Downgraded to V2: Dropped table AuditLogs.';
END;
GO


-- adauga camp nou
CREATE PROCEDURE sp_UpgradeToV4 AS
BEGIN
    ALTER TABLE Branches ADD BranchRating DECIMAL(3,2) NULL;
    PRINT 'Upgraded to V4: Added column BranchRating to Branches.';
END;
GO

CREATE PROCEDURE sp_DowngradeToV3 AS
BEGIN
    ALTER TABLE Branches DROP COLUMN BranchRating;
    PRINT 'Downgraded to V3: Dropped column BranchRating from Branches.';
END;
GO


--constrangere pe o cheie straine
CREATE PROCEDURE sp_UpgradeToV5 AS
BEGIN
    ALTER TABLE Cards DROP CONSTRAINT FK_Cards_Accounts;
    PRINT 'Upgraded to V5: Dropped foreign key constraint FK_Cards_Accounts.';
END;
GO

CREATE PROCEDURE sp_DowngradeToV4 AS
BEGIN
    ALTER TABLE Cards ADD CONSTRAINT FK_Cards_Accounts FOREIGN KEY (AccountID) REFERENCES Accounts(AccountID);
    PRINT 'Downgraded to V4: Re-created foreign key constraint FK_Cards_Accounts.';
END;
GO


-- procedura de tranzatie intre versiuni
GO
CREATE PROCEDURE sp_ChangeDatabaseVersion
    @TargetVersion INT
AS
BEGIN
    DECLARE @CurrentVersion INT;
    

    SELECT @CurrentVersion = VersionID 
    FROM DatabaseVersion;

    IF @TargetVersion < 0 OR @TargetVersion > 5
    BEGIN
        RAISERROR('Invalid target version!', 16, 1);
        RETURN;
    END

    WHILE @CurrentVersion < @TargetVersion
    BEGIN
        IF @CurrentVersion = 0 
        BEGIN 
            EXEC sp_UpgradeToV1; 
            UPDATE DatabaseVersion SET VersionID = 1; 
        END
        ELSE IF @CurrentVersion = 1 
        BEGIN 
            EXEC sp_UpgradeToV2; 
            UPDATE DatabaseVersion SET VersionID = 2; 
        END
        ELSE IF @CurrentVersion = 2 
        BEGIN 
            EXEC sp_UpgradeToV3; 
            UPDATE DatabaseVersion SET VersionID = 3; 
        END
        ELSE IF @CurrentVersion = 3 
        BEGIN 
            EXEC sp_UpgradeToV4; 
            UPDATE DatabaseVersion SET VersionID = 4; 
        END
        ELSE IF @CurrentVersion = 4 
        BEGIN 
            EXEC sp_UpgradeToV5; 
            UPDATE DatabaseVersion SET VersionID = 5; 
        END
        
        SELECT @CurrentVersion = VersionID 
        FROM DatabaseVersion;
    END

    WHILE @CurrentVersion > @TargetVersion
    BEGIN
        IF @CurrentVersion = 5 
        BEGIN 
            EXEC sp_DowngradeToV4; 
            UPDATE DatabaseVersion SET VersionID = 4; 
        END
        ELSE IF @CurrentVersion = 4 
        BEGIN 
            EXEC sp_DowngradeToV3; 
            UPDATE DatabaseVersion SET VersionID = 3; 
        END
        ELSE IF @CurrentVersion = 3 
        BEGIN 
            EXEC sp_DowngradeToV2; 
            UPDATE DatabaseVersion SET VersionID = 2; 
        END
        ELSE IF @CurrentVersion = 2 
        BEGIN 
            EXEC sp_DowngradeToV1; 
            UPDATE DatabaseVersion SET VersionID = 1; 
        END
        ELSE IF @CurrentVersion = 1 
        BEGIN 
            EXEC sp_DowngradeToV0; 
            UPDATE DatabaseVersion SET VersionID = 0; 
        END
        
        SELECT @CurrentVersion = VersionID FROM DatabaseVersion;
    END

    PRINT 'Database to version: ' + CAST(@TargetVersion AS VARCHAR(10));
END;
GO


SELECT * FROM DatabaseVersion;

EXEC sp_ChangeDatabaseVersion @TargetVersion = 0;
GO

SELECT * FROM Branches;

EXEC sp_ChangeDatabaseVersion @TargetVersion = 1;
GO

EXEC sp_ChangeDatabaseVersion @TargetVersion = 2;
GO

EXEC sp_ChangeDatabaseVersion @TargetVersion = 3;
GO

EXEC sp_ChangeDatabaseVersion @TargetVersion = 4;
GO

EXEC sp_ChangeDatabaseVersion @TargetVersion = 5;
GO

EXEC sp_ChangeDatabaseVersion @TargetVersion = 0;
GO
