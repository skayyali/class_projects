set serveroutput on size 32000
--Create procedure 1: pro_department_report
create or replace procedure pro_department_report as

CURSOR dept_list is select deptid, dname from department order by dname;
CURSOR student_list is select sname, deptid from student order by sname;

begin
	for i in dept_list loop
		dbms_output.put_line('Department: '|| ' ' || i.dname);	
		dbms_output.put_line('-------------');
		for j in student_list loop
			if j.deptid = i.deptid then
				dbms_output.put_line(j.sname);
			end if;
		end loop;
		dbms_output.put_line(CHR(10));
	end loop;
end pro_department_report;
/
--run procedure
begin
pro_department_report;
end;
/

--Create procedure 2: pro_student_stats
create or replace procedure pro_student_stats as


CURSOR enroll_list is select snum, count(*) as num from enrolled group by snum;
CURSOR student_list is select sname, snum from student order by sname;

begin
	dbms_output.put_line('Student Name - #Classes');
	dbms_output.put_line('-----------------------');
	for i in student_list loop
		for j in enroll_list loop
			if i.snum = j.snum then
				dbms_output.put_line(i.sname|| ' - ' || j.num);
			end if;
		end loop;
	end loop;
end pro_student_stats;
/
--run procedure
begin
pro_student_stats;
end;
/

--Create procedure 3: pro_faculty_stats
create or replace procedure pro_faculty_stats as

CURSOR faculty_list is select f.fname, coalesce(tab.num, 0) as num
						from faculty f left join
						(select c.fid, count(e.snum) as num
							from class c left join enrolled e on c.cname = e.cname group by c.fid)
						tab on f.fid = tab.fid order by f.fname;

begin
	dbms_output.put_line('Faculty name - #Students ');
	dbms_output.put_line('-----------------------');
	for i in faculty_list loop
		dbms_output.put_line(i.fname|| ' - ' || i.num);
	end loop;
end pro_faculty_stats;
/

--run procedure
begin
pro_faculty_stats;
end;
/

--Create procedure 4: pro_histogram
create or replace procedure pro_histogram as

max_age number;
min_age number;

s_age number;
age_count number;
CURSOR student_list is select age, count(snum) as cnt from student group by age order by age;

begin
	open student_list;
	select max(age) into max_age from student;
	select min(age) into min_age from student;
	fetch student_list into s_age, age_count;
	dbms_output.put_line('Age'|| ' | ' || 'number of students');
	for i in min_age..max_age loop
		if s_age = i then
			dbms_output.put_line(s_age|| '  | ' || age_count);
			fetch student_list into s_age, age_count;
		else
			dbms_output.put_line(i|| '  | ' || '0');
		end if;
	end loop;
	close student_list;
end pro_histogram;
/

--run procedure
begin
pro_histogram;
end;
/


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