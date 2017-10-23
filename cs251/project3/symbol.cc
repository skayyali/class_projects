#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <map>
#include "key.h"
#include "symbol.h"

using namespace std;

map<string,Key> symTable;
int main(int argc, char *argv[]){
   
   if (argc != 2) exit(EXIT_FAILURE);
   
   // Create a Key from the input password
   Symbol symKey((char*) argv[1]);
   
   //initialize the table
   
	symKey.initializeTable();

	
	symKey.createSymTable();	
	
	symKey.decrypt(Key(argv[1]));
}

Symbol::Symbol(char s[]){
 
   char buffer[C+1];
   
   //initialze to encrypted key
   encrypted.keySetString(s);
   
}

void Symbol::initializeTable(){
   
   char buffer[C+1];   

   // Read in table T
   for (int i = 0; i < N; i++) {
      cin.getline(buffer,C+1,'\n');
      buffer[C]=0;
      T[i].keySetString(buffer);
   }
}

void Symbol::createSymTable(){
	string test = "";
	string end = "";
	int i;
	for(i = 0; i<C/2; i++){
		end.append("5");
		test.append("a");
	}
	Key input = encrypted;
	char *testinput = new char[test.length() + 1];
	while(test != end)
	{
		strcpy(testinput, test.c_str());
		for(i = 0; i < C/2 + 1; i++)
			strcat(testinput, "a");
			
		input.keySetString(testinput);
		Key result = input.keySubsetSum(T);
		symTable.insert(pair<string,Key>(test, result));
		int carry = 0;
		if(test[(C/2)-1] == 'z'){
			test[(C/2)-1] = '0';
		}
		else if(test[(C/2)-1] == '5'){
			test[(C/2)-1] = 'a';
			carry+=1;
		}
		else
			test[(C/2)-1] = (char)((int)test[(C/2)-1] + 1);
		for(i=(C/2)-2; i>=0; i--){
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
	strcpy(testinput, test.c_str());
	for(i = 0; i < C/2 + 1; i++)
		strcat(testinput, "a");
	input.keySetString(testinput);
	Key result = input.keySubsetSum(T);
	symTable.insert(pair<string,Key>(test, result));
	delete testinput;
}

string Increment(string test)
{	
	int i;		
	int carry = 0;
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
	return test;
}

Key Symbol::decrypt(Key key){
	string test = "";
	string end = "";
	char* compStr = new char[test.length()/2 + 1];
	strcpy(compStr, "");
	int i;
	for(i = 0; i < C; i++)
	{
		test.append("a");
		end.append("5");
	}
	for(i = 0; i < C/2 + 1; i++)
	{
		strcat(compStr, "5");
	}
	Key input = key;
	Key symVal = symTable[test.substr(0, C/2).c_str()];
	char *firsthalf = new char[test.length() + 1];
	char *secondhalf = new char[test.length() + 1];
	char* teststr = new char[test.length() + 1];
	bool lookup = false;
	while(test != end)
	{

		strcpy(teststr, test.c_str());

		strcpy(firsthalf, "");
		strcpy(firsthalf, test.substr(0, C/2).c_str());

		strcpy(secondhalf, "");
		for(i = 0; i < C/2; i++)
		{
			strcat(secondhalf, "a");
			strcat(firsthalf, "a");
		}
		strcat(secondhalf, test.substr(C/2, C).c_str());

		if(lookup)
		{
			symVal = symTable[test.substr(0, C/2).c_str()];
			lookup = false;
		}

		if(strcmp(test.substr(C/2, C).c_str(), compStr) == 0)
		{
			lookup = true;
		}

		input.keySetString(secondhalf);

		subsetSum.keySet(input.keySubsetSum(T));
		subsetSum.keyAdd(symVal);
		input.keySetString(teststr);

		if(subsetSum.keyEquals(key)){
			input.keyShow();
		}
		test = Increment(test);
	}
	delete teststr;
	delete compStr;
	delete firsthalf;
	delete secondhalf;
	return key;
}
