package project1;

import java.io.Serializable;
import java.util.ArrayList;

public class Department implements Serializable {
	String DEPTID;
	String DNAME;
	String LOCATION;
	ArrayList<String> students = new ArrayList<String>();
	ArrayList<String> faculty = new ArrayList<String>();
	
	public Department(String DEPTID, String DNAME, String LOCATION) {
		this.DEPTID		= DEPTID;
		this.DNAME		= DNAME;
		this.LOCATION	= LOCATION;
	}
	
	
	public void addStudent(String SNUM) {
		students.add(SNUM);
	}
	public void addFaculty(String FID) {
		faculty.add(FID);
	}
}
