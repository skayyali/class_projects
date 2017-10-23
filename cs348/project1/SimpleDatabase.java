package project1;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.lang.Integer;
import java.util.ArrayList;


public class SimpleDatabase implements Serializable {


	int maxStudents, maxFaculties	= 99999;  // MAX NUMBER OF STUDENTS/FACULTY MEMBERS, INDICATES HOW MANY DIGITS IN ID
	
	private boolean studentID[]	= new boolean[maxStudents];
	private boolean facultyID[]	= new boolean[maxFaculties];
	//ArrayLists of Objects
	private ArrayList<Student>	students		= new ArrayList<Student>();//new Student[maxStudents]; //holds Student objects
	private ArrayList<Faculty>	faculties		= new ArrayList<Faculty>();//new Faculty[maxFaculties]; //holds faculty objects
	private ArrayList<NewClass> classes 		= new ArrayList<NewClass>(); //ArrayList of classes 
	private ArrayList<Department> departments = new ArrayList<Department>();//ArrayList of departments
	
	//ArrayLists and Arrays of relations (check list)
	private ArrayList<String> deptList	= new ArrayList<String>();
	private ArrayList<String> classList = new ArrayList<String>();
	
	
	/*Your implementation starts here*/
	
	public SimpleDatabase() {
		for (int i = 0; i < studentID.length; i++) {
			studentID[i] 	= false;
			students.add(null);
		}
		for (int i = 0; i < facultyID.length; i++) {
			facultyID[i]	= false;
			faculties.add(null);
		}
	}
	 
	public void addStudent( String snum, String sname, String slevel, int age, String deptid ) {
		if (studentID[Integer.parseInt(snum)]){
			System.out.println("Error: Student already exists!");
			return;
		}
		if (!deptList.contains(deptid)){
			System.out.println("Error: Department does not exist!");
			return;
		}
		
 		Student newStudent	= new Student(snum, sname, slevel, age, deptid); //new Student object
 		int dnum			= deptList.indexOf(deptid);		//get department index number
 		Department d		= departments.get(dnum);		//get department object from ArrayList
 		
 		d.addStudent(snum);								//add to department's student array
		studentID[Integer.parseInt(snum)]	= true;     //student checklist
		students.add(Integer.parseInt(snum), newStudent);
	}
	
	public void addFaculty( String fid, String fname, String deptid ) {
		if (facultyID[Integer.parseInt(fid)]){
			System.out.println("Error: Faculty already exists!");
			return;
		}
		if (!deptList.contains(deptid)){
			System.out.println("Error: Department does not exist!");
			return;
		}
		
		Faculty newFaculty = new Faculty(fid, fname, deptid);
		int dnum			= deptList.indexOf(deptid);		//get department index number
 		Department d		= departments.get(dnum);		//get department object from ArrayList
 		
 		d.addFaculty(fid);								//add to department's faculty array
		facultyID[Integer.parseInt(fid)] = true;		//faculty checklist
		faculties.add(Integer.parseInt(fid), newFaculty);
	}
	
	public void addClass( String name, String room, String meets_at, String fid ) {
		if (classList.contains(name)){
			System.out.println("Error: class already exists!");
			return;
		}
		if (!facultyID[Integer.parseInt(fid)]){
			System.out.println("Error: Faculty does not exist!");
			return;
		}
		
		NewClass newClass = new NewClass(name, room, meets_at, fid); //new class object
		
		int facultyID = Integer.parseInt(fid);
		
		Faculty f = faculties.get(facultyID);//faculties[facultyID];
		f.addClass(name);
		classList.add(name);
		classes.add(newClass);
	}
	
	public void addDepartment( String deptid, String dname, String location ) {
		if (deptList.contains(deptid)) {
			System.out.println("Error: Department arleady exists");
			return;
		}
		
		Department department = new Department(deptid, dname, location);
		deptList.add(deptid);
		departments.add(department);
		
	}
	
	public void enroll( String snum, String name) {
		if (!studentID[Integer.parseInt(snum)]){
			System.out.println("Error: Student does not exist!");
			return;
		}
		if (!classList.contains(name)){
			System.out.println("Error: class does not exist!");
			return;
		}
		
		int studentID = Integer.parseInt(snum);
		NewClass c = null;
		for (int i = 0; i < classes.size(); i++) {
			c = classes.get(i);
			if(c.getName().equals(name))
				break;
		}
		
		Student s = students.get(studentID);//students[studentID];
		c.addStudent(snum); //add student to class's list
		s.addClass(name);   //add class to student's list
		
	}
	
	public void getStudentsInDepartment( String deptid ) {
		int dnum = deptList.indexOf(deptid);
		if (dnum == -1) {
			System.out.println("Error: Department does not exsist!");
			return;
		}
		
 		Department d = departments.get(dnum);
		for (int i = 0; i < d.students.size(); i++) {
			String studentID = d.students.get(i);
			int id = Integer.parseInt(studentID);
			Student s = students.get(id);//students[id];
			String name = s.getName();
			String level = s.getLevel();
			int age = s.getAge();
			System.out.println(name + ", " + level + ", " + age);
		}
	}
	
	public void getStudentsInClass( String name ) {
		NewClass c = null;
		for (int i = 0; i < classes.size(); i++) {
			c= classes.get(i);
			if(c.getName().equals(name))
				break;
		}
		
		for (int i = 0; i < c.students.size(); i++) {
			String studentID = c.students.get(i);
			int id = Integer.parseInt(studentID);
			Student s = students.get(id);//students[id];
			String sname = s.getName();
			String level = s.getLevel();
			int age = s.getAge();
			System.out.println(sname + ", " + level + ", " + age);
		}
	}
	
	public void getClassesForStudent( String snum ) {
		int studentID = Integer.parseInt(snum);
		Student s = students.get(studentID);//students[studentID];
		NewClass c;
		for (int i = 0; i < s.classes.size(); i++) {
			String className = s.classes.get(i);
			for(int j = 0; j < classes.size(); j++) {
				c = classes.get(j);
				if (c.getName().equals(className)) {
					String cname = c.getName();
					String clocation = c.getLocation();
					String meeting = c.getMeeting();
					String cFID = c.getFID();
					System.out.println(cname + ", "  + clocation + ", " + meeting + ", " + cFID);
					break;
				}
			}
		}
	}
	
	public void getClassesForFaculty( String fid ) {
		int facultyID = Integer.parseInt(fid);
		Faculty f = faculties.get(facultyID);//faculties[facultyID];
		NewClass c;
		for (int i = 0; i < f.classes.size(); i++) {
			String className = f.classes.get(i);
			for(int j = 0; j < classes.size(); j++) {
				c = classes.get(j);
				if (c.getName().equals(className)) {
					String cname = c.getName();
					System.out.println(cname);
					break;
				}
			}
		}
	}
	
	public void deleteClass( String name ) {
		NewClass deleteClass = null;
		for (int i = 0; i < classes.size(); i++) {
			deleteClass = classes.get(i);
			if(deleteClass.getName().equals(name))
				break;
		}
		int facultyID = Integer.parseInt(deleteClass.getFID());
		Faculty f = faculties.get(facultyID);
		ArrayList<String> studentsInClass = new ArrayList<String>(deleteClass.students);
		Student s;
		for (int i = 0; i < studentsInClass.size(); i++) {
			s = students.get(Integer.parseInt(studentsInClass.get(i)));
			s.removeClass(name);
		}
		
		f.removeClass(name);
	}
	
	public void save( String filename ) {
		String file = filename + ".bin";
		try {
			ObjectOutputStream os = new ObjectOutputStream(new FileOutputStream(file));
			os.writeObject(this);
			os.close();
		} catch (IOException e) {
			System.out.println("Error saving file");
			e.printStackTrace();
		}
		
	}
	
	public void load( String filename ) throws ClassNotFoundException {
		String file = filename + ".bin";
		try {
			ObjectInputStream is = new ObjectInputStream(new FileInputStream(file));
			SimpleDatabase temp = (SimpleDatabase) is.readObject();
			maxStudents	= temp.maxStudents;
			maxFaculties	= temp.maxFaculties;
			
			for (int i = 0; i < maxStudents; i++)
				studentID[i] = temp.studentID[i];
			for (int i = 0; i < maxFaculties; i++)
				facultyID[i] = temp.facultyID[i];
			students.clear();
			faculties.clear();
			classes.clear();
			departments.clear();
			deptList.clear();
			classList.clear();
			
			students = new ArrayList<Student>(temp.students);
			faculties = new ArrayList<Faculty>(temp.faculties);
			classes = new ArrayList<NewClass>(temp.classes);
			departments = new ArrayList<Department>(temp.departments);
			deptList = new ArrayList<String>(temp.deptList);
			classList = new ArrayList<String>(temp.classList);
			is.close();
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
	public void help() {
		System.out.println("add_department DEPTID DNAME LOCATION\n"
						+ "add_student SNUM SNAME SLEVEL AGE DEPTID\n"
						+ "add_faculty FID FNAME DEPTID\n"
						+ "add_class NAME ROOM MEETS_AT FID\n"
						+ "enroll SNUM NAME\n"
						+ "get_students_in_department DEPTID\n"
						+ "get_students_in_class NAME\n"
						+ "get_classes_for_student SNUM\n"
						+ "get_classes_for_faculty FID\n"
						+ "delete_class NAME\n"
						+ "save FILENAME\n"
						+ "load FILENAME\n"
						+ "exit");
	}
	
	
  
   /*Your implementation ends here */
   
   
	public static void main( String [] args ) throws ClassNotFoundException {
	
		SimpleDatabase sd = new SimpleDatabase();
		
		System.out.println( "Please enter a command.  Enter 'help' for a list of commands." );
		
		BufferedReader reader = new BufferedReader( new InputStreamReader( System.in ) );

		String line = "";
		
		try {
			line = reader.readLine();
		}
		catch ( IOException e ) {
			e.printStackTrace();
		}
		
		
		
		String[] pieces = line.split( "\\s+" );
		String[] params;
		String command;
		
		if ( pieces.length > 0 ) {
			command = pieces[0];
			params = new String[pieces.length - 1];
			System.arraycopy( pieces, 1, params, 0, pieces.length - 1 );
		}
		else {
			command = "";
			params = null;
		}
		
		
		while ( !( command.equalsIgnoreCase( "exit" ) ) ) {
		
			if ( command.equalsIgnoreCase( "add_student" ) ) {
				if ( params.length != 5 ) {
					System.out.println( "Incorrect number of parameters!" );
				}
				else {
					String snum = params[0];
					String sname = params[1];
					String slevel = params[2];
					int age = ( new Integer( params[3] ) ).intValue();
					String deptid = params[4];
					sd.addStudent( snum, sname, slevel, age, deptid );
				}
			}
			else if ( command.equalsIgnoreCase( "add_faculty" ) ) {
				if ( params.length != 3 ) {
					System.out.println( "Incorrect number of parameters!" );
				}
				else {
					String fid = params[0];
					String fname = params[1];
					String deptid = params[2];
					sd.addFaculty( fid, fname, deptid );
				}
			}
			else if ( command.equalsIgnoreCase( "add_department" ) ) {
				if ( params.length != 3 ) {
					System.out.println( "Incorrect number of parameters!" );
				}
				else {
					String deptid = params[0];
					String dname = params[1];
					String location = params[2];
					sd.addDepartment( deptid, dname, location );
				}
			}
			else if ( command.equalsIgnoreCase( "add_class" ) ) {
				if ( params.length != 4 ) {
					System.out.println( "Incorrect number of parameters!" );
				}
				else {
					String name = params[0];
					String room = params[1];
					String meets_at = params[2];
					String fid = params[3];
					sd.addClass( name, room, meets_at, fid );
				}
			}
			else if ( command.equalsIgnoreCase( "enroll" ) ) {
				if ( params.length != 2 ) {
					System.out.println( "Incorrect number of parameters!" );
				}
				else {
					String snum = params[0];
					String name = params[1];
					sd.enroll( snum, name );
				}
			}
			else if ( command.equalsIgnoreCase( "get_students_in_department" ) ) {
				if ( params.length != 1 ) {
					System.out.println( "Incorrect number of parameters!" );
				}
				else {
					String deptid = params[0];
					sd.getStudentsInDepartment( deptid );
				}
			}
			else if ( command.equalsIgnoreCase( "get_students_in_class" ) ) {
				if ( params.length != 1 ) {
					System.out.println( "Incorrect number of parameters!" );
				}
				else {
					String name = params[0];
					sd.getStudentsInClass( name );
				}
			}
			else if ( command.equalsIgnoreCase( "get_classes_for_student" ) ) {
				if ( params.length != 1 ) {
					System.out.println( "Incorrect number of parameters!" );
				}
				else {
					String snum = params[0];
					sd.getClassesForStudent( snum );
				}
			}
			else if ( command.equalsIgnoreCase( "get_classes_for_faculty" ) ) {
				if ( params.length != 1 ) {
					System.out.println( "Incorrect number of parameters!" );
				}
				else {
					String fid = params[0];
					sd.getClassesForFaculty( fid );
				}
			}
			else if ( command.equalsIgnoreCase( "delete_class" ) ) {
				if ( params.length != 1 ) {
					System.out.println( "Incorrect number of parameters!" );
				}
				else {
					String name = params[0];
					sd.deleteClass( name );
				}
			}
			else if ( command.equalsIgnoreCase( "save" ) ) {
				if ( params.length != 1 ) {
					System.out.println( "Incorrect number of parameters!" );
				}
				else {
					String filename = params[0];
					sd.save( filename );
				}
			}
			else if ( command.equalsIgnoreCase( "load" ) ) {
				if ( params.length != 1 ) {
					System.out.println( "Incorrect number of parameters!" );
				}
				else {
					String filename = params[0];
					sd.load( filename );
				}
			}
			else if ( command.equalsIgnoreCase( "help" ) ) {
				if ( params.length != 0 ) {
					System.out.println( "Incorrect number of parameters!" );
				}
				else {
					sd.help();
				}
			}
			else {
				System.out.println( "Invalid command!" );
			}
			
			try {
				line = reader.readLine();
			}
			catch ( IOException e ) {
				e.printStackTrace();
			}
			
			pieces = line.split( "\\s+" );
		
			if ( pieces.length > 0 ) {
				command = pieces[0];
				params = new String[pieces.length - 1];
				System.arraycopy( pieces, 1, params, 0, pieces.length - 1 );
			}
			else {
				command = "";
			}
			
		}
	
	}



}