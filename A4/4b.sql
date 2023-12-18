--creation of table
create table area
(radius int,
 area float
);


--procedure for area calculation
delimiter //
create procedure calc_area()
begin
declare r int;
declare a float;

set a = 0.0;
set r = 5;

while (r < 10) do
set a = 3.14 * r * r;
insert into area values (r,a);
set r = r + 1;
end while;

end
//
delimiter ;

--invoking the created procedure
call calc_area();
