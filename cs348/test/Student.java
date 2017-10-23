package project1;

import java.io.Serializable;
import java.util.ArrayList;


public class Student  implements Serializable {
	private String SNUM;
	private String SNAME;
	private String SLEVEL;
	private int AGE;
	private String DEPTID;
	ArrayList<String> classes = new ArrayList<String>();
	
	
	public Student(String SNUM, String SNAME, String SLEVEL, int AGE, String DEPTID) {
		this.SNUM	= SNUM;
		this.SNAME	= SNAME;
		this.SLEVEL	= SLEVEL;
		this.AGE	= AGE;
		this.DEPTID	= DEPTID;
	}
	
	public String getName() {
		return this.SNAME;
	}
	
	public String getLevel() {
		return this.SLEVEL;
	}
	
	public int getAge() {
		return this.AGE;
	}
	
	public void addClass(String className) {
		classes.add(className);
	}

	public void removeClass(String name) {
		classes.remove(name);
		
	}
}
