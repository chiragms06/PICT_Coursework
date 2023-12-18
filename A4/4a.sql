--creation of tables
create table borrower
(rollno int primary key,
 name varchar(20),
 date_of_issue date,
 book_name varchar(20),
 status char(2)
);

create table fine
(rollno int primary key,
 fine_date date,
 fine_amt int
);


--insertion of records
insert into borrower values
(1,'abc','2023-08-15','Harry Potter','I'),
(2,'pqr','2023-07-31','Goosebumps','I'),
(3,'xyz','2023-08-05','Atomic Habits','I');


--procedure for fine calculation
delimiter //
create procedure calcfine(in rno int,in bname varchar(20))
begin
declare fineamt int;
declare issuedate date;
declare numdays int;
declare dup int;

declare continue handler for 1062
set dup=1;

declare exit handler for not found
select 'Not found' as NFMessage;

select date_of_issue into issuedate from borrower where rollno=rno and book_name=bname;
set numdays=datediff(curdate(),issuedate);

set fineamt=0;
set dup=0;

if numdays>15 and numdays<30 then
set fineamt=5*numdays;
elseif numdays>30 then
set fineamt=50*(numdays-30)+5*30;
end if;

update borrower set status='R' where rollno=rno and book_name=bname;
insert into fine values(rno,curdate(),fineamt);

if dup=1 then
begin
set dup=0;
select 'Duplicate entry !' as DupMessage;
end;
end if;

end
//
delimiter ;


--invoking the created procedure
call calcfine(1,'Harry Potter');

call calcfine(3,'Atomic Habits');
