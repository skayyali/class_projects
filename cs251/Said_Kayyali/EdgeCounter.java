public class EdgeCounter implements Comparable<EdgeCounter>
{
	public int counter;
	public int v;
	public int w;

	public EdgeCounter(int n, Edge e)
	{
		counter = n;
		v = e.either();
		w = e.other(v);
	}

	public String toString()
	{
		return new Edge(v, w, 0).toString();
	}
	
	@Override
	public int compareTo(EdgeCounter e)
	{
		if(this.counter > e.counter)
			return -1;
		else if (this.counter < e.counter)
			return 1;
		else
			return 0;
	}
}
