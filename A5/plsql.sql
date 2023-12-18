--creation of tables
create table student
(rollno int primary key,
 name varchar(20),
 marks int
);

create table result
(rollno int primary key,
 category varchar(20)
);


--stored function for category
delimiter //
create function getCategory(marks int)
returns varchar(20)
deterministic
begin
  
declare category varchar(20);

if marks>=990 and marks<=1500 then
set category='Distinction';
elseif marks>=900 and marks<=989 then
set category='First Class';
elseif marks>=825 and marks<=899 then
set category='Higher Second Class';
else
set category='Pass';
end if;

return category;

end;
//
delimiter ;


--stored procedure for insertion of records
delimiter //
create procedure addData(in rollno int,in name varchar(20),in marks int)
begin
  
insert into student values(rollno,name,marks);
insert into result values(rollno,getCategory(marks));

end;
//
delimiter ;


--invoking the created procedure
call addData(1,'abc',1250);

call addData(2,'pqr',950);

call addData(3,'xyz',840);

call addData(4,'rst',798);
