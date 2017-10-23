#include <iostream>
#include <stdlib.h>
#include "key.h"
#include "brute.h"
#include <string.h>
#include <stdio.h>

using namespace std;


int main(int argc, char *argv[]){
   
   if (argc != 2) exit(EXIT_FAILURE);
   
   // Create a Key from the input password
   Brute bruteKey((char*) argv[1]);
   
   //initialize the table
   bruteKey.initializeTable();
   
   //Add code here
	bruteKey.decrypt(Key(argv[1]));

}

Brute::Brute(char s[]){
 
   char buffer[C+1];
   
   //initialze to encrypted key
   encrypted.keySetString(s);
   
}

void Brute::initializeTable(){
   
   char buffer[C+1];   

   // Read in table T
   for (int i = 0; i < N; i++) {
      cin.getline(buffer,C+1,'\n');
      buffer[C]=0;
      T[i].keySetString(buffer);
   }
}

Key Brute::decrypt(Key brute){
	string test = "";
	string end = "";
	int i;
	for(i = 0; i<C; i++){
		test.append("a");
		end.append("5");
	}
	Key input = brute;
	char *testinput = new char[test.length() + 1];
	int carry = 0;
	int temp;
	
	while(test != end)
	{
		strcpy(testinput, test.c_str());
		input.keySetString(testinput);
		subsetSum.keySet(input.keySubsetSum(T));
		int carry = 0;
		int temp;
		if(subsetSum.keyEquals(brute)){
			input.keyShow();
		}
		if(test[C-1] == 'z'){
			test[C-1] = '0';
		}
		else if(test[C-1] == '5'){
			test[C-1] = 'a';
			carry+=1;
		}
		else
			test[C-1] = (char)((int)test[C-1] + 1);
		for(i=C-2; i>=0; i--){
			if(carry != 0)
			{
				carry--;
				switch(test[i])
				{
					case 'a': test[i] = 'b' + carry;
						carry = 0;
					break;
					case 'b': test[i] = 'c' + carry;
						carry = 0;
					break;
					case 'c': test[i] = 'd' + carry;
						carry = 0;
					break;
					case 'd': test[i] = 'e' + carry;
						carry = 0;
					break;
					case 'e': test[i] = 'f' + carry;
						carry = 0;
					break;
					case 'f': test[i] = 'g' + carry;
						carry = 0;
					break;
					case 'g': test[i] = 'h' + carry;
						carry = 0;
					break;
					case 'h': test[i] = 'i' + carry;
						carry = 0;
					break;
					case 'i': test[i] = 'j' + carry;
						carry = 0;
					break;
					case 'j': test[i] = 'k' + carry;
						carry = 0;
					break;
					case 'k': test[i] = 'l' + carry;
						carry = 0;
					break;
					case 'l': test[i] = 'm' + carry;
						carry = 0;
					break;
					case 'm': test[i] = 'n' + carry;
						carry = 0;
					break;
					case 'n': test[i] = 'o' + carry;
						carry = 0;
					break;
					case 'o': test[i] = 'p' + carry;
						carry = 0;
					break;
					case 'p': test[i] = 'q' + carry;
						carry = 0;
					break;
					case 'q': test[i] = 'r' + carry;
						carry = 0;
					break;
					case 'r': test[i] = 's' + carry;
						carry = 0;
					break;
					case 's': test[i] = 't' + carry;
						carry = 0;
					break;
					case 't': test[i] = 'u' + carry;
						carry = 0;
					break;
					case 'u': test[i] = 'v' + carry;
						carry = 0;
					break;
					case 'v': test[i] = 'w' + carry;
						carry = 0;
					break;
					case 'w': test[i] = 'x' + carry;
						carry = 0;
					break;
					case 'x': test[i] = 'y' + carry;
						carry = 0;
					break;
					case 'y': test[i] = 'z' + carry;
						carry = 0;
					break;
					case 'z': test[i] = '0' + carry;
						carry = 0;
					break;
					case '0': test[i] = '1' + carry;
						carry = 0;
					break;
					case '1': test[i] = '2' + carry;
						carry = 0;
					break;
					case '2': test[i] = '3' + carry;
						carry = 0;
					break;
					case '3': test[i] = '4' + carry;
						carry = 0;
					break;
					case '4': test[i] = '5' + carry;
						carry = 0;
					break;
					case '5': test[i] = 'a' + carry;
						carry = 1;
					break;
				}
			}
	
		}
	}
	delete testinput;
	return brute;
		
}

