--Create procedure 5: pro_enroll
select * from enrolled;
create or replace procedure pro_enroll(sname_in IN varchar, cname IN varchar) as

student_num number;

begin
	select s.snum into student_num from student s where s.sname = sname_in;
	insert into ENROLLED values (student_num, cname);
end pro_enroll;
/

--run procedure
begin
	pro_enroll('M.Lee', 'CS448');
	pro_enroll('A.Smith', 'ENG320');
end;
/
select * from enrolled;