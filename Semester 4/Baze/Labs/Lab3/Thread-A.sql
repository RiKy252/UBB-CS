use Supermarket
go

exec sp_who2

DROP TABLE IF EXISTS ExampleTable;
CREATE TABLE ExampleTable (
    ExampleId INT PRIMARY KEY,
    ExampleNumber INT
);

INSERT INTO ExampleTable VALUES (1, 250), (2, 400), (3, 25);

SELECT * FROM ExampleTable

-- dirty read

-- SET TRANSACTION ISOLATION LEVEL READ COMMITTED
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;

BEGIN TRAN;
UPDATE ExampleTable
SET ExampleNumber = 999
WHERE ExampleId = 1;
WAITFOR DELAY '00:00:10';
commit;

-- non-repeatable reads

SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;

BEGIN TRAN;
SELECT ExampleNumber FROM ExampleTable WHERE ExampleId = 1;
WAITFOR DELAY '00:00:10';
SELECT ExampleNumber FROM ExampleTable WHERE ExampleId = 1;
COMMIT;

-- phantom reads

SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;

BEGIN TRAN;
SELECT * FROM ExampleTable WHERE ExampleNumber > 100;
WAITFOR DELAY '00:00:10';
SELECT * FROM ExampleTable WHERE ExampleNumber > 100;
COMMIT;

-- deadlock

BEGIN TRAN;
UPDATE ExampleTable SET ExampleNumber = ExampleNumber - 10 WHERE ExampleId = 1;
WAITFOR DELAY '00:00:10';
UPDATE ExampleTable SET ExampleNumber = ExampleNumber + 10 WHERE ExampleId = 2;  -- Waits for B
commit;

-- sol: ?
SET DEADLOCK_PRIORITY LOW
BEGIN TRAN;
UPDATE ExampleTable SET ExampleNumber = ExampleNumber - 10 WHERE ExampleId = 1;
WAITFOR DELAY '00:00:10';
UPDATE ExampleTable SET ExampleNumber = ExampleNumber + 10 WHERE ExampleId = 2; 