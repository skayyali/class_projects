import java.util.*;
import java.lang.Math;

public class SlowConvexHull {
    Point[] points;
    LinkedList<Edge> solutions;
    int totalNumberOfPoints;
    int currentNumberOfPoints;
  
  
    public SlowConvexHull(int n) { 
        points = new Point[n];
        totalNumberOfPoints = n;
        currentNumberOfPoints = 0;
        solutions = new LinkedList<Edge>();
    }
  
  public void add(double x, double y){
      if(currentNumberOfPoints == totalNumberOfPoints)
          return;
      points[currentNumberOfPoints] = new Point(x,y,currentNumberOfPoints);
      currentNumberOfPoints++;
  }
  /*
   * 
   * Undefined behvaiour when (x0,y0) == (x1,y1) and x==x0/x1 but y!=y0/y1
   * Will return 0, but not necessarily correct
   * 
  */
  public int whichSide(double x0, double y0, double x1, double y1, double x, double y){
      double m, b, c;
      if(y1==y0){
          b = y1;
          if(x0 < x1)
          {
              //Above is to the left
              if(y>b)
                  return 1;
              //Below is to the right
              else if (y<b)
                  return -1;
          }
          else if (x0 > x1)
          {
              //Above is to the right
              if(y>b)
                  return -1;
              //Below is to the left
              else if(y<b)
                  return 1;
          }
          else
          {
              //(x0,y0) == (x1,y1)
              if(x0<x)
                  return -1;
              else if(x0>x)
                  return 1;
          }
          return 0;
      }
      else if(x1==x0)
      {
          m=x1;
          if(y0<y1)
          {
              //right is right
              if(x>m)
                  return -1;
              //left is left
              if(x<m)
                  return 1;
          }
          else
          {
              //right is left
              if(x>m)
                  return 1;
              if(x<m)
                  return -1;
              //left is right
          }
          return 0;
      }
      // general cases
      m = (y1-y0)/(x1-x0);
      //if(y0 == 3.0 && x0 == 2.0 && x1 == 3.0 && y1 == 2.0 ) StdOut.printf("\t\tm: %f\n", m);
      b = y1-m*x1;
      //if(y0 == 3.0 && x0 == 2.0 && x1 == 3.0 && y1 == 2.0 ) StdOut.printf("\t\tb: %f\n", b);
      
      c = (y-b)/m;
      //if(y0 == 3.0 && x0 == 2.0 && x1 == 3.0 && y1 == 2.0 ) StdOut.printf("\t\tc: %f\n", c);
      if ( y1 < y0)
      {
          //point is on the left
          if(c<x)
              return 1;
          //poit is on the right
          else if(c>x)
              return -1;
          else
              return 0;
      }
      else
      {
          //point is on the left
          if(c>x)
              return 1;
          //poit is on the right
          else if(c<x)
              return -1;
          else
              return 0;
      }
      
  }
  
  public double distance(Point start, Point end)
  {
      return Math.sqrt((start.x-end.x)*(start.x-end.x) + (start.y-end.y)*(start.y-end.y));
  } 
  
  public static void main(String[] args) 
  { 
      boolean DRAW = false;
	Point unit;
	Point unitTarget;
      int size = StdIn.readInt();
      
      SlowConvexHull hull = new SlowConvexHull(size);
      for(int i= 0; i<size;i++){
          hull.add(StdIn.readDouble(), StdIn.readDouble());
      }
      
      int start, end, point;
      boolean allLeft = true;
      //StdOut.printf("Number of points: %d\n", hull.currentNumberOfPoints);
      
      for(start = 0; start < hull.currentNumberOfPoints; start++)
      {
          //StdOut.printf("Start: (%f, %f)\n", hull.points[start].x, hull.points[start].y);
          for(end = 0; end < hull.currentNumberOfPoints; end++)
          {
              //StdOut.printf("\tEnd: (%f, %f)\n", hull.points[end].x, hull.points[end].y);
              if(start != end)
              {
                  for(point = 0; point < hull.currentNumberOfPoints; point++)
                  {
                      if(hull.points[point] != hull.points[start] && hull.points[point] != hull.points[end])
			{
		              //StdOut.printf("\t\tPoint: (%f, %f)\n", hull.points[point].x, hull.points[point].y);
		              int result = hull.whichSide(hull.points[start].x, hull.points[start].y, hull.points[end].x, hull.points[end].y, hull.points[point].x, hull.points[point].y);
		              //StdOut.printf("\t\t\tResult: %d of (%f, %f)\n", result, hull.points[point].x, hull.points[point].y);
		              if(result == -1)
		              {
		                  //StdOut.printf("\t\t\tFound one on the right!\n");
		                  allLeft = false;
		                  break;
		              }
			}
                  }
                  if(allLeft)
                  {
                      //StdOut.printf("\tNew edge! (%f, %f) to (%f, %f)\n", hull.points[start].x,hull.points[start].y, hull.points[end].x,hull.points[end].y);
                      hull.solutions.add(new Edge(hull.points[start], hull.points[end], "id" + start));
                      break;
                  }
                  allLeft = true;
              }
          }
      }
      
	for(int y = 0; y < hull.solutions.size(); y++)
	{
		Edge e = hull.solutions.get(y);
		for(int z = 0; z < hull.solutions.size(); z++)
		{
			Edge f = hull.solutions.get(z);
			if(e.end == f.end && y != z)
			{
				double e_dist = hull.distance(e.start, e.end);
				double f_dist = hull.distance(f.start, f.end);
				if(e_dist > f_dist)
				{
					hull.solutions.remove(f);
					z--;
				}
				else
				{
					hull.solutions.remove(e);
					y--;
				}
			}
		}
	}
	if(DRAW)
	{
		StdDraw.clear(StdDraw.BLACK);
		StdDraw.setPenColor(StdDraw.WHITE);
		//For loop to map all coordinates to unit scale
		for(int x = 0; x < hull.currentNumberOfPoints; x++)
		{
		  unit = new Point(hull.points[x].x, hull.points[x].y, hull.points[x].index);
		  StdDraw.filledCircle(unit.x, unit.y, 0.0025);
		}
	}

	if(DRAW)
	{
		StdDraw.setPenColor(StdDraw.GREEN);
	}
	Edge current = hull.solutions.pop();
	Point beginning = current.start;
	Point lastEnd = current.end;
	StdOut.printf("%s (%f, %f)", current.name, current.start.x, current.start.y);
	if(DRAW)
	{         
		unit = new Point(current.start.x, current.start.y, current.start.index);
		unitTarget = new Point(current.end.x, current.end.y,current.end.index);
		StdDraw.line(unit.x, unit.y, unitTarget.x, unitTarget.y);
	}
      //StdOut.printf("%s (%f, %f)", current.end.index, current.end.x, current.end.y);
	while(hull.solutions.size() != 0 )
	{
		/*for(int x = 0;x < hull.solutions.size(); x++)
		{
			hull.solutions.get(x).print();
		}
		StdOut.print("\n");*/
		current = hull.solutions.pop();
		//StdOut.print("Last Endpoint: "); lastEnd.print(); StdOut.print("\n");
		if(current.start == lastEnd)
		{
			StdOut.printf(", %s (%f, %f)", current.name, current.start.x, current.start.y);
			if(DRAW)
			{
				unit = new Point(current.start.x, current.start.y, current.start.index);
				unitTarget = new Point(current.end.x, current.end.y,current.end.index);
				StdDraw.line(unit.x, unit.y, unitTarget.x, unitTarget.y);
			}
			lastEnd = current.end;
		}
		else
		{
			hull.solutions.add(current);
		}
	}

		StdOut.printf("\n");
	}
  
}
