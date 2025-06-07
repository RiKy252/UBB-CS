use Altex
go

select * from Distributors

-- same query returns different result in same transaction

SET TRANSACTION ISOLATION LEVEL READ COMMITTED;

BEGIN TRAN;
SELECT Dphone FROM Distributors WHERE Did = 1;
WAITFOR DELAY '00:00:10';
SELECT Dphone FROM Distributors WHERE Did = 1;
COMMIT;

-- sol
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;



-- reset

UPDATE Distributors SET Dphone = 'Distributor 1 phone number' WHERE Did = 1;
