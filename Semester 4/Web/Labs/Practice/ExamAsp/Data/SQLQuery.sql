create database OrdersApp
go

use OrdersApp
go

create table Users(
	Username nvarchar(100) primary key,
	UserId int unique
)

drop table Users

create table Products(
	ProductId int primary key identity (1, 1),
	ProductName nvarchar(100) not null,
	Price float not null
)
drop table Orders
create table Orders(
	OrderId int primary key identity (1, 1),
	UserId int foreign key references Users(UserId),
	TotalPrice float not null
)
drop table OrderItems
create table OrderItems(
	OrderItemId int primary key identity (1, 1),
	OrderId int foreign key references Orders(OrderId),
	ProductId int foreign key references Products(ProductId)
)

insert into Users values ('Alex', 1), ('Denis', 2)

select * from Users

insert into Products values ('BOOK-Math', 25.25), ('TOY-Car', 30)

select * from Products
delete from Products
insert into Orders values (1, 25.25), (2, 25.25)
delete from Orders
select * from Orders

insert into OrderItems values (1, 1), (2, 1)
delete From OrderItems
select * from OrderItems
