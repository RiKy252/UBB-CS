drop database Seminar6
go

create database Seminar6
go

use Seminar6
go

create table Stations (
	Sid int primary key identity (1, 1),
	SName varchar(50) unique
)

create table TrainTypes (
	Typeid int primary key identity (1, 1),
	Description varchar(50)
)

create table Trains (
	Tid int primary key identity (1, 1),
	TName varchar(50),
	Typeid int foreign key references TrainTypes(Typeid)
)

create table Routes (
	Rid int primary key identity (1, 1),
	RName varchar(50) unique,
	Tid int foreign key references Trains(Tid)
)

create table RoutesStations (
	Rid int foreign key references Routes(Rid),
	Sid int foreign key references Stations(Sid),
	ArrivalTime time,
	DepartureTime time,
	constraint pk_RoutesStations primary key (Rid, Sid)
)
go

insert into TrainTypes values ('description 1'), ('description 2')
insert into Trains values ('InterRegio', 1), ('InterCity', 1), ('Regio', 2)
insert into Stations values ('Cluj-Napoca'), ('Brasov'), ('Bucuresti')
insert into Routes values ('Sighisoara', 1), ('Medias', 2)
insert into RoutesStations values (1, 1, '12:00:00', '18:00:00'), (1, 2, '15:30:00', '22:42:00'), (2, 2, '08:05:00', '21:48:00')
go

select * from TrainTypes
select * from Trains
select * from Stations
select * from Routes
select * from RoutesStations

go
create proc Add_Stops @Rid int, @Sid int, @at time, @dt time
as
	declare @nr int;
	set @nr = 0;
	select @nr = count(*) from RoutesStations where Rid = @Rid and Sid = @Sid
	if (@nr <> 0) begin
		update RoutesStations
		set ArrivalTime = @at, DepartureTime = @dt
		where Rid = @Rid and Sid = @Sid
	end
	else begin
		insert into RoutesStations values (@Rid, @Sid, @at, @dt)
	end
go

exec Add_Stops 2, 1, '05:00:00', '09:00:00'
select * from RoutesStations
exec Add_Stops 2, 1, '10:00:00', '19:00:00'

create view vRouteContainingAllStations
as
	select RName
	from Routes r inner join RoutesStations rs on r.Rid = rs.Rid
	group by RName
	having count(*) = (select count(*) from Stations)

select * from Routes
select * from RoutesStations
select * from Stations
insert into RoutesStations values (1, 3, '12:00:00', '18:00:00')
select * from vRouteContainingAllStations

create function uf_StationsRoutes(@r int)
returns table
as
return
	select distinct s.Sid, SName, count(SName) as noOfRoutes
	from Stations s inner join RoutesStations ss on ss.Sid = s.Sid
	group by s.Sid, SName
	having count(SName)>=@r

select * from uf_StationsRoutes(1)