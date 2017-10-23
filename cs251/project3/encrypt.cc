/**********************************************************************
 *  Encrypt a file using subset-sum algorithm.
 *
 *  Execution:      % ./encrypt password < rand8.txt
 *                  vbskbezp
 *
 *  Note: need to set C = 8 in key.h before compiling and executing
 *        with rand8.txt.
 *
 **********************************************************************/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "key.h"

using namespace std;

int main(int argc, char *argv[]) {
   int i;
   char buffer[C+1];     	  // temporary string buffer 
   Key T[N];                      // the table T
   Key subsetSum;	
   

   if (argc != 2) exit(EXIT_FAILURE);
   
   // Create a Key from the input password
   Key password((char *) argv[1]);
   
   // Print out input password
   cout<<"   ";
   password.keyShow();
   cout<<endl;

   // Read in table T
   for (i = 0; i < N; i++) {
      cin.getline(buffer,C+1,'\n');
      buffer[C]=0;
      T[i].keySetString(buffer);
   }

   // Compute subset sum
   subsetSum.keySet(password.keySubsetSum(T));

   // Print results
   cout<<endl<<"   ";
   subsetSum.keyShow();
   
   return 0;
}

