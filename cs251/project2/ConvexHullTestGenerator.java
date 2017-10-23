public class ConvexHullTestGenerator
{
	public static void main(String[] args)
	{
		StdOut.printf("%d\n", 1000);
		for(int x = 0;x < 1000; x++)
		{
			StdOut.printf("%f %f\n", StdRandom.uniform(0.0, 1.0), StdRandom.uniform(0.0, 1.0));
		}
	}
}
