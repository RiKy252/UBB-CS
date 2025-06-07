CREATE DATABASE MiniFacebook
GO

USE MiniFacebook
GO

create table Users(
Uidd int primary key identity(1, 1),
UName VARCHAR(50),
UCity VARCHAR(50),
UDob DATE
)

create table Categories(
Cid int primary key identity(1, 1),
CName VARCHAR(50),
CDescription VARCHAR(50)
)

create table Pages(
Pid int primary key identity(1, 1),
PName VARCHAR(50),
Cid INT FOREIGN KEY REFERENCES Categories(Cid)
)

create table Likes(
Uidd int references Users(Uidd),
Pid int references Pages(Pid),
LikeDate date,
CONSTRAINT PK_LIKES PRIMARY KEY(Uidd, Pid)
)

create table Posts(
Poid int primary key identity(1, 1),
PoDate date,
PoText VARCHAR(50),
NoOfShares int,
Uidd int foreign key references Users(Uidd)
)

create table Comments(
Coid int primary key identity(1, 1),
CoDate date,
CoText VARCHAR(50),
CoFlagTop bit,
Poid int foreign key references Posts(Poid)
)

INSERT Users VALUES('User 1', 'Cluj-Napoca', '10/10/2000'), ('User 2', 'Bucuresti', '2/2/1998')
INSERT Categories VALUES('Category 1', 'very interesting'), ('Category 2', 'interesting')
INSERT Pages VALUES('Page 1', 1), ('Page 2', 1)
INSERT Likes VALUES(1,1,'2/21/2018'), (1,2,'6/7/2018'), (2,1, '2/3/2017')
INSERT Posts VALUES ('1/1/2018', 'Post 1', 3, 1), ('3/23/2018', 'Post 2',5, 2)
insert Comments values ('6/8/2019','comment 1', 1,1), ('6/9/2017', 'commmmmmm', 0,2)

select * from Users
select * from Categories
select * from Pages
select * from Likes
select * from Posts
select * from Comments
