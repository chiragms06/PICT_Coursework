# Database Management Systems Laboratory

## Group A - SQL and PL/SQL

### A1 - ER Modeling and Normalization
Decide a case study related to real time application in group of 2-3 students and formulate a
problem statement for application to be developed. Propose a Conceptual Design using ER
features using tools like ERD plus, ER Win etc. (Identifying entities, relationships between
entities, attributes, keys, cardinalities, generalization, specialization etc.) Convert the ER diagram
into relational tables and normalize Relational data model.

### A2 - SQL Queries (all CRUD operations)
a. Design and Develop SQL DDL statements which demonstrate the use of SQL objects such
as Table, View, Index, Sequence, Synonym, different constraints etc.
b. Write at least 10 SQL queries on the suitable database application using SQL DML
statements.

### A3 - SQL Queries (all types of Join, Sub-Query and View)
Write at least 10 SQL queries for suitable database application using SQL DML statements.

### A4 - Unnamed PL/SQL code block (use of Control structure and Exception handling is mandatory)
Consider Tables:
1. Borrower(Roll_no, Name, DateofIssue, NameofBook, Status)
2. Fine(Roll_no,Date,Amt)
 Accept Roll_no and NameofBook from user.
 Check the number of days (from date of issue).
 If days are between 15 to 30 then fine amount will be Rs 5per day.
 If no. of days>30, per day fine will be Rs 50 per day and for days less than 30, Rs. 5 per
day.
 After submitting the book, status will change from I to R.
 If condition of fine is true, then details will be stored into fine table.
 Also handles the exception by named exception handler or user define exception handler.
OR
Write a PL/SQL code block to calculate the area of a circle for a value of radius varying from 5 to
9. Store the radius and the corresponding values of calculated area in an empty table named areas,
consisting of two columns, radius and area.

### A5 - Named PL/SQL Block (PL/SQL Stored Procedure and Stored Function)
Write a Stored Procedure namely proc_Grade for the categorization of student. If marks scoredby
students in examination is <=1500 and marks>=990 then student will be placed in distinction
category if marks scored are between 989 and 900 category is first class, if marks 899 and 825
category is Higher Second Class.
Write a PL/SQL block to use procedure created with above requirement.
Stud_Marks(roll, name, total_marks) Result(Roll, Name, Class)

### A6 - Cursors (all types: Implicit, Explicit, Cursor FOR Loop, Parameterized Cursor)
Write a PL/SQL block of code using parameterized Cursor that will merge the data availablein
the newly created table N_RollCall with the data available in the table O_RollCall. If the data in
the first table already exist in the second table then that data should be skipped.

### A7 - Database Trigger (all Types: Row level and Statement level triggers, Before and After Triggers)
Write a database trigger on Library table. The System should keep track of the records that are
being updated or deleted. The old value of updated or deleted records should be added in
Library_Audit table.

### A8 - Database Connectivity
Write a program to implement MySQL/Oracle database connectivity with any front end
language to implement Database navigation operations (add, delete, edit etc.).

## Group B - NOSQL

### B1 - MongoDB Queries
Design and Develop MongoDB Queries using CRUD operations. (Use CRUD operations,
SAVE method, logical operators etc.).

### B2 - MongoDB (Aggregation and Indexing)
Design and Develop MongoDB Queries using aggregation and indexing with suitable example
using MongoDB.

### B3 - MongoDB (Map reduces operations)
Implement Map reduces operation with suitable example using MongoDB.

### B4 - Database Connectivity
Write a program to implement MongoDB database connectivity with any front end language to
implement Database navigation operations (add, delete, edit etc.)
