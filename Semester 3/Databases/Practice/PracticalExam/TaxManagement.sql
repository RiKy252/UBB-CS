use TaxManagement
go

create table TaxCompany (
	TaxCompanyID int primary key identity (1, 1),
	TaxCompanyName varchar(50),
	NrClients int,
	NrSRLs int
)

create table Clients (
	ClientID int primary key identity (1, 1),
	ClientName varchar(50),
	MoneySent float,
	TaxCompanyID int foreign key references TaxCompany(TaxCompanyID)
)

create table Assets (
	AssetID int primary key identity (1, 1),
	AssetName varchar(50),
	NrAssets int,
	Loc varchar(50),
	ClientID int foreign key references Clients(ClientID)
)

create table SRLs (
	SRLID int primary key identity (1, 1),
	SRLName varchar(50),
	Activity varchar(50),
	Loc varchar(50),
	ClientID int foreign key references Clients(ClientID)
)

select * from TaxCompany
select * from Clients
select * from Assets
select * from SRLs

insert into TaxCompany values ('Ionut', 5, 5)
insert into Clients values ('Anghel', 1000, 1)
insert into Assets values ('Anghel1Asset', 3, 'homeless', 1)
insert into SRLs values ('Anghel1SRL', 'act1', 'hmls1', 1), ('Anghel2SRL', 'act2', 'hmls2', 1)

-- Implement a stored procedure that receives a client and returns the 
-- number of assets owned and the number of SRLs opened in his name

go
create or alter procedure ClientAssetsAndSRLs @ClientID int
as
	declare @noAssets int
	declare @noSRLs int
	set @noAssets = 0
	set @noSRLs = 0
	select @noAssets = count(*)
	from Assets a
	where a.ClientID = @ClientID

	select @noSRLs = count(*)
	from SRLs s
	where s.ClientID = @ClientID
	print @noAssets
	print @noSRLs
go

exec ClientAssetsAndSRLs 1

-- Create a view that shows clients id and money owned
-- also the name and activity of all SRLs opened in his name

go
create or alter view vClientSRLsActivity
as
	select c.ClientID, c.MoneySent, s.SRLName, s.Activity
	from Clients c, SRLs s
	where s.ClientID = c.ClientID
go

select * from vClientSRLsActivity

-- Implement a function that lists the identification numbers of the 
-- clients and the location of all the SRLs opened in his name and in addition
-- the number of assets for each SRL

go
create function uf_ListClientSRLLocationsNrAssets()
returns table
as
return
	select c.ClientID, s.Loc, a.NrAssets
	from Clients c, SRLs s, Assets a
go

select * from uf_ListClientSRLLocationsNrAssets()