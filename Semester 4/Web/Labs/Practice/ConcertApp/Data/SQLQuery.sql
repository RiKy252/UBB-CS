create database ConcertReservationDB
go

use ConcertReservationDB
go

create table Flights(
	FlightId int primary key identity (1, 1),
	Date Date not null,
	DestinationCity nvarchar(100) not null,
	AvailableSeats int not null
);
go

create table Hotels(
	HotelId int primary key identity (1, 1),
	HotelName nvarchar(100) not null,
	Date Date not null,
	City nvarchar(100) not null,
	AvailableRooms int not null
);
go

create table Reservations(
	Id int primary key identity (1, 1),
	Person nvarchar(100) not null,
	Type nvarchar(10) not null check (Type in ('Flight', 'Hotel')),
	IdReservedResource int not null
);
go

INSERT INTO Flights (Date, DestinationCity, AvailableSeats) VALUES
('2025-07-01', 'New York', 5),
('2025-07-01', 'New York', 3),
('2025-07-01', 'Chicago', 4),
('2025-07-02', 'New York', 6),
('2025-07-01', 'Los Angeles', 2);
GO

INSERT INTO Hotels (HotelName, Date, City, AvailableRooms) VALUES
('Hilton NY', '2025-07-01', 'New York', 5),
('Marriott NY', '2025-07-01', 'New York', 4),
('Holiday Inn Chicago', '2025-07-01', 'Chicago', 6),
('Hyatt NY', '2025-07-02', 'New York', 2),
('LA Grand Hotel', '2025-07-01', 'Los Angeles', 3);
GO

SELECT * FROM Flights;
SELECT * FROM Hotels;
select * from Reservations
