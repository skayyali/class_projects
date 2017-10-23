import java.util.*;

public class CriticalEdges
{
	public static void main(String args[])
	{
		In graph= new In(args[0]);
		int n = Integer.parseInt(args[1]);
		int nVertix = graph.readInt();
		int nEdges = graph.readInt();
		Edge[] edges;
		EdgeWeightedGraph ewg;
		int v, w;
		Edge edge;
		HashMap<Edge, Integer> counts = new HashMap<>();

		edges = new Edge[nEdges];
		for(int x = 0; x < nEdges; x++)
		{
			v = graph.readInt();
			w = graph.readInt();
			edges[x] = new Edge(v,w,0);
			counts.put(edges[x], 0);
		}
		for(int i = 0; i<50; i++)
		{
	 		ewg = new EdgeWeightedGraph(nVertix);
			for(int x = 0; x < nEdges; x++)
			{
				Edge old = edges[x];
				double rand = StdRandom.uniform();
				v = old.either();
				w = old.other(v);
				edge = new Edge(v, w, rand);
				ewg.addEdge(edge);
			}
			PrimMST mst = new PrimMST(ewg);
			int temp_count;
			Edge temp;
			for(Edge e : mst.edges())
			{
				for(Edge f : edges)
				{
					if(e.either() == f.either() && e.other(e.either()) == f.other(f.either()))
					{
						temp_count = counts.remove(f);
						temp_count++;
						counts.put(f, temp_count);
					}
				}
			}
		}

		LinkedList<EdgeCounter> finals = new LinkedList<>();
		for(Edge e : counts.keySet())
		{
			finals.add(new EdgeCounter(counts.get(e), e));
		}
		Collections.sort(finals);
		while(finals.size() > n)
			finals.removeLast();
		for(EdgeCounter ec : finals)
		{
			System.out.println("Edge " + ec.v + "-" + ec.w);
		}
	}
	
}
