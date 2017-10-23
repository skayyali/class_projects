package project2;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class ByteCounter {
	public static void main (String args[]) throws IOException {
		Boolean table = false;
		FileInputStream in = null;
		PrintWriter out = null;
		int byteCount [] = new int[256];
		for (int i = 0; i < byteCount.length; i++)
			byteCount[i] = 0;
		try {
			in = new FileInputStream("C:\\Users\\Said\\workspace\\project2\\src\\project2\\storycbc.txt");
			out = new PrintWriter(new FileWriter("C:\\Users\\Said\\workspace\\project2\\src\\project2\\output.txt")); 
			int fileSize = (int) in.getChannel().size();
			//System.out.println(fileSize);
			int b;
			int count = 0;
			while ((b = in.read()) != -1) {
				byteCount[b]++;
			}
			//System.out.println(count);
			int index = 0;
			for (int i = 0; i < byteCount.length; i++) {
				if (!table) {
					out.println(i + "\t" + byteCount[i]);
					index ++;
				}
				else if (table) {
					out.print(i + "\t" + byteCount[i] + "\t");
					index ++;
					if (index == 16) {
						out.println();
						//out.println("----------------------------------------------------------------------------------------------------------------------"
								//+ "------------------------------------------------------------------------------------------------------------------------------------");
						index = 0;
					}
				}
			}
		}
		finally {
			if (in != null)
				in.close();
			if (out!= null)
				out.close();
		}
	}


}
