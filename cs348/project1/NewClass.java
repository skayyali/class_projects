package project1;

import java.io.Serializable;
import java.util.ArrayList;

public class NewClass implements Serializable {
	private String NAME;
	private String ROOM;
	private String MEETS_AT;
	private String FID;
	ArrayList<String> students = new ArrayList<String>();
	
	
	public NewClass(String NAME, String ROOM, String MEETS_AT, String FID) {
		this.NAME = NAME;
		this.ROOM = ROOM;
		this.MEETS_AT = MEETS_AT;
		this.FID = FID;
	}
	public String getName() {
		return this.NAME;
	}
	
	public void addStudent(String SNUM) {
		students.add(SNUM);
	}
	public String getLocation() {
		return this.ROOM;
	}
	public String getMeeting() {
		return MEETS_AT;
	}
	public String getFID() {
		return FID;
	}
}
