package university;

import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;
import com.google.appengine.api.datastore.EntityNotFoundException;
import com.google.appengine.api.datastore.FetchOptions;
import com.google.appengine.api.datastore.Key;
import com.google.appengine.api.datastore.KeyFactory;
import com.google.appengine.api.datastore.PreparedQuery;
import com.google.appengine.api.datastore.Query;
import com.google.appengine.api.datastore.Query.Filter;
import com.google.appengine.api.datastore.Query.FilterPredicate;
import com.google.appengine.api.datastore.Query.FilterOperator;
import com.google.appengine.api.datastore.Query.CompositeFilter;
import com.google.appengine.api.datastore.Query.CompositeFilterOperator;
import com.google.appengine.api.datastore.Query.SortDirection;
import com.google.appengine.api.datastore.QueryResultList;

import java.io.IOException;







import java.util.List;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ProcessCommandServlet extends HttpServlet {
    public void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws IOException {
    	
        Key universityKey = KeyFactory.createKey("University", "Purdue");
        
        
      /*you don't need to worry about the variable below, this gets the value of the 
       * string entered in the text area as defined in the university.jsp file
       */
        String content = req.getParameter("command");
        
        
        /*This String array contains the individual elements of the 
        command entered in the text area, e.g. if commandEls[0] gives "add_department", 
        commandEls[1] gives the department id, commandEls[2] gives the department name
        and commandEls[3] gives the department location*/ 
        String [] commandEls = content.split(" ");
        
        /*This string contains the results to display to the user once a command is entered.
         * For a query, it should list the results of the query. 
         * For an insertion, it should either contain an error message or 
         * the message "Command executed successfully!"*/
        String results = null;
        
        
        DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();
        
        /*your implementation starts here*/
        
        
        if ( commandEls[0].equals( "add_student" ) ) {
        	String snum = commandEls[1];
        	String sname = commandEls[2];
        	String slevel = commandEls[3];
        	String age = commandEls[4];
        	
        	Filter snumFilter = new FilterPredicate("snum", FilterOperator.EQUAL, snum);
        	Query q = new Query("Student").setFilter(snumFilter);
        	PreparedQuery pq = datastore.prepare(q);
        	List<Entity> list = pq.asList(FetchOptions.Builder.withLimit(5));
        	
        	if (list.size() > 0) {
        		results = "Error: Student already exists!";
        	} else {
            	Entity student = new Entity("Student");
            	student.setProperty("snum", snum);
            	student.setProperty("sname", sname);
            	student.setProperty("slevel", slevel);
            	student.setProperty("age", age);
            	
            	datastore.put(student);
            	results = "Command executed successfully!";
        	}
        	
        	
        }
        else if ( commandEls[0].equals( "add_faculty" ) ) {
        	String fid = commandEls[1];
        	String fname = commandEls[2];
        	
        	Filter fidFilter = new FilterPredicate("fid", FilterOperator.EQUAL, fid);
        	Query q = new Query("Faculty").setFilter(fidFilter);
        	PreparedQuery pq = datastore.prepare(q);
        	List<Entity> list = pq.asList(FetchOptions.Builder.withLimit(5));
        	
        	if (list.size() > 0 ) {
        		results = "Error: Faculty already exists!";
        	} else {
        		Entity faculty = new Entity("Faculty");
            	faculty.setProperty("fid", fid);
            	faculty.setProperty("fname", fname);
            	
            	datastore.put(faculty);
            	results = "Command executed successfully!";
        	}
        		
        }
        else if ( commandEls[0].equals( "add_class" ) ) {
        	String cname = commandEls[1];
        	String room = commandEls[2];
        	String meets_at = commandEls[3];
        	String fid = commandEls[4];
        	
        	Filter cnameFilter = new FilterPredicate("cname", FilterOperator.EQUAL, cname);
        	Query q = new Query("Class").setFilter(cnameFilter);
        	PreparedQuery pq = datastore.prepare(q);
        	List<Entity> list = pq.asList(FetchOptions.Builder.withLimit(5));
        	
        	if (list.size() > 0 ) {
        		results = "Error: Class already exists!";
        	} else {
        		Entity newClass = new Entity("Class");
            	newClass.setProperty("cname", cname);
            	newClass.setProperty("room", room);
            	newClass.setProperty("meets_at", meets_at);
            	newClass.setProperty("fid", fid);
            	
            	datastore.put(newClass);
            	results = "Command executed successfully!";
        	}
            	
        }
        else if ( commandEls[0].equals( "enroll" ) ) {
        	String snum = commandEls[1];
        	String cname = commandEls[2];
        	System.out.println("GOT: " + snum + " AND " + cname);
        	Filter snumFilter = new FilterPredicate("snum", FilterOperator.EQUAL, snum);
        	Filter cnameFilter = new FilterPredicate("cname", FilterOperator.EQUAL, cname);
        	Filter enrollFilter =  CompositeFilterOperator.and(snumFilter, cnameFilter);
        	Query q = new Query("Enrollment").setFilter(enrollFilter);
        	PreparedQuery pq = datastore.prepare(q);
        	List<Entity> enrollments = pq.asList(FetchOptions.Builder.withLimit(5));
        	System.out.println("Number of existing tuples : " + enrollments.size());
        	if (enrollments.size() > 0) {
        		results = "Error: Class already exists!";
        	} else {
        		Entity enrollment = new Entity("Enrollment");
            	enrollment.setProperty("snum", snum);
            	enrollment.setProperty("cname", cname);
            	
            	datastore.put(enrollment);
            	results = "Command executed successfully!";
        	}
        }
        
        else if ( commandEls[0].equals( "get_classes_for_student" ) ) {
        	String snum = commandEls[1];
        	String message = "";
        	Filter snumFilter = new FilterPredicate("snum", FilterOperator.EQUAL, snum);
        	Query q = new Query("Enrollment").setFilter(snumFilter);
        	PreparedQuery pq = datastore.prepare(q);
        	List<Entity> snumClasses = pq.asList(FetchOptions.Builder.withLimit(10));
        	for (Entity snumClass : snumClasses) {
        		String className = (String) snumClass.getProperty("cname");
        		Filter cnameFilter = new FilterPredicate("cname", FilterOperator.EQUAL, className);
        		Query q2 = new Query("Class").setFilter(cnameFilter);
        		PreparedQuery pq2 = datastore.prepare(q2);
        		List<Entity> classes = pq2.asList(FetchOptions.Builder.withLimit(5));
        		for (Entity entity : classes) {
        			String name = (String) entity.getProperty("cname");
        			String room = (String) entity.getProperty("room");
        			String time = (String) entity.getProperty("meets_at");
        			String fid	= (String) entity.getProperty("fid");
        			message = message + name + ", " + room + ", " + time + ", " + fid + "; ";
        		}
        	}
        	results = message;
        }
        
        else if ( commandEls[0].equals( "get_instructors_for_student" ) ) {
        	String snum = commandEls[1];
        	String message = "";
        	Filter snumFilter = new FilterPredicate("snum", FilterOperator.EQUAL, snum);
        	Query q = new Query("Enrollment").setFilter(snumFilter);
        	PreparedQuery pq = datastore.prepare(q);
        	List<Entity> snumClasses = pq.asList(FetchOptions.Builder.withLimit(10));
        	for (Entity snumClass : snumClasses) {
        		String className = (String) snumClass.getProperty("cname");
        		Filter cnameFilter = new FilterPredicate("cname", FilterOperator.EQUAL, className);
        		Query q2 = new Query("Class").setFilter(cnameFilter);
        		PreparedQuery pq2 = datastore.prepare(q2);
        		List<Entity> classes = pq2.asList(FetchOptions.Builder.withLimit(5));
        		for (Entity entity : classes) {
        			String fid	= (String) entity.getProperty("fid");
        			Filter fidFilter = new FilterPredicate("fid", FilterOperator.EQUAL, fid);
                	Query q3 = new Query("Faculty").setFilter(fidFilter);
                	PreparedQuery pq3 = datastore.prepare(q3);
                	List<Entity> fidList = pq3.asList(FetchOptions.Builder.withLimit(5));
                	for (Entity facultyMember : fidList) {
                		String fname = (String) facultyMember.getProperty("fname");
                		message = message + fname + "; ";
                	}
        		}
        	}
        	results = message;
        }
        /*your implementation ends here */
        resp.sendRedirect( "/university.jsp?universityName=Purdue&display=" + results );
    }  

}
