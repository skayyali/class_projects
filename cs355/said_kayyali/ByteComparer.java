package project2;

import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class ByteComparer {
	public static void main (String args[]) throws IOException {
		FileInputStream in = null;
		FileInputStream in1 = null;
		PrintWriter out = null;
		int byteCount [] = new int[256];
		for (int i = 0; i < byteCount.length; i++)
			byteCount[i] = 0;
		try {
			in = new FileInputStream("C:\\Users\\Said\\workspace\\project2\\src\\project2\\storycbc.txt");
			in1 = new FileInputStream("C:\\Users\\Said\\workspace\\project2\\src\\project2\\storycbc2.txt");
			int file1Size = (int) in.getChannel().size();
			int file2Size = (int) in1.getChannel().size();
			int size = 0;
			int otherS = 0;
			if (file1Size < file2Size) {
				size = file1Size;
				otherS = file2Size;
			}
			else {
				size = file2Size;
				otherS = file1Size;
			}
			//System.out.println(fileSize);
			int count = 0;
			for (int i = 0; i < size; i++) {
				if(in.read() == in1.read()) {
					count ++;
				}
			}
			int diff = otherS - count + (size - count);
			System.out.println("Number of same bytes: " + count + "\t Number of different bytes: " + diff);
		}
		finally {
			if (in != null) {
				in.close();
				in1.close();
			}
		}
	}
}
