USE BankManagement;

INSERT INTO Branches (BranchName, BranchCode, BranchAddress, City, PhoneNumber) VALUES
('Central Branch', 'BR001', 'Str. Universitatii 10', 'Cluj-Napoca', '0264111222'),
('Unirii Branch', 'BR002', 'Bulevardul Titulescu 15', 'Bucuresti', '0213334444'),
('Copou Branch', 'BR003', 'Bulevardul Titulescu 20', 'Iasi', '0232555666'),
('Victory Square Branch', 'BR004', 'Calea Victoriei 12', 'Bucuresti', '0217778888');

SELECT * FROM Branches;

INSERT INTO AccountTypes (TypeName, InterestRate, MonthlyFee) VALUES
('Standard Checking', 0.0000, 5.00),
('Savings Account', 0.0350, 0.00),
('Premium Checking', 0.0100, 15.00),
('Student Account', 0.0050, 0.00);

INSERT INTO Customers (FirstName, LastName, PersonalNumericCode, DateOfBirth, Email, PhoneNumber, CustomerAddress) VALUES
('Ioan', 'Risca', '2950325432109', '1995-03-25', 'risca.ioan@yahoo.com', '0722333444', 'B-dul Libertatii 22, Bucuresti'),
('Luca', 'Racoti', '1901114512388', '1990-11-14', 'luca.racoti@gmail.com', '0763444555', 'Str. Lapusna 3, Iasi'),
('Alexandra', 'Popovici', '1980512123456', '1998-05-12', 'alexandra.popovici@gmail.com', '0740111222', 'Str. Memorandumului 5, Cluj-Napoca'),
('Valeriu', 'Nistor', '2990708112233', '1999-07-08', 'valeriu.nist@gmail.com', '0751222333', 'Calea Dorobantilor 45, Bucuresti'),
('Antonio', 'Russano', '1851204223344', '1985-12-04', 'a.russ@gmail.com', '0770889900', 'Str. Horei 12, Cluj-Napoca');

INSERT INTO Employees (BranchID, FirstName, LastName, JobTitle, HireDate, Salary) VALUES
(1, 'Ana', 'Munteanu', 'Branch Manager', '2015-06-01', 6500.00),
(1, 'Ioana', 'Stancu', 'Cashier', '2020-03-15', 3200.00),
(2, 'Radu', 'Constantin', 'Loan Officer', '2018-09-10', 4800.00),
(3, 'Carmen', 'Vasile', 'Customer Advisor', '2021-01-20', 3500.00),
(4, 'Mihai', 'Petrescu', 'Branch Manager', '2014-11-05', 7000.00);

INSERT INTO Accounts (BranchID, AccountTypeID, AccountNumber, Balance, Currency, AccountStatus, OpenedDate) VALUES
(1, 1, 'RO49RNCB0123456789010001', 2450.50, 'RON', 'Active', '2022-01-15'),
(1, 2, 'RO49RNCB0123456789010002', 12500.00, 'RON', 'Active', '2022-02-20'),
(2, 3, 'RO14BRDE4567891234560001', 45000.00, 'RON', 'Active', '2021-05-10'),
(3, 4, 'RO55BTRL9876543210980001', 850.30, 'RON', 'Active', '2023-10-05'),
(4, 1, 'RO88INGB1122334455660001', 3100.00, 'EUR', 'Active', '2023-03-12'),
(2, 2, 'RO14BRDE4567891234560002', 23000.00, 'RON', 'Active', '2023-08-15');

INSERT INTO CustomerAccounts (CustomerID, AccountID, AccountRole, LinkDate) VALUES
(1, 1, 'Primary', '2022-01-15'),
(1, 2, 'Primary', '2022-02-20'),
(2, 3, 'Primary', '2021-05-10'),
(3, 4, 'Primary', '2023-10-05'),
(4, 5, 'Primary', '2023-03-12'),
(2, 6, 'Primary', '2023-08-15'),
(5, 6, 'Secondary', '2023-08-15');

INSERT INTO Transactions (AccountID, TransactionType, Amount, TransactionDate, Description) VALUES
(1, 'Deposit', 1000.00, '2026-01-10 10:30:00', 'Monthly Salary'),
(1, 'Withdrawal', 200.00, '2026-01-12 14:15:00', 'ATM Withdrawal'),
(2, 'Deposit', 5000.00, '2026-01-15 09:00:00', 'Savings deposit'),
(3, 'Transfer', 1500.00, '2026-01-18 16:45:00', 'Rent payment'),
(4, 'Withdrawal', 100.00, '2026-01-20 11:20:00', 'Supermarket purchase');

INSERT INTO Cards (AccountID, CardNumber, CardType, ExpiryDate, CVV, IsActive) VALUES
(1, '4532781293847561', 'Debit', '2028-05-30', '123', 1),
(2, '5412758963251478', 'Credit', '2027-12-31', '456', 1),
(3, '4000123456789010', 'Debit', '2029-03-31', '789', 1),
(4, '5234567890123456', 'Debit', '2026-09-30', '321', 1);

INSERT INTO Loans (CustomerID, BranchID, LoanAmount, InterestRate, TermInMonths, StartDate, LoanStatus) VALUES
(1, 1, 25000.00, 0.0850, 60, '2023-06-01', 'Approved'),
(2, 2, 120000.00, 0.0690, 300, '2021-08-15', 'Approved'),
(3, 3, 10000.00, 0.0900, 24, '2024-02-10', 'Approved');

INSERT INTO LoanPayments (LoanID, PaymentAmount, PaymentDate, PrincipalAmount, InterestAmount) VALUES
(1, 515.50, '2026-01-05 10:00:00', 390.50, 125.00),
(1, 515.50, '2026-02-05 10:00:00', 393.20, 122.30),
(2, 850.00, '2026-01-10 11:30:00', 160.00, 690.00),
(3, 456.00, '2026-01-15 12:00:00', 381.00, 75.00);
GO

SELECT * FROM Accounts;
SELECT * FROM AccountTypes;
SELECT * FROM Branches;
SELECT * FROM Cards;
SELECT * FROM CustomerAccounts;
SELECT * FROM Customers;
SELECT * FROM Employees;
SELECT * FROM LoanPayments;
SELECT * FROM Loans;
SELECT * FROM Transactions;

--ctustomers din Bucuresti m - n
SELECT c.FirstName, c.LastName, c.Email, a.AccountNumber, a.Balance
FROM Customers c
JOIN CustomerAccounts ca ON c.CustomerID = ca.CustomerID
JOIN Accounts a ON ca.AccountID = a.AccountID
WHERE c.CustomerAddress LIKE '%Bucuresti%';


--tranzactii > 500 m - n
SELECT c.FirstName, c.LastName, a.AccountNumber, t.TransactionType, t.Amount, t.TransactionDate
FROM Transactions t
JOIN Accounts a ON t.AccountID = a.AccountID
JOIN CustomerAccounts ca ON a.AccountID = ca.AccountID
JOIN Customers c ON ca.CustomerID = c.CustomerID
WHERE t.Amount > 500.00;


--carduri care expira dupa 2026
SELECT cr.CardNumber, cr.CardType, cr.ExpiryDate, a.AccountNumber, b.BranchName
FROM Cards cr
JOIN Accounts a ON cr.AccountID = a.AccountID
JOIN Branches b ON a.BranchID = b.BranchID
WHERE cr.IsActive = 1 AND cr.ExpiryDate > '2026-12-31';


--conturi active cu balance > 1000 
SELECT DISTINCT at.TypeName, at.InterestRate
FROM AccountTypes at
JOIN Accounts a ON at.AccountTypeID = a.AccountTypeID
WHERE a.AccountStatus = 'Active' AND a.Balance > 1000.00;


--employees din Cluj-Napoca cu salary > 3000 
SELECT e.FirstName, e.LastName, e.JobTitle, e.Salary, b.BranchName, b.City
FROM Employees e
JOIN Branches b ON e.BranchID = b.BranchID
WHERE b.City = 'Cluj-Napoca' AND e.Salary > 3000.00;


--total balance grupate by branch si account type
SELECT b.BranchName, at.TypeName, SUM(a.Balance) AS TotalBalance, COUNT(a.AccountID) AS TotalAccountsCount
FROM Accounts a
JOIN Branches b ON a.BranchID = b.BranchID
JOIN AccountTypes at ON a.AccountTypeID = at.AccountTypeID
GROUP BY b.BranchName, at.TypeName;


--branches cu suma loan > 50000
SELECT b.BranchName, COUNT(l.LoanID) AS NumberOfLoans, SUM(l.LoanAmount) AS TotalLoanPortfolio
FROM Loans l
JOIN Branches b ON l.BranchID = b.BranchID
JOIN Customers c ON l.CustomerID = c.CustomerID
GROUP BY b.BranchName
HAVING SUM(l.LoanAmount) > 50000.00;


--cccount types si branches unde media soldului > 5000
SELECT at.TypeName, b.BranchName, AVG(a.Balance) AS AverageBalance
FROM Accounts a
JOIN AccountTypes at ON a.AccountTypeID = at.AccountTypeID
JOIN Branches b ON a.BranchID = b.BranchID
GROUP BY at.TypeName, b.BranchName
HAVING AVG(a.Balance) > 5000.00;


--jobs uri distincte ale angajatilor 
SELECT DISTINCT JobTitle
FROM Employees;

--Plati de credite cu detalii complete
SELECT lp.PaymentID, l.LoanID, c.FirstName + ' ' + c.LastName AS CustomerName, b.BranchName, lp.PaymentAmount, lp.PaymentDate
FROM LoanPayments lp
JOIN Loans l ON lp.LoanID = l.LoanID
JOIN Customers c ON l.CustomerID = c.CustomerID
JOIN Branches b ON l.BranchID = b.BranchID;