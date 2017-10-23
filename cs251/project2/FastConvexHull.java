import java.util.*;
import java.lang.Math;
import java.lang.*;
import java.awt.*;

public class FastConvexHull {
    ArrayList<Point> points;
    LinkedList<Edge> solutions;
    int totalNumberOfPoints;
    int currentNumberOfPoints;
  
  
    public FastConvexHull(int n) { 
        points = new ArrayList<Point>();
        totalNumberOfPoints = n;
        currentNumberOfPoints = 0;
        solutions = new LinkedList<Edge>();
    }
  
  public void add(double x, double y){
      if(currentNumberOfPoints == totalNumberOfPoints)
          return;
      points.add(new Point(x,y,currentNumberOfPoints));
      currentNumberOfPoints++;
  }
  /*
   * 
   * Undefined behvaiour when (x0,y0) == (x1,y1) and x==x0/x1 but y!=y0/y1
   * Will return 0, but not necessarily correct
   * 
  */
  public int whichSide(Point start, Point end, Point target){
      double m, b, c;
      double x0 = start.x;
      double y0 = start.y;
      double x1 = end.x;
      double y1 = end.y;
      double x = target.x;
      double y = target.y;
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
      int size = StdIn.readInt();
	Stopwatch time = new Stopwatch();
      
      FastConvexHull hull = new FastConvexHull(size);
      for(int i= 0; i<size;i++){
          hull.add(StdIn.readDouble(), StdIn.readDouble());
      }
      
      LinkedList<Point> lower = new LinkedList<Point>();
      LinkedList<Point> upper = new LinkedList<Point>();
      Collections.sort(hull.points);
      
      lower.add(hull.points.get(0));
      lower.add(hull.points.get(1));
      
      upper.add(hull.points.get(hull.currentNumberOfPoints-1));
      upper.add(hull.points.get(hull.currentNumberOfPoints-2));
      for(int i = 2; i<hull.currentNumberOfPoints; i++){
                   
          while(lower.size()>=2  &&  hull.whichSide(lower.get(lower.size()-2), lower.peekLast(), hull.points.get(i)) <= 0)
          {
              lower.removeLast();
          }
          lower.add(hull.points.get(i));
      }
      
      for(int i = hull.currentNumberOfPoints-2; i>-1; i--){
                   
          while(upper.size()>=2  &&  hull.whichSide(upper.get(upper.size()-2), upper.peekLast(), hull.points.get(i)) <= 0)
          {
              upper.removeLast();
          }
          upper.add(hull.points.get(i));
      }
      lower.removeLast();
      upper.removeLast();
      lower.addAll(upper);
	
	StdOut.printf("Elapsed: %f\n", time.elapsedTime());
      for(int i = 0; i < lower.size(); i++)
      {
          lower.get(i).print();
      }

  }
  
}
