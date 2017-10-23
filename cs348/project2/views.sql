CREATE VIEW VIEWA AS
SELECT f.fname, COUNT(c.cname) AS numberofstudents
FROM FACULTY f
LEFT JOIN CLASS c
ON f.fid = c.fid
GROUP BY f.fname
ORDER BY f.fname;

CREATE VIEW VIEWB AS
SELECT * FROM (SELECT s.sname, c.room, TO_CHAR(c.meets_at, 'HH24:MI')
FROM STUDENT s, ENROLLED e, CLASS c
WHERE (s.snum = e.snum and e.cname = c.cname)
UNION
SELECT f.fname, c.room, TO_CHAR(c.meets_at, 'HH24:MI')
FROM FACULTY f, CLASS c
WHERE (f.fid = c.fid)
ORDER BY sname);