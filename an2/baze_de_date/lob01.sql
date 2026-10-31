CREATE DATABASE BankManagement;
GO

USE BankManagement;
GO

drop database BankManagement;

-- 1. Branches
CREATE TABLE Branches(
    BranchID INT PRIMARY KEY IDENTITY(1, 1),
    BranchName NVARCHAR(100) NOT NULL,
    BranchCode VARCHAR(10) UNIQUE NOT NULL,
    BranchAddress NVARCHAR(255) NOT NULL,
    City NVARCHAR(100) NOT NULL,
    PhoneNumber VARCHAR(20)
);

-- 2. AccountTypes
CREATE TABLE AccountTypes(
    AccountTypeID INT PRIMARY KEY IDENTITY(1, 1),
    TypeName VARCHAR(50) UNIQUE NOT NULL,
    InterestRate DECIMAL(5, 4) DEFAULT 0.00 CHECK (InterestRate >= 0),
    MonthlyFee DECIMAL(10, 2) DEFAULT 0.00
);

-- 3. Customers
CREATE TABLE Customers(
    CustomerID INT PRIMARY KEY IDENTITY(1, 1),
    FirstName NVARCHAR(100) NOT NULL,
    LastName NVARCHAR(100) NOT NULL,
    PersonalNumericCode VARCHAR(20) UNIQUE NOT NULL,
    DateOfBirth DATE NOT NULL CHECK (DateOfBirth <= GETDATE()),
    Email VARCHAR(100) UNIQUE,
    PhoneNumber VARCHAR(20) NOT NULL,
    CustomerAddress NVARCHAR(255) -- Corectat din CustomerAdress
);

-- 4. Employees
CREATE TABLE Employees(
    EmployeeID INT IDENTITY(1,1) PRIMARY KEY,
    BranchID INT NOT NULL,
    FirstName NVARCHAR(100) NOT NULL,
    LastName NVARCHAR(100) NOT NULL,
    JobTitle VARCHAR(50) NOT NULL,
    HireDate DATE DEFAULT GETDATE(),
    Salary DECIMAL(10,2) NOT NULL CHECK (Salary > 0),
    CONSTRAINT FK_Employees_Branches FOREIGN KEY (BranchID) REFERENCES Branches(BranchID)
);

-- 5. Accounts
CREATE TABLE Accounts (
    AccountID INT IDENTITY(1,1) PRIMARY KEY,
    BranchID INT NOT NULL,
    AccountTypeID INT NOT NULL,
    AccountNumber VARCHAR(30) UNIQUE NOT NULL,
    Balance DECIMAL(18,2) DEFAULT 0.00,
    Currency VARCHAR(3) DEFAULT 'USD',
    AccountStatus VARCHAR(20) DEFAULT 'Active' CHECK (AccountStatus IN ('Active', 'Suspended', 'Closed')), -- Redenumit din Status
    OpenedDate DATETIME DEFAULT GETDATE(),
    CONSTRAINT FK_Accounts_Branches FOREIGN KEY (BranchID) REFERENCES Branches(BranchID),
    CONSTRAINT FK_Accounts_AccountTypes FOREIGN KEY (AccountTypeID) REFERENCES AccountTypes(AccountTypeID)
);

-- 6. CustomerAccounts (Many-to-Many)
CREATE TABLE CustomerAccounts(
    CustomerID INT NOT NULL,
    AccountID INT NOT NULL,
    AccountRole VARCHAR(30) DEFAULT 'Primary' CHECK (AccountRole IN ('Primary', 'Secondary', 'Guarantor')),
    LinkDate DATETIME DEFAULT GETDATE(),
    PRIMARY KEY (CustomerID, AccountID),
    CONSTRAINT FK_CustomerAccounts_Customers FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID),
    CONSTRAINT FK_CustomerAccounts_Accounts FOREIGN KEY (AccountID) REFERENCES Accounts(AccountID)
);

-- 7. Transactions
CREATE TABLE Transactions (
    TransactionID INT IDENTITY(1,1) PRIMARY KEY,
    AccountID INT NOT NULL,
    TransactionType VARCHAR(20) NOT NULL CHECK (TransactionType IN ('Deposit', 'Withdrawal', 'Transfer', 'Fee')),
    Amount DECIMAL(18,2) NOT NULL CHECK (Amount > 0),
    TransactionDate DATETIME DEFAULT GETDATE(),
    Description NVARCHAR(255),
    CONSTRAINT FK_Transactions_Accounts FOREIGN KEY (AccountID) REFERENCES Accounts(AccountID)
);

-- 8. Cards
CREATE TABLE Cards (
    CardID INT IDENTITY(1,1) PRIMARY KEY,
    AccountID INT NOT NULL,
    CardNumber VARCHAR(16) UNIQUE NOT NULL,
    CardType VARCHAR(20) NOT NULL CHECK (CardType IN ('Debit', 'Credit')),
    ExpiryDate DATE NOT NULL,
    CVV VARCHAR(4) NOT NULL,
    IsActive BIT DEFAULT 1,
    CONSTRAINT FK_Cards_Accounts FOREIGN KEY (AccountID) REFERENCES Accounts(AccountID)
);

-- 9. Loans
CREATE TABLE Loans (
    LoanID INT IDENTITY(1,1) PRIMARY KEY,
    CustomerID INT NOT NULL,
    BranchID INT NOT NULL,
    LoanAmount DECIMAL(18,2) NOT NULL CHECK (LoanAmount > 0),
    InterestRate DECIMAL(5,4) NOT NULL,
    TermInMonths INT NOT NULL CHECK (TermInMonths > 0),
    StartDate DATE DEFAULT GETDATE(),
    LoanStatus VARCHAR(20) DEFAULT 'Pending' CHECK (LoanStatus IN ('Pending', 'Approved', 'PaidOff', 'Defaulted')), -- Redenumit din Status
    CONSTRAINT FK_Loans_Customers FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID),
    CONSTRAINT FK_Loans_Branches FOREIGN KEY (BranchID) REFERENCES Branches(BranchID)
);

-- 10. LoanPayments
CREATE TABLE LoanPayments (
    PaymentID INT IDENTITY(1,1) PRIMARY KEY,
    LoanID INT NOT NULL,
    PaymentAmount DECIMAL(18,2) NOT NULL CHECK (PaymentAmount > 0),
    PaymentDate DATETIME DEFAULT GETDATE(),
    PrincipalAmount DECIMAL(18,2) NOT NULL,
    InterestAmount DECIMAL(18,2) NOT NULL,
    CONSTRAINT FK_LoanPayments_Loans FOREIGN KEY (LoanID) REFERENCES Loans(LoanID)
);