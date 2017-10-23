package project1;

import java.util.Scanner;

public class ModifiedPrimeSolver2 {
	public static void main(String[] args) {
		long startTime = System.currentTimeMillis();
		int I;
		int J;
		Scanner in = new Scanner(System.in);
		System.out.println("Enter I :");
		I = 1000000000;
		//I = in.nextInt();
		System.out.println("Enter J (J > I) :");
		J = 1000000000+1000000;
		//J = in.nextInt();
		
		double L = 1000;
		
		int n = (int) L;
		//System.out.println("L  -- >" + n);
		int count = 0;
		Boolean [] p = new Boolean[n +1];
		p[0] = false;
		p[1] = false;
		
		//initialize all as true
		for (int c = 2; c <= n; c++) {
			p[c] = true;
		}
		
		//start crossing out
		int k = 2;
		while (k <= Math.sqrt(n)) {
			int y = k + k;
			while(y <= n) {
				p[y] = false;
				y = y + k;
			}
			y = k + 1;
			while (y <= Math.sqrt(n) && p[y] == false) {
				y = y + y;
			}
			k = y;
		}
		
		Boolean A[] = new Boolean[J-I];
		for (int i = 0; i < J-I; i++) {
			A[i] = true;
		}
		
		for (int i = 1; i <= n; i++) {
			if (p[i] == false)
				continue;
			int j = ((I+i-1)/i)*i;
			while (j < J) {
				A[j - I] = false;
				j = j + i;
			}
		}
		int number = 0;
		for (int i = I; i < J; i++) {
			if (A[i-I] == true) {
				if (true) {
					int index = number+1;
					System.out.println(index+". : "+i);
					number++;
				}
				count = count + 1;
			}
		}
		System.out.println("NUMBER OF PRIMES BETWEEN " + I + " AND " + J + "  :  " + count);
		long endTime = System.currentTimeMillis();
		System.out.println("Run  "+(endTime - startTime) + " ms"); 
	}
}
