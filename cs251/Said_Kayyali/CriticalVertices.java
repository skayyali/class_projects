import java.util.*;
import java.io.*;
public class CriticalVertices
{
	public static int indexOfMax(int[] array) {
		int max = 0;
		int index = 0;
		for(int i = 0; i < array.length; i++) {
			if(array[i] > max) {
				index = i;
				max = array[i];
			}
		}
		return index;
	}

	public static void main(String args[]){
		File file = new File(args[0]);
		In graph= new In(file);
		int n = Integer.parseInt(args[1]);

		EdgeWeightedDigraph ewdg = new EdgeWeightedDigraph(graph);
		
		int v = ewdg.V();;
		int [] vertices = new int[v];

		for(int i = 0; i<v; i++){
			DijkstraSP dsp = new DijkstraSP(ewdg, i);
			for(int j = 0; j < v; j++){
				vertices[j]++;
				for(DirectedEdge a : dsp.pathTo(j)){
					vertices[a.from()]++;
				}
			}
		}
		if(v<n){v=n;}
		int [] copy = Arrays.copyOf(vertices, vertices.length);
		
		System.out.printf("Vertices with high betweenness centrality:");
		for(int i = 0; i<n; i++){
			int index = indexOfMax(copy);
			copy[index] = -1;
			if(i==n-1){System.out.printf(" %d", index);}
			else{
				System.out.printf(" %d,", index);
			}
		}
		System.out.printf("\n");
		
		
	}
}
