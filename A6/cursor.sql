--creation of tables
create table o_call
(rollno int primary key,
 name varchar(20)
);

create table n_call
(rollno int primary key,
 name varchar(20)
);


--insertion of records
insert into o_call values
(1,'abc'),
(2,'pqr'),
(3,'xyz'),
(4,'rst');

insert into n_call values
(1,'abc'),
(3,'xyz');


--stored procedure containing an explicit cursor
DELIMITER //
CREATE PROCEDURE mergedata()
BEGIN
    DECLARE rno INT;
    DECLARE naam VARCHAR(20);
    DECLARE dup INT;
    DECLARE flag INT;
    DECLARE c1 CURSOR FOR SELECT * FROM o_call;
    
    DECLARE CONTINUE HANDLER FOR 1062
        SET dup = 1;
    
    DECLARE CONTINUE HANDLER FOR NOT FOUND
        SET flag = 1;

    SET dup = 0;  
    
    OPEN c1;
    
    l1: LOOP
        FETCH c1 INTO rno, naam;
        
        IF flag = 1 THEN
            LEAVE l1;
        END IF;

        INSERT INTO n_call VALUES (rno, naam);

        IF dup = 1 THEN
            BEGIN
                SET dup = 0;
                SELECT 'Duplicate record ignored' AS Message; 
            END;
        END IF;
    END LOOP l1;

    CLOSE c1;
END //
DELIMITER ;


--invoking the created procedure
call mergedata();
