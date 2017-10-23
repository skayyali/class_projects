rem Query 1
SELECT DEPARTMENT.deptid, DEPARTMENT.dname, COUNT(f.fid)
FROM DEPARTMENT
	LEFT JOIN FACULTY f
	ON DEPARTMENT.deptid=f.deptid
GROUP BY DEPARTMENT.deptid, DEPARTMENT.dname
ORDER BY DEPARTMENT.dname;


rem Query 2
SELECT FACULTY.fid AS FID, FACULTY.fname AS FNAME, FACULTY.deptid AS DEPTID
FROM FACULTY
WHERE (
	 fid IN (SELECT fid FROM CLASS GROUP BY fid HAVING COUNT(*) = (SELECT MAX(COUNT(*)) FROM CLASS GROUP BY fid))
);


rem Query 3
SELECT STUDENT.sname AS SNAME, STUDENT.deptid AS DEPTID, STUDENT.age AS AGE
FROM STUDENT
WHERE (
	snum in (SELECT snum
	FROM ENROLLED
	INNER JOIN (
		SELECT c.fid, c.cname
		FROM CLASS c
		INNER JOIN FACULTY f
		ON (c.fid = f.fid AND f.deptid = 1)
		WHERE f.deptid = 1
	) tab ON ENROLLED.cname = tab.cname GROUP BY snum HAVING COUNT(*) = (SELECT MAX(COUNT(*)) FROM ENROLLED
						INNER JOIN (
							SELECT c.fid, c.cname
							FROM CLASS c
							INNER JOIN FACULTY f
							ON (c.fid = f.fid AND f.deptid = 1)
							WHERE f.deptid = 1
						) tab
						ON ENROLLED.cname = tab.cname
						GROUP BY snum)
	)
);


rem Query 4
SELECT STUDENT.sname, STUDENT.deptid
FROM STUDENT
WHERE (
	snum IN (
		SELECT snum FROM (
			SELECT DISTINCT s.snum, c.room
			FROM STUDENT s, CLASS c
			WHERE (
				snum IN (
					SELECT snum FROM ENROLLED WHERE ENROLLED.cname = c.cname 
				)
			)
		) GROUP BY snum HAVING COUNT(*) = (SELECT MAX(COUNT(*)) FROM (
			SELECT DISTINCT s.snum, c.room
			FROM STUDENT s, CLASS c
			WHERE (
				snum IN (
					SELECT snum FROM ENROLLED WHERE ENROLLED.cname = c.cname 
				)
			)
		) tab
		GROUP BY tab.snum)
	) OR age < 20
);


rem Query 5
SELECT snum
FROM (SELECT e.snum, (SELECT SUM(COUNT(t.snum))
				FROM ENROLLED t
				WHERE t.snum != e.snum AND t.cname IN (SELECT cname FROM ENROLLED w WHERE w.snum = e.snum)
				GROUP BY cname) as "Classmates"
FROM ENROLLED e
GROUP BY snum
ORDER BY "Classmates" DESC)
WHERE ROWNUM = 1;


rem Query 6
SELECT f.fname
FROM FACULTY f
WHERE (
	f.fid IN (SELECT fid
			FROM CLASS
			GROUP BY fid, room
			HAVING COUNT(*) > 1)
);


rem Query 7
SELECT d.deptid, NVL((SELECT AVG(s.age) FROM STUDENT s WHERE s.deptid = d.deptid), 0) AS AverageAge
FROM DEPARTMENT d
WHERE dname != 'Management';


rem Query 8
SELECT deptid, sname, age
FROM (SELECT s.deptid, s.sname, s.age
		FROM STUDENT s
		WHERE (
			s.snum NOT IN (SELECT DISTINCT e.snum FROM ENROLLED e)
		)
		ORDER BY age ASC)
WHERE ROWNUM = 1;


rem Query 9
SELECT s.snum
FROM STUDENT s
WHERE (
	s.deptid NOT IN (
		SELECT f.deptid
		FROM FACULTY f
		LEFT JOIN CLASS c
		ON f.fid = c.fid
		GROUP BY f.deptid
		HAVING COUNT(c.cname) > 0
	)
);


rem Query 10
SELECT fname, numberofstudents
FROM(
	SELECT fname
	FROM FACULTY
	WHERE(
		fid IN (SELECT c.fid FROM CLASS c WHERE (c.cname = (SELECT * FROM (SELECT e.cname FROM ENROLLED e GROUP BY e.cname ORDER BY COUNT(e.snum) DESC) WHERE ROWNUM = 1)))
	)
), (
	SELECT * FROM (SELECT COUNT(e.snum) as numberofstudents FROM ENROLLED e GROUP BY e.cname ORDER BY COUNT(e.snum) DESC) WHERE ROWNUM = 1
);