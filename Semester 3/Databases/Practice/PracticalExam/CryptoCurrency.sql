create database CryptoCurrency
go

use CryptoCurrency
go

create table Clients (
	ClientID int primary key identity (1, 1),
	ClientName varchar(50),
)

create table Accounts (
	AccountID int primary key identity (1, 1),
	ClientID int foreign key references Clients(ClientID),
	InvestingMoney float
)

create table Cryptos (
	CryptoID int primary key identity (1, 1),
	CryptoType varchar(50)
)

insert into Cryptos values ('Bitcoin'), ('Ethereum'), ('Dodgecoin')
select * from Cryptos

create table Transactions (
	TransactionID int primary key identity (1, 1),
	AccountID int foreign key references Accounts(AccountID),
	CryptoID int foreign key references Cryptos(CryptoID),
	TransactionType varchar(50),
	Price float
)

create table Stats (
	StatisticID int primary key identity (1, 1),
	AccountID int foreign key references Accounts(AccountID),
	noBuyOrders int default 0,
	noSellOrders int default 0,
	noOperations int default 0,
	MoneyLeft float
)

