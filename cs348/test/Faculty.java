package project1;

import java.io.Serializable;
import java.util.ArrayList;

public class Faculty implements Serializable {
	private String FID;
	private String FNAME;
	private String DEPTID;
	ArrayList<String> classes = new ArrayList<String>();
	
	public Faculty(String FID, String FNAME, String DEPTID) {
		this.FID = FID;
		this.FNAME = FNAME;
		this.DEPTID = DEPTID;
	}
	
	public void addClass(String className) {
		classes.add(className);
	}

	public void removeClass(String name) {
		classes.remove(name);
	}
}
