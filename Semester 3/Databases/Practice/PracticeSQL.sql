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
