--creation of tables
create table library
(b_id int primary key,
 b_name varchar(20)
);

create table library_audit
(b_id int primary key,
 b_name varchar(20)
);


--insertion of records
insert into library values
(1,'abc'),
(2,'pqr'),
(3,'xyz'),
(4,'rst');


--triggers
--update trigger
delimiter //
create trigger updTrig
before update on library
for each row
begin
insert into library_audit values(old.b_id,old.b_name);
end;
//

--delete trigger
delimiter //
create trigger delTrig
before delete on library
for each row
begin
insert into library_audit values(old.b_id,old.b_name);
end;
//

--insert trigger
delimiter //
create trigger insTrig
after insert on library
for each row
begin
insert into library_audit values(new.b_id,new.b_name);
end;
//

delimiter ;
