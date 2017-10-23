import java.util.*;

public class SAP
{
	public Digraph d;
	public Digraph reverse;

	public SAP(Digraph d)
	{
		this.d = d;
		this.reverse = d.reverse();
	}
	
	public int length(int v, int w)
	{
		int temp = 0;
		Iterator<Integer> parent;
		int length = 0;
		//StdOut.printf("Finding length between %d and %d\n", v, w);
		while(temp == 0)
		{
			temp = isChild(v, w, false);
			//StdOut.printf("Is %d a child of %d?\n", w, v);
			if(temp == 0)
			{
				//StdOut.printf("Nope! Time to check the parents\n");
				parent = d.adj(v).iterator();
				if(parent.hasNext() == false)
				{
					length = -1;
					break;
				}
				v = parent.next();
				//StdOut.printf("New parent node: %d\n", v);
				length++;
				//StdOut.printf("Length so far: %d\n", length);
			}
			else
			{
				length += temp;
				//StdOut.printf("Yes! Distance: %d\n", temp);
			}
		}
		
		return length;
	}

	public int ancestor(int v, int w)
	{
		int temp = 0;
		Iterator<Integer> parent;
		//StdOut.printf("Finding ancestor between %d and %d\n", v, w);
		while(temp == 0)
		{
			temp = isChild(v, w, false);
			//StdOut.printf("Is %d a child of %d?\n", w, v);
			if(temp == 0)
			{
				//StdOut.printf("Nope! Time to check the parents\n");
				parent = d.adj(v).iterator();
				if(parent.hasNext() == false)
				{
					return -1;
				}
				v = parent.next();
				//StdOut.printf("New parent node: %d\n", v);
			}
			else
			{
				//StdOut.printf("We found a common parent node!\n");
				return v;
			}
		}
		//StdOut.printf("This should never happen,\n");
		return -1;
	}

	public int isChild(int v, int w, boolean reversed)
	{
		Digraph graph;
		if(reversed == false)
		{
			graph = this.reverse;
		}
		else
		{
			graph = d;
		}
		Iterator<Integer> children = graph.adj(v).iterator();
		int result = 0;
		while(children.hasNext())
		{
			int temp;
			temp = children.next();
			//StdOut.printf("Checking child node %d of %d\n", temp, v);
			if(temp == w)
			{
				result++;
				//StdOut.printf("They're teh same! Result: %d\n", result);
				break;
			}
			int length = isChild(temp, w, reversed);
			//StdOut.printf("Is %d a child of %d? Result: %d\n", w, temp, length);
			if(length != 0)
			{
				result += length + 1;
				break;
			}
		}
		//StdOut.printf("Result: %d\n", result);
		return result;
	}
	public static void main(String args[])
	{
		In digraphInput = new In(args[0]);
		In digraphTest = new In(args[1]);
		Digraph digraph = new Digraph(digraphInput);
		SAP sap = new SAP(digraph);
		int i, j;
		while(!digraphTest.isEmpty())
		{
			i = digraphTest.readInt();
			j = digraphTest.readInt();
		
			int result = sap.length(i, j);
			int ancestor = sap.ancestor(i, j);
		
			StdOut.printf("SAP = %d, ancestor = %d\n", result, ancestor);
		

		}
	
	}
}

