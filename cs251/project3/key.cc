#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "key.h"

using namespace std;

// return the ith bit of the key
int Key::keyBit(int i) {
   return (digit[i/B] >> (B - 1 - i % B)) & 1;
}

// print out the key in characters, base R, and binary
void Key::keyShow() {
   int i;
   for (i = 0; i < C; i++)
      putchar(ALPHABET[digit[i]]);
   printf("  ");
   for (i = 0; i < C; i++)
      printf("%2d ", digit[i]);
   printf("  ");
   for (i = 0; i < N; i++)
      printf("%d", keyBit(i));
   putchar('\n');
}

//initialize empty key
Key::Key(){
   int i;
   for (i = 0; i < C; i++)
             digit[i] = 0;	
}


// convert from char to integer 0-31
Key::Key(char s[]) {
   int i, j;
   for (i = 0; i < C; i++)
       for (j = 0; j < R; j++)
          if (s[i] == ALPHABET[j])
             digit[i] = j;
}

// checks if the argument key is equal to 
// the current key
bool Key::keyEquals(Key key){
    int i;
    for(i = 0; i < C; i++){
	if(digit[i]!=key.digit[i])
		return false;
    }

    return true;
}

// returns true if key a is greater than 
// equal to key b
bool Key::keyGreaterThan(Key a, Key b){

   int i;
   for(i = 0; i < C; i++){
        if(b.digit[i]>a.digit[i])
                return false;
	if(b.digit[i]<a.digit[i])
		return true;
   }
}

// convert from char to integer 0-31
void Key::keySetString(char s[]) {
   int i, j;
   for (i = 0; i < C; i++)
       for (j = 0; j < R; j++)
          if (s[i] == ALPHABET[j])
             digit[i] = j;
}


void Key::keySet(Key a){
   int i;
   for(i = 0; i < C; i++)
   	digit[i] = a.digit[i];

}

// c = a + b
void Key::keyAdd(Key b)  {
    int i,t;
    int carry = 0;
    for (i = C-1; i >= 0; i--) {
       t = digit[i];	
       digit[i] = (t + b.digit[i] + carry)  % R; 
       carry    = (t + b.digit[i] + carry) >= R; 
    }
}

// compute sum of subset of T[i] for which ith bit of k is 1
Key Key::keySubsetSum(Key T[N])  {
   Key sum; 
   int i;
   for (i = 0; i < N; i++)
      if (keyBit(i)) {
	 sum.keyAdd(T[i]);
         //printf("%2d ", i);           // for debugging
	 //T[i].keyShow();		// for debugging	
      }
   return sum;   
}


