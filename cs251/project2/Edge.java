public class Edge {
  public Point start;
  public Point end;
  public String name;
  public Edge(Point start, Point end, String name) { 
    this.start = start;
    this.end = end;
    this.name = name;
  }

	public void print()
	{
		StdOut.print("(");
		this.start.print();
		StdOut.print(",");
		this.end.print();
		StdOut.print(")");
	}
}
