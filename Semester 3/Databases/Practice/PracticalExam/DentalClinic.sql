use DentalClinic
go

create table Patients (
	PatientID int primary key identity (1, 1),
	PatientName varchar(50) unique,
	PhoneNumber varchar(50),
	Email varchar(50),
	Addr varchar(50)
)

create table TreatmentPlans (
	TreatmentID int primary key identity (1, 1),
	TreatmentName varchar(50) unique,
	Duration int,
	Fee int
)


create table Services (
	ServiceID int primary key identity (1, 1),
	ServiceName varchar(50) unique,
	ServiceFee float,
	TreatmentID int foreign key references TreatmentPlans(TreatmentID)
)

create table Appointments (
	AppointmentID int primary key identity (1, 1),
	AppointmentDate date,
	AppointmentTime time,
	Information varchar(50),
	TreatmentID int foreign key references TreatmentPlans(TreatmentID),
	PatientID int foreign key references Patients(PatientID)
)

create table Dentists (
	DentistID int primary key identity (1, 1),
	DentistName varchar(50) unique,
	PhoneNumber varchar(50),
	Email varchar(50),
	AppointmentID int foreign key references Appointments(AppointmentID)
)

create table DentistTreatmentPlan (
	DTPID int primary key identity (1, 1),
	DentistID int foreign key references Dentists(DentistID),
	TreatmentID int foreign key references TreatmentPlans(TreatmentID)
)

-- Implement a stored procedure that receives the details of a patient and
--  adds the patient in the database. If there is already a patient with the 
--  same name, the procedure should return an error message and it
--  should not add the patient in the database.

create or alter procedure spAddPatient
	@PatientName varchar(50),
	@Phone varchar(50),
	@Email varchar(50),
	@Addr varchar(50)
as
begin
	if exists (select * from Patients
				where Patients.PatientName = @PatientName)
	begin
		raiserror('Patient already exists', 16, 1)
	end
	else
	begin
		insert into Patients values (@PatientName, @Phone, @Email, @Addr)
	end
end
go

select * from Patients
exec spAddPatient 'Andrei', '0747345829', 'andreigaming252@gmail.com', 'Str. Hasdeu nr. 51'

-- create a view that displays the name of the patients that have appointments
-- scheduled for february 2024

create or alter view vPatientsAppointmentFeb2024
as
	select p.PatientName
	from Patients p
	where p.PatientID in (
		select a.PatientID
		from Appointments a
		where a.AppointmentDate like '2024-02-%'
		)
go

select * from vPatientsAppointmentFeb2024

select * from Patients
select * from Appointments
select * from TreatmentPlans

insert into TreatmentPlans values ('Tratament1', 5, 10)
insert into Appointments values ('2024-02-25', '20:00:00', 'pt andrei', 1, 1)

-- implement a function that returns the dentist with the highest number of treatment plans
-- prescribed during appointments within a time period. The period of time is represented by a
-- start time and end time, which are function parameters. 

go
create or alter function fnGetDentistWithHighestNumberOfTreatmentPlans
	(@StartTime time, @EndTime time)
returns varchar(50)
as
begin
	declare @DentistName varchar(50)
	select top 1 @DentistName = d.DentistName
	from Dentists d
	join DentistTreatmentPlan dt on d.DentistID = dt.DentistID
	join TreatmentPlans tp on dt.TreatmentID = tp.TreatmentID
	join Appointments a on tp.TreatmentID = a.TreatmentID
	where a.AppointmentTime >= @StartTime and a.AppointmentTime <= @EndTime
	group by d.DentistName
	order by count(*) desc
	return @DentistName
end
go

insert into TreatmentPlans values ('T2', 1, 1), ('T3', 1, 1), ('T4', 1, 1)
select * from TreatmentPlans
insert into Appointments values ('2024-02-25', '19:00:00', 'info', 1, 1)
select * from Appointments

insert into Dentists values ('D1', '', '', 7), ('D2', '', '', 6)
select * from Dentists

insert into DentistTreatmentPlan values (1, 1), (2, 4), (1, 3)
select * from DentistTreatmentPlan

select dbo.fnGetDentistWithHighestNumberOfTreatmentPlans('2024-02-23', '2024-02-26')
