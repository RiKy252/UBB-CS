use Shoes
go

-- a)

create table PresentationShop(
	PresentationShopID int primary key identity(1, 1),
	PresentationShopName varchar(255),
	PresenationShopCity varchar(255)
)

create table Women(
	WomanID int primary key identity(1, 1),
	WomanName varchar(255),
	MaximumAmountToSpend float
)

create table ShoeModels(
	ShoeModelID int primary key identity(1, 1),
	ShoeModelName varchar(255),
	ShoeModelSeason varchar(255)
)

create table Shoes(
	ShoeID int primary key identity(1, 1),
	ShoePrice float,
	ShoeModelID int foreign key references ShoeModels(ShoeModelID)
)

create table PresentationShopShoes(
	PresentationShopID int foreign key references PresentationShop(PresentationShopID),
	ShoeID int foreign key references Shoes(ShoeID),
	primary key (PresentationShopID, ShoeID),
	AvailableShoes int
)

create table WomenShoes(
	WomanID int foreign key references Women(WomanID),
	ShoeID int foreign key references Shoes(ShoeID),
	primary key (WomanID, ShoeID),
	BoughtShoes int,
	SpentAmount float
)

insert into Women values ('Diana', 505.3);
insert into ShoeModels values ('AF1', 'Summer');
insert into Shoes values (500.1, 1);
insert into PresentationShop values ('Buzz', 'Bacau');

select * from Women
select * from Shoes
select * from ShoeModels
select * from PresentationShop

-- b)

go
create procedure Add_Shoe @ShoeID int, @PresentationShopID int , @NoOfShoes int
as
	insert into PresentationShopShoes values (@PresentationShopID, @ShoeID, @NoOfShoes);
go

exec Add_Shoe 1, 1, 25;
select * from PresentationShopShoes

-- c)

go
create or alter view vWomenBought2AirForces
as
	select w.WomanName, s.ShoeModelID
	from Women w
	join WomenShoes ws on w.WomanID = ws.WomanID
	join Shoes s on ws.ShoeID = s.ShoeID
	group by w.WomanName, s.ShoeModelID
	having sum(ws.BoughtShoes) >= 2 and s.ShoeModelID = 1;
go

select * from WomenShoes
select * from Women
select * from Shoes

insert into Shoes values (255.4, 1);
insert into Shoes values (321.76, 1);

insert into Women values ('Alexia', 1023.34);
insert into Women values ('Miruna', 921.6);

insert into WomenShoes values (1, 2, 1, 255.4), (2, 3, 1, 0), (2, 1, 1, 0), (3, 2, 2, 0);

select * from vWomenBought2AirForces;

-- d)

select * from PresentationShop
select * from Shoes
select * from PresentationShopShoes

go
create or alter function uf_ListShoesFoundInTPresentationShops(@T int)
returns table
as
return
	select s.ShoeID
	from Shoes s
	join PresentationShopShoes pss on s.ShoeID = pss.ShoeID
	group by s.ShoeID
	having count(distinct pss.PresentationShopID) >= @T
go

select * from uf_ListShoesFoundInTPresentationShops(1);
