--Lab1 HW
--1:n -> checkoutCounter and customers
--1:n -> category and products
--n:m -> customers and products

create table shelves(
	shelfId int not null primary key,
	shelfCapacity int,
	shelfSize int
)

create table category(
	categoryId int not null primary key,
	categoryName varchar(100)
)

create table products(
	productId int not null primary key,
	categoryId int not null,
	name varchar(100),
	expiringDate date,
	price float,
	constraint FK_Category_Products foreign key (categoryId) references category (categoryId)
)

create table checkoutCounter(
	checkoutCounterId int not null primary key,
	cashInside float,
	isActive bit
)

create table checkoutEmployee(
	checkoutEmployeeId int foreign key references checkoutCounter(checkoutCounterId),
	salary float,
	active bit,
	constraint pk_checkoutEmployeeCounter primary key(checkoutEmployeeId)
)

create table customers(
	customerId int not null primary key,
	customerName varchar(100),
	checkoutCounterId int foreign key references checkoutCounter(checkoutCounterId)
)

create table customersProducts(
	customerId int foreign key references customers(customerId),
	productId int foreign key references products(productId),
	constraint pk_cproducts primary key (customerId, productId)
)

alter table products
add shelfId int;

alter table products
add constraint FK_Shelf_Products foreign key (shelfId) references shelves (shelfId);

alter table customers
add age int

create table restockEmployee(
	restockEmployeeId int not null primary key,
	salary float,
	active bit
)

create table shelvesRestockers(
	shelfId int foreign key references shelves(shelfId),
	restockerId int foreign key references restockEmployee(restockEmployeeId),
	constraint pk_shelfrestockers primary key (shelfId, restockerId)
)

create table freezer(
	freezerId int not null primary key,
	temperature float,
	freezerCapacity int,
	freezerSize int
)

-- Lab2 HW

-- Shelf insertions
INSERT INTO shelves (shelfId, shelfCapacity, shelfSize) VALUES (1, 50, 22);
INSERT INTO shelves (shelfId, shelfCapacity, shelfSize) VALUES (2, 100, 15);
INSERT INTO shelves (shelfId, shelfCapacity, shelfSize) VALUES (3, 250, 111);
INSERT INTO shelves (shelfId, shelfCapacity, shelfSize) VALUES (4, 350, 231);

SELECT * FROM shelves;

-- Category insertions
INSERT INTO category (categoryId, categoryName) VALUES (1, 'Dairy');
INSERT INTO category (categoryId, categoryName) VALUES (2, 'Bakery');
INSERT INTO category (categoryId, categoryName) VALUES (3, 'Meat & Seafood');
INSERT INTO category (categoryId, categoryName) VALUES (4, 'Frozen Foods');
INSERT INTO category (categoryId, categoryName) VALUES (5, 'Beverages');
INSERT INTO category (categoryId, categoryName) VALUES (6, 'Snacks');

SELECT * FROM category;

-- Product insertions
-- Dairy Products
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (1, 1, 'Milk', '2025-03-13', 5.35, 1);
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (2, 1, 'Cheddar Cheese', '2025-06-10', 3.75, 1);
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (3, 1, 'Yogurt', '2025-01-22', 2.50, 1);
-- Bakery Products
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (4, 2, 'Whole Wheat Bread', '2023-11-15', 1.99, 2);
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (5, 2, 'Croissant', '2023-11-05', 1.50, 2);
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (6, 2, 'Bagel', '2023-11-08', 1.25, 2);
-- Meat & Seafood
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (7, 3, 'Chicken Breast', '2023-12-10', 7.99, 3);
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (8, 3, 'Salmon Fillet', '2023-12-05', 12.50, 3);
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (9, 3, 'Ground Beef', '2023-12-01', 6.99, 3);
-- Frozen Foods
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (10, 4, 'Frozen Peas', '2025-08-30', 2.75, 4);
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (11, 4, 'Ice Cream', '2025-05-15', 4.99, 4);
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (12, 4, 'Pizza', '2025-06-01', 5.49, 4);
-- Beverages
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (13, 5, 'Orange Juice', '2024-01-10', 3.99, 3);
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (14, 5, 'Cola', '2025-02-01', 1.25, 3);
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (15, 5, 'Mineral Water', '2025-06-15', 0.99, 3);
-- Snacks
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (16, 6, 'Potato Chips', '2025-03-01', 1.75, 2);
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (17, 6, 'Pretzels', '2025-03-15', 1.50, 2);
INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) VALUES (18, 6, 'Chocolate Bar', '2025-04-01', 1.20, 2);

SELECT * FROM products;

-- Violation of referencial integrity insert example
INSERT INTO products (productId, categoryId, name, expiringDate, price) VALUES (25, 23, 'Something', '2025-05-21', 1.15);

-- Checkout counter insertions
INSERT INTO checkoutCounter (checkoutCounterId, cashInside, isActive) VALUES (1, 2593.4, 1);
INSERT INTO checkoutCounter (checkoutCounterId, cashInside, isActive) VALUES (2, 3223.15, 0);
INSERT INTO checkoutCounter (checkoutCounterId, cashInside, isActive) VALUES (3, 5594.3, 1);
INSERT INTO checkoutCounter (checkoutCounterId, cashInside, isActive) VALUES (4, 9126.74, 0);
INSERT INTO checkoutCounter (checkoutCounterId, cashInside, isActive) VALUES (5, 7291.6, 1);

SELECT * FROM checkoutCounter;

-- Customer insertions
INSERT INTO customers (customerId, customerName, checkoutCounterId) VALUES (1, 'Alex', 1);
INSERT INTO customers (customerId, customerName, checkoutCounterId) VALUES (2, 'Denis', 1);
INSERT INTO customers (customerId, customerName, checkoutCounterId) VALUES (3, 'Mihai', 5);
INSERT INTO customers (customerId, customerName, checkoutCounterId) VALUES (4, 'Radu', 5);
INSERT INTO customers (customerId, customerName, checkoutCounterId) VALUES (5, 'Razvan', 4);
INSERT INTO customers (customerId, customerName, checkoutCounterId) VALUES (6, 'Robert', 3);
INSERT INTO customers (customerId, customerName, checkoutCounterId) VALUES (7, 'Paul', 1);
INSERT INTO customers (customerId, customerName, checkoutCounterId) VALUES (8, 'Ionut', 2);
INSERT INTO customers (customerId, customerName, checkoutCounterId) VALUES (9, 'Dan', 4);
INSERT INTO customers (customerId, customerName, checkoutCounterId) VALUES (10, 'David', 3);


SELECT * FROM customers;
SELECT * FROM customersProducts

INSERT INTO customersProducts (customerId, productId) VALUES (2, 1)
INSERT INTO customersProducts (customerId, productId) VALUES (3, 8)
INSERT INTO customersProducts (customerId, productId) VALUES (10, 5)
INSERT INTO customersProducts (customerId, productId) VALUES (5, 3)

INSERT INTO restockEmployee (restockEmployeeId, salary, active) VALUES (1, 5000, 1)
INSERT INTO restockEmployee (restockEmployeeId, salary, active) VALUES (2, 3215, 0)
INSERT INTO restockEmployee (restockEmployeeId, salary, active) VALUES (3, 4321, 1)
INSERT INTO restockEmployee (restockEmployeeId, salary, active) VALUES (4, 2112, 0)
INSERT INTO restockEmployee (restockEmployeeId, salary, active) VALUES (5, 2356, 1)
INSERT INTO restockEmployee (restockEmployeeId, salary, active) VALUES (6, 3893, 0)
INSERT INTO restockEmployee (restockEmployeeId, salary, active) VALUES (7, 4849, 1)
INSERT INTO restockEmployee (restockEmployeeId, salary, active) VALUES (8, 1234, 1)
INSERT INTO restockEmployee (restockEmployeeId, salary, active) VALUES (9, 2345, 0)

INSERT INTO shelvesRestockers (shelfId, restockerId) VALUES (1, 5)
INSERT INTO shelvesRestockers (shelfId, restockerId) VALUES (2, 8)
INSERT INTO shelvesRestockers (shelfId, restockerId) VALUES (3, 7)
INSERT INTO shelvesRestockers (shelfId, restockerId) VALUES (4, 5)
INSERT INTO shelvesRestockers (shelfId, restockerId) VALUES (1, 3)
INSERT INTO shelvesRestockers (shelfId, restockerId) VALUES (2, 3)
INSERT INTO shelvesRestockers (shelfId, restockerId) VALUES (3, 2)
INSERT INTO shelvesRestockers (shelfId, restockerId) VALUES (4, 6)

-- UPDATE statements
-- For products
UPDATE products
SET products.shelfId = 4
WHERE products.categoryId = 1

SELECT * FROM products
--obs2
UPDATE products
SET products.shelfId = 3
WHERE (products.price < 3 AND products.categoryId >= 5)
--obs2
UPDATE products
SET products.shelfId = 3
WHERE (products.price BETWEEN 2 AND 10)

SELECT * FROM products

-- For customers

UPDATE customers
SET customers.age = 19
WHERE customers.checkoutCounterId = 1;

UPDATE customers
SET customers.checkoutCounterId = 3
WHERE customers.age IS NOT NULL

UPDATE customers
SET customers.age = 22
WHERE customers.customerName LIKE 'R%'

SELECT * FROM customers;

-- For checkout counter

UPDATE checkoutCounter
SET checkoutCounter.cashInside = 0
WHERE checkoutCounter.isActive = 0

SELECT * FROM checkoutCounter

-- DELETE statements
-- From customers
DELETE FROM customers
WHERE customers.customerId = 9 

DELETE FROM customers
WHERE customers.customerId IN (1, 4, 9)

SELECT * FROM customers

-- From products
DELETE FROM products
WHERE products.name = 'Bagel'

SELECT * FROM products

-- QUERIES
-- a)
SELECT * FROM products

SELECT products.name, products.expiringDate
FROM products
WHERE products.expiringDate LIKE '%10'
UNION ALL
SELECT products.name, products.expiringDate
FROM products
WHERE products.shelfId IS NOT NULL

SELECT products.name, products.expiringDate
FROM products
WHERE products.expiringDate LIKE '%10' OR products.shelfId IS NOT NULL

-- b)
SELECT * FROM customers

SELECT DISTINCT customers.customerName
FROM customers
WHERE customers.age = 22
INTERSECT
SELECT DISTINCT customers.customerName
FROM customers
WHERE customers.customerName LIKE 'R%'

SELECT customers.customerName
FROM customers
WHERE customers.customerId IN (1, 2, 5, 7, 22)

-- c)

SELECT * FROM products WHERE products.shelfId = 3

SELECT DISTINCT products.name, products.shelfId, products.price
FROM products
WHERE products.shelfId = 3
EXCEPT
SELECT products.name, products.shelfId, products.price
FROM products
WHERE products.price > 3
ORDER BY products.name desc

SELECT products.name, products.categoryId
FROM products
WHERE products.categoryId NOT IN (3, 4, 5)

-- d)

select * from products

-- 3 tables
select distinct products.name, products.productId
from products
inner join customers
on customers.customerId = products.productId
inner join checkoutCounter
on checkoutCounter.checkoutCounterId = products.productId
order by products.name asc

select * from products
select * from checkoutCounter
select * from customers
select * from customersProducts
select * from shelves
select * from restockEmployee
select * from shelvesRestockers

-- many to many
select customersProducts.customerId, customersProducts.productId
from customersProducts
full join customers
on customers.customerId = customersProducts.customerId

select shelvesRestockers.restockerId
from shelvesRestockers
left join restockEmployee
on restockEmployee.restockEmployeeId = shelvesRestockers.restockerId
--obs1
select products.price + 1 as incrementedPrice
from products
right join customers	
on customers.customerId = products.productId

-- e)

select * from customers
select * from customersProducts
select * from products
-- customers that have expensive products (> 5)
select customers.customerName
from customers
where customers.customerId in (select customersProducts.customerId
									from customersProducts
									where customersProducts.productId in (select products.productId
																			from products
																			where products.price > 5))
-- customers that have products from the shelf 3
select customers.customerName
from customers
where customers.customerId in (select customersProducts.customerId
								from customersProducts
								where customersProducts.productId in (select products.productId
																		from products
																		where products.shelfId = 3)) 
-- f)
select * from customers
select * from customersProducts
select * from products
-- select products that have been bought by customers
select p.name, p.productId
from products p
where exists (select *
				from customersProducts cp
				where cp.productId = p.productId)

select * from shelves
select * from restockEmployee
select * from shelvesRestockers
-- restockers that have at least a shelf to restock
select restockEmployee.restockEmployeeId, restockEmployee.salary
from restockEmployee
where exists (select *
				from shelvesRestockers
				where shelvesRestockers.restockerId = restockEmployee.restockEmployeeId)

-- g)
select customerId
from (select *
		from customers
		where customers.age = 22) as subquery

select *
from (select *
	from products
	where products.shelfId is not null) as subquery

-- h)
select customers.checkoutCounterId, min(customers.age) as youngest
from customers
group by customers.checkoutCounterId
having count(*) >= 2

select products.categoryId, sum(price) as total_sum
from products
group by products.categoryId

select products.categoryId, avg(price) as average_price
from products
group by products.categoryId
having avg(products.price) > (select avg(products.price) from products)

select products.categoryId, max(price) as maxPrice
from products
group by products.categoryId
having min(products.price) < (select avg(products.price) from products)

select * from products

-- i)
select * from customers


select customers.customerName, customers.age
from customers
where customers.age < any (select customers.age
							from customers
							where customers.customerName like 'R%')

select customers.customerName, customers.age
from customers
where customers.age < all (select customers.age
							from customers
							where customers.customerName like 'R%')

select * from products

select products.name, products.price
from products
where products.price > any (select products.price
							from products
							where products.name like 'M%')

select products.name, products.price
from products
where products.price > all (select products.price
							from products
							where products.name like 'M%')

-- agg

select products.name, products.price
from products
where products.price > any (select products.price
							from products
							where products.price > (select count(*) from customers))
--obs1
select customers.customerName, customers.age + 1 as incrementedAge
from customers
where customers.age > all (select max(products.price)
							from products)

-- in / not in
-- obs1 obs2 
select products.name, products.price + 1 as incrementedPrice
from products
where products.price > all (select products.price
							from products
							where products.categoryId not in (1, 3, 5))

select customers.customerName, customers.age
from customers
where customers.age > any (select customers.age
							from customers
							where customers.customerId in (10, 4, 23, 43))

-- top

select top 3 products.name, products.price
from products
order by products.price desc

select top 3 customers.customerName, customers.customerId
from customers
order by customers.customerName asc

-- Lab3 HW

-- a)

select * from checkoutCounter

CREATE PROCEDURE setIsActiveColumnFromBitToInt AS
	BEGIN
		ALTER TABLE checkoutCounter ALTER COLUMN isActive INT
		PRINT 'Changed isActive column type from BIT to INT'
	END
GO

CREATE PROCEDURE revertIsActiveColumnFromIntToBit AS
	BEGIN
		ALTER TABLE checkoutCounter ALTER COLUMN isActive BIT
		PRINT 'Changed isActive column type from INT to BIT'
	END
GO

EXEC setIsActiveColumnFromBitToInt
EXEC revertIsActiveColumnFromIntToBit

-- b)

select * from customers

CREATE PROCEDURE addCustomersOccupation AS
	BEGIN
		ALTER TABLE customers ADD occupation VARCHAR(30)
		PRINT 'Added occupation column for customers'
	END
GO

CREATE PROCEDURE removeCustomersOccupation AS
	BEGIN
		ALTER TABLE customers DROP COLUMN occupation
		PRINT 'Removed occupation column for customers'
	END
GO

EXEC addCustomersOccupation
EXEC removeCustomersOccupation

-- c)

INSERT INTO checkoutCounter (checkoutCounterId, cashInside) VALUES (6, 0)
select * from checkoutCounter
delete from checkoutCounter where checkoutCounter.checkoutCounterId = 6


CREATE PROCEDURE addIsActiveDefaultConstraint AS
	BEGIN
		ALTER TABLE checkoutCounter ADD CONSTRAINT DF_isActive DEFAULT 0 FOR isActive
		PRINT 'Added default constraint for isActive column'
	END
GO

CREATE PROCEDURE removeIsActiveDefaultConstraint AS
	BEGIN
		ALTER TABLE checkoutCounter DROP CONSTRAINT DF_isActive
		PRINT 'Removed default constraint from isActive column'
	END
GO

EXEC addIsActiveDefaultConstraint
EXEC removeIsActiveDefaultConstraint

-- d)

CREATE PROCEDURE removePrimaryKeyFromAdvertismentTable AS
	BEGIN
		ALTER TABLE Advertisment DROP CONSTRAINT Ad_Primary
		PRINT 'Removed primary key from Advertisment table'
	END
GO

CREATE PROCEDURE addPrimaryKeyToAdvertismentTable AS
	BEGIN
		ALTER TABLE Advertisment ADD CONSTRAINT Ad_Primary PRIMARY KEY (Id)
		PRINT 'Added primary key to Advertisment table'
	END
GO

EXEC removePrimaryKeyFromAdvertismentTable
EXEC addPrimaryKeyToAdvertismentTable

-- e)

CREATE PROCEDURE addProductNameAsCandidateKey AS
	BEGIN
		ALTER TABLE Advertisment ADD CONSTRAINT ProductName_CandidateKey UNIQUE (ProductName)
		PRINT 'Added product name as candidate key in the Advertisment table'
	END
GO

CREATE PROCEDURE removeProductNameAsCandidateKey AS
	BEGIN
		ALTER TABLE Advertisment DROP CONSTRAINT ProductName_CandidateKey
		PRINT 'Removed candidate key from Advertisment table'
	END
GO

EXEC addProductNameAsCandidateKey
EXEC removeProductNameAsCandidateKey

-- f)

CREATE PROCEDURE addAdvertismentForeignKey AS
	BEGIN
		ALTER TABLE Advertisment ADD CONSTRAINT pid_fk FOREIGN KEY (ProductId) REFERENCES products (productId)
		PRINT 'Added foreign key for Advertisment table'
	END
GO

CREATE PROCEDURE removeAdvertismentForeignKey AS
	BEGIN
		ALTER TABLE Advertisment DROP CONSTRAINT pid_fk
		PRINT 'Removed foreign key from Advertisment table'
	END
GO

EXEC addAdvertismentForeignKey
EXEC removeAdvertismentForeignKey

-- g)

CREATE PROCEDURE createParkingTable AS
	BEGIN
		CREATE TABLE Parking (
			AvailableSpaces INT,
			TotalSpaces INT,
			Id INT NOT NULL PRIMARY KEY
		)
		PRINT 'Created Parking table'
	END
GO

CREATE PROCEDURE dropParkingTable AS
	BEGIN
		DROP TABLE Parking
		PRINT 'Removed Parking table'
	END
GO

EXEC createParkingTable
select * from Parking
EXEC dropParkingTable

---------------
CREATE OR ALTER PROCEDURE createAdvertismentTable AS
	BEGIN
		CREATE TABLE Advertisment (
			ProductName VARCHAR(100) NOT NULL,
			ProductId INT,
			Discount FLOAT,
			Id INT NOT NULL
		)
		PRINT 'Created Advertisment table'
	END
GO

CREATE PROCEDURE dropAdvertismentTable AS
	BEGIN
		DROP TABLE Advertisment
		PRINT 'Deleted Advertisment table'
	END
GO

EXEC createAdvertismentTable
SELECT * FROM Advertisment
EXEC dropAdvertismentTable

--

CREATE TABLE Versions
	(CurrentProcedure VARCHAR(100),
	PreviousProcedure VARCHAR(100),
	versionId INT UNIQUE)
GO

INSERT INTO Versions (CurrentProcedure, PreviousProcedure, versionId) VALUES
('setIsActiveColumnFromBitToInt', 'revertIsActiveColumnFromIntToBit', 1),
('addCustomersOccupation', 'removeCustomersOccupation', 2),
('addIsActiveDefaultConstraint', 'removeIsActiveDefaultConstraint', 3),
('addPrimaryKeyToAdvertismentTable', 'removePrimaryKeyFromAdvertismentTable', 4),
('addProductNameAsCandidateKey', 'removeProductNameAsCandidateKey', 5),
('addAdvertismentForeignKey', 'removeAdvertismentForeignKey', 6),
('createParkingTable', 'dropParkingTable', 7)

CREATE TABLE CurrentVersion (
	cVersion INT DEFAULT 0
)

CREATE OR ALTER PROCEDURE goToVersion(@version INT) AS
	BEGIN
		DECLARE @currentVersion INT
		SET @currentVersion = (SELECT cVersion FROM CurrentVersion) 
		IF @version = @currentVersion 
			BEGIN
				PRINT 'We are already on this version!'
				RETURN
			END
		ELSE
		DECLARE @currentProcedure VARCHAR(50)
		IF @currentVersion < @version
			BEGIN
				WHILE @currentVersion < @version
					BEGIN
						SET @currentProcedure = (SELECT CurrentProcedure
												FROM Versions
												WHERE versionId = @currentVersion + 1)
						EXEC(@currentProcedure)
						SET @currentVersion = @currentVersion + 1
					END
			END
		ELSE
			BEGIN
				WHILE @currentVersion > @version
					BEGIN
						SET @currentProcedure = (SELECT PreviousProcedure
												FROM Versions
												WHERE versionId = @currentVersion)
						EXEC(@currentProcedure)
						SET @currentVersion = @currentVersion - 1

					END
			END
		UPDATE CurrentVersion
		SET cVersion = @currentVersion
		PRINT 'Updated version!'
	END
GO

INSERT INTO CurrentVersion VALUES (0)
SELECT * FROM CurrentVersion

EXEC goToVersion 3
EXEC goToVersion 0
EXEC goToVersion 7
EXEC goToVersion 5
EXEC goToVersion 2

select * from customers