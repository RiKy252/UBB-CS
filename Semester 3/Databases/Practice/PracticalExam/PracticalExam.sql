use PracticalExam
go

create table CarBrand (
	CarBrandID int primary key identity(1, 1),
	CarBrandName varchar(255),
)

create table CarType (
	CarTypeID int primary key identity(1, 1),
	CarTypeModel varchar(255),
	NumberOfModels int,
	CarBrandID int foreign key references CarBrand(CarBrandID)
)

insert into CarBrand values ('Audi'), ('BMW'), ('Dacia');

select * from CarBrand

insert into CarType values ('Sport', 25, 2), ('SUV', 35, 1), ('Sedan', 50, 3);

select * from CarType

create table CarParts (
	CarPartID int primary key identity(1, 1),
	CarPartName varchar(255),
	Price float,
	CarTypeID int foreign key references CarType(CarTypeID),
	CarBrandID int foreign key references CarBrand(CarBrandID)
)

create table Factory (
	FactoryID int primary key identity(1, 1),
	FactoryName varchar(255),
	CarBrandID int foreign key references CarBrand(CarBrandID)
)

drop table Factory
drop table CarParts
drop table CarType
drop table CarBrand

-- 2.

select * from CarBrand
select * from CarType
select * from Factory

insert into Factory values ('Factory1', 2);
insert into Factory values ('Factory2', 1);

go
create or alter procedure FactoryBrandSports @FactoryID int
as
	select f.FactoryName, cb.CarBrandName
	from Factory f, CarBrand cb
	where f.FactoryID = @FactoryID and cb.CarBrandID = f.CarBrandID
	
go

exec FactoryBrandSports 1

-- 3.

go
create or alter view vCarModelsAudi
as
	select ct.CarTypeModel, cp.CarPartName
	from CarType ct, CarParts cp
	where ct.CarBrandID = 1 and cp.price > 1
	
go

select * from CarParts

select * from vCarModelsAudi
	
