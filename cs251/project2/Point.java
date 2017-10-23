public class Point implements Comparable<Point> {
  public double x, y;
  int index;
  public Point(double x, double y, int index) {
    this.x = x;
    this.y = y;
    this.index = index;
  }
  
  public int compareTo(Point target){
      double diff = this.x-target.x;
      if(diff==0){
          double diffY = this.y-target.y;
          if(diffY>0){return 1;}
          else if(diffY<0){return -1;}
          else if(diffY==0){return 0;}
      }
      else if(diff>0){return 1;}
      return -1;
  }
  
  public void print()
  {
      this.print("");
  }
  
  public void print(String prepend)
  {
      StdOut.print(prepend + "id" + this.index + " (" + this.x + "," + this.y + ")");
  }
}
