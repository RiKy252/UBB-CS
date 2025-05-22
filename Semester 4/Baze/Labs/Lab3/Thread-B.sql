use Supermarket
go

-- dirty read

-- SET TRANSACTION ISOLATION LEVEL READ COMMITTED
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
BEGIN TRAN;

SELECT * FROM ExampleTable WHERE ExampleId = 1;
commit

-- non-repeatable reads

SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;

BEGIN TRAN;
UPDATE ExampleTable SET ExampleNumber = ExampleNumber + 250 WHERE ExampleId = 1;
COMMIT;

-- phantom reads

SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;

BEGIN TRAN;
INSERT INTO ExampleTable VALUES (4, 120);
COMMIT;

-- deadlock

BEGIN TRAN;
UPDATE ExampleTable SET ExampleNumber = ExampleNumber + 10 WHERE ExampleId = 2;
WAITFOR DELAY '00:00:15';
UPDATE ExampleTable SET ExampleNumber = ExampleNumber - 10 WHERE ExampleId = 1; -- waits for A
commit;

-- sol:
SET DEADLOCK_PRIORITY LOW
BEGIN TRAN;
UPDATE ExampleTable SET ExampleNumber = ExampleNumber - 10 WHERE ExampleId = 1;
WAITFOR DELAY '00:00:10';
UPDATE ExampleTable SET ExampleNumber = ExampleNumber + 10 WHERE ExampleId = 2; 