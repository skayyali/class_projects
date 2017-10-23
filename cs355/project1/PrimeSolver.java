package project1;

import java.util.Scanner;


public class PrimeSolver {
	public static void main (String [] args) {
		long startTime = System.currentTimeMillis();
		//uncomment loop for 1 iteration
		for(int e = 2; e < 13; e++) {
			int n;
			int count = 0;
			Scanner in =  new Scanner(System.in);
			//System.out.println("Enter J:");
			//set n = to desired J;
			n = (int) Math.pow(3,e);
			Boolean [] p = new Boolean[n+1];
			p[0] = false;
			p[1] = false;
			
			for (int i = 2; i <= n; i++) {
				p[i] = true;
			}
			int k = 2;
			while (k <= Math.sqrt(n)) {
				int i = k + k;
				while(i <= n) {
					p[i] = false;
					i = i + k;
				}
				i = k + 1;
				while (i <= Math.sqrt(n) && p[i] == false) {
					i = i + 1;
				}
				k = i;
			}
			int number = 0;
			for (int i = 0; i <= n; i++) {
				if (p[i] == true) {
					count++;
					number++;
					//print list:
					//if (number < 10)
						//System.out.println(i);
				}
			}
			double approx = n/Math.log(n);
			System.out.println("TOTAL PRIMES FOR " + e +" :\t" + count + "\tapprox.: " + approx);
		}
		long endTime = System.currentTimeMillis();
		System.out.println("Run  "+(endTime - startTime) + " ms"); 
	}
	
}
