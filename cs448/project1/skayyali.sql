rem CS448 SQL Project 1
rem Said Kayyali
rem skayyali@purdue.edu

/* ######### PART 1: SQL QUERIES ######### */

rem Query1
SELECT EmpName
FROM Employee
WHERE HomeZipCode=47906 OR HomeZipCode=47907;


rem Query2
SELECT p.ProjName
FROM Project p, ProjectManager pm
WHERE p.ProjId=pm.ProjId AND EndDate IS NULL;


rem Query3
WITH Counts AS (
	SELECT ProjId, COUNT(EmpId) AS COUNT FROM EmpProject GROUP BY ProjId
)
SELECT p.ProjName, c.Count
FROM Project p, Counts c
WHERE c.ProjID=p.ProjID;


rem Query4
WITH list AS (SELECT DISTINCT * FROM Graduate WHERE (Graduate.EmpId IN (SELECT DISTINCT MgrId FROM ProjectManager))),
	list2 AS(SELECT UnivId, COUNT(*) AS num FROM list GROUP BY UnivId HAVING COUNT(*) = (SELECT MAX(COUNT(EmpId)) FROM list GROUP BY UnivId))
SELECT u.UnivName FROM University u, list2 l WHERE u.UnivId = l.UnivId;


rem Query5
SELECT e.EmpName, d.DeptName, g.GradYear FROM Employee e INNER JOIN Department d ON e.DeptId=d.DeptId INNER JOIN Graduate g ON e.EmpId=g.EmpId;
						
						
rem Query6
WITH list AS (SELECT DISTINCT EmpId, ProjId FROM EmpProject),
	list2 AS (SELECT ProjId, COUNT(*) AS num FROM list GROUP BY ProjId HAVING COUNT(*) = (SELECT MAX(COUNT(EmpId)) FROM list GROUP BY ProjId))
SELECT p.Projname FROM Project p, list2 l WHERE p.ProjId = l.ProjId;

/* ######### END OF PART 1 ######### */

/* ######### PART 2: SQL UPDATES AND DELETES ######### */

rem Update1
UPDATE Employee SET HomeZipCode='47907' WHERE EmpId=2;
SELECT * FROM Employee WHERE EmpId=2;


rem Update2
UPDATE Graduate SET GradYear=GradYear+3 WHERE GradYear<2002;


rem Update3
UPDATE Graduate SET GradYear=GradYear-2 WHERE (EmpId IN (SELECT EmpId FROM Employee WHERE HomeZipCode='47907'));


rem Delete1
DELETE FROM ProjectManager WHERE ProjId=2;
DELETE FROM EmpProject WHERE ProjId=2;
DELETE FROM Project WHERE ProjId=2;