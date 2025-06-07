create database Altex
go

use Altex
go

create table Customers(
Cid int primary key identity(1, 1),
Cname varchar(50),
CDob date,
Cemail varchar(100),
Cphone varchar(50),
Caddress varchar(50)
)

create table Categories(
Ctid int primary key identity(1, 1),
Ctname varchar(50)
)

create table Distributors(
Did int primary key identity(1, 1),
Dname varchar(50),
Dphone varchar(50),
Demail varchar(100)
)

create table Products(
Pid int primary key identity(1, 1),
Ctid int foreign key references Categories(Ctid),
Did int foreign key references Distributors(Did),
Pname varchar(50),
Pdescription varchar(50),
Pprice float,
Pstock int
)

create table Orders(
Cid int references Customers(Cid),
Pid int references Products(Pid),
Oquantity int,
Oprice float,
constraint PK_Orders primary key(Cid, Pid)
)

create table Payments(
Cid int references Customers(Cid),
Pid int references Products(Pid),
Pmethod varchar(50),
Pdate date,
Pstatus varchar(50),
constraint PK_Payments primary key(Cid, Pid)
)

select * from Categories
select * from Distributors
select * from Payments
select * from Orders
select * from Products
select * from Customers

insert into Categories values ('Electronics'), ('It'), ('Home')
insert into Distributors values ('Distributor 1', 'Distributor 1 phone number', 'Distributor 1 email'), ('Distributor 2', 'Distributor 2 phone number', 'Distributor 2 email')
insert into Products values (1, 1, 'Electronic product', 'Electronic description', 252.23, 125), (2, 1, 'It product', 'It description', 653.99, 225), (3, 2, 'Home product', 'Home description', 2050.35, 100)
insert into Customers values ('Josh', '2/21/2005', 'josh@test.com', '0725252525', 'Str. Asds 9'), ('Ioan', '5/11/2003', 'ioan@test.com', '0725252523', 'Str. Obor 23'), ('Liviu', '1/16/2008', 'liviu@test.com', '0725252521', 'Str. Piezisa 9')
insert into Orders values (1, 1, 2, 504.46), (1, 2, 1, 653.99), (2, 1, 2, 504.46), (3, 3, 1, 2050.35)
