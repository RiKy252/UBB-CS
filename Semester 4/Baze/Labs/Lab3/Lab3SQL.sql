use Supermarket
go

-- SCENARIO 1

CREATE OR ALTER PROCEDURE AddCustomerWithProductTransactional
    @CustomerName NVARCHAR(100),
    @Age INT,
    @ProductName NVARCHAR(100),
    @CategoryId INT,
    @Price DECIMAL(10, 2),
    @ExpDate DATE
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @CustomerId INT;
    DECLARE @ProductId INT;

    BEGIN TRY
        BEGIN TRAN;

        -- Validate age
        IF @Age < 1 OR @Age > 100
        BEGIN
            THROW 50001, 'Age must be between 1 and 100.', 1;
        END

        -- Check if customer already exists
        IF EXISTS (SELECT 1 FROM customers WHERE customerName = @CustomerName)
        BEGIN
            THROW 50002, 'Customer already exists.', 1;
        END

        -- Insert customer
        INSERT INTO customers (customerName, age)
        VALUES (@CustomerName, @Age);
        SET @CustomerId = SCOPE_IDENTITY();

        -- Validate category
        IF NOT EXISTS (SELECT 1 FROM category WHERE categoryId = @CategoryId)
        BEGIN
            THROW 50003, 'Invalid category ID.', 1;
        END

        -- Validate price
        IF @Price < 0
        BEGIN
            THROW 50004, 'Price cannot be negative.', 1;
        END

        -- Validate expiration date
        IF @ExpDate <= GETDATE()
        BEGIN
            THROW 50005, 'Expiration date must be in the future.', 1;
        END

        -- Check if product already exists
        IF EXISTS (SELECT 1 FROM products WHERE name = @ProductName)
        BEGIN
            THROW 50006, 'Product already exists.', 1;
        END

        -- Insert product
        INSERT INTO products (categoryId, name, price, expiringDate)
        VALUES (@CategoryId, @ProductName, @Price, @ExpDate);
        SET @ProductId = SCOPE_IDENTITY();

        -- Link customer and product
        INSERT INTO customersProducts (customerId, productId)
        VALUES (@CustomerId, @ProductId);

        COMMIT;
        PRINT 'Transaction completed successfully.';
    END TRY
    BEGIN CATCH
        ROLLBACK;

        PRINT 'Transaction failed and rolled back.';
        PRINT ERROR_MESSAGE();
    END CATCH
END

EXEC AddCustomerWithProductTransactional
	@CustomerName = 'Dan',
	@Age = 32,
	@ProductName = 'Sprite',
	@CategoryId = 5,
	@Price = 2.33,
	@ExpDate = '2026-01-01'; 

select * from customersProducts
select * from customers
select * from products 

-- SCENARIO 2
CREATE OR ALTER PROCEDURE AddCustomerWithProduct
	@CustomerName NVARCHAR(100),
    @Age INT,
    @ProductName NVARCHAR(100),
    @CategoryId INT,
    @Price DECIMAL(10, 2),
    @ExpDate DATE
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @CustomerId INT;
    DECLARE @ProductId INT;
	DECLARE @SkipCustomer BIT = 0;

    BEGIN TRY
        IF @Age < 1 OR @Age > 100
        BEGIN
            PRINT 'Age must be between 1 and 100. Aborting customer insert.';
            SET @SkipCustomer = 1;
        END

		IF @SkipCustomer = 0
		BEGIN
			IF NOT EXISTS (SELECT 1 FROM customers WHERE customerName = @CustomerName)
			BEGIN
				INSERT INTO customers (customerName, age)
				VALUES (@CustomerName, @Age);

				SET @CustomerId = SCOPE_IDENTITY();
				PRINT 'Inserted customer.';
			END
			ELSE
			BEGIN
				SELECT @CustomerId = customerId FROM customers WHERE customerName = @CustomerName;
				PRINT 'Customer already exists.';
			END
		END
    END TRY
    BEGIN CATCH
        PRINT 'Error inserting customer: ' + ERROR_MESSAGE();
        RETURN;
    END CATCH

    BEGIN TRY
        IF NOT EXISTS (SELECT 1 FROM products WHERE name = @ProductName)
        BEGIN
            -- Validate category
            IF NOT EXISTS (SELECT 1 FROM category WHERE categoryId = @CategoryId)
            BEGIN
                PRINT 'Invalid category ID. Aborting product insert.';
                RETURN;
            END

            -- Validate price
            IF @Price < 0
            BEGIN
                PRINT 'Price cannot be negative. Aborting product insert.';
                RETURN;
            END

            -- Validate expiring date
            IF @ExpDate <= GETDATE()
            BEGIN
                PRINT 'Expiring date must be in the future. Aborting product insert.';
                RETURN;
            END

            -- Insert product
            INSERT INTO products (categoryId, name, price, expiringDate)
            VALUES (@CategoryId, @ProductName, @Price, @ExpDate);

            SET @ProductId = SCOPE_IDENTITY();
            PRINT CONCAT('Inserted product with ID ', @ProductId);
        END
        ELSE
        BEGIN
            SELECT @ProductId = productId FROM products WHERE name = @ProductName;
            PRINT CONCAT('Product already exists with ID ', @ProductId);
        END
    END TRY
    BEGIN CATCH
        PRINT 'Error inserting product: ' + ERROR_MESSAGE();
        RETURN;
    END CATCH

    BEGIN TRY
        IF NOT EXISTS (
            SELECT 1 FROM customersProducts
            WHERE customerId = @CustomerId AND productId = @ProductId
        )
        BEGIN
            INSERT INTO customersProducts (customerId, productId)
            VALUES (@CustomerId, @ProductId);

            PRINT 'Linked customer with product.';
        END
        ELSE
        BEGIN
            PRINT 'Link already exists. Skipping.';
        END
    END TRY
    BEGIN CATCH
        PRINT 'Error linking customer and product: ' + ERROR_MESSAGE();
    END CATCH

    PRINT 'Procedure completed.';
END

EXEC AddCustomerWithProduct
	@CustomerName = 'Dan',
	@Age = 32,
	@ProductName = 'Sprite',
	@CategoryId = 5,
	@Price = 2.33,
	@ExpDate = '2026-01-01';

select * from customersProducts
select * from customers
select * from products 

-- SCENARIO 3

-- Dirty Reads (READ UNCOMMITTED)
-- problem: one transaction reads uncommitted data from another transaction
-- SOLUTION: use read commited

-- Non-Repeatable Reads (READ COMMITTED)
-- problem is that the same query returns different result in the same transaction
-- SOLUTION: use repeatable read 

-- Phantom Reads (REPEATABLE READ)
-- problem is that: a query returns new rows when re-executed, even tho stable results are expected
-- SOLUTION: use serializable 

-- Deadlock
-- problem: Two sessions hold locks the other needs, causing a cycle
-- SOLUTION: always access resources in the same order
