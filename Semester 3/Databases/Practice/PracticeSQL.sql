use Practice
go

create table S(
	sid varchar(10) primary key,
	a varchar(10),
	b varchar(10),
	c varchar(50),
	d int,
	e int,
	f int
)

insert into S values ('t1', 'a1', 'b2', 'c1', 0, 1, 0), ('t2', 'a1', 'b2', 'c2', 1, 2, 1), ('t3', 'a1', 'b3', 'c3', 0, 3, 0), ('t4', 'a1', 'b3', 'c4', 2, 123, -1), ('t5', 'a1', 'b3', 'c5', -1, 4, -1)

select * from S

select b,c,count(*)
from S
group by b,c
having d <= 1

create table R(
	RID int primary key,
	M varchar(50) not null,
	N varchar(50) not null,
	P int not null,
	Q int,
	O int
)

insert into R values (10, 'negru', 'toti', 20, 1, 10), (1, 'voda', 'voinici', 21, 1, 5), (2, 'si-a', 'cu', 22, 1, null), (11, 'lui', 'fruntea', 23, 1, null), (3, 'ceata', 'lata', 24, 1, 2)

select * from R

select avg(P)
from R
group by P
having avg(p) > 10

select *
from R
where M is null

select M, P from R
select distinct M, P from R

select * from R
where Q is not null

select count(r1.RID) NoRows
from R r1
where r1.P < ANY (select r3.P
				  from R r2 full outer join R r3
				  on r2.RID = r3.RID
				  group by r3.P)

select *
from R r1
where r1.P > any (select r2.P
			      from R r2)

select avg(r1.P) avgP
from R r1
where r1.RID not in (1, 2, 10)
group by r1.Q
having avg(r1.P) > any
(select avg(r2.Q)
from R r2
group by r2.P)

select * from R


