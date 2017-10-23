#ifndef KEY_H
#define KEY_H

#define C 6

#define B 5          // number of bits per character
#define R (1 << B)   // size of alphabet (32)
#define N (B * C)    // number of bits per password

#define ALPHABET "abcdefghijklmnopqrstuvwxyz012345"

// base 64 alphabet
// #define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"


class Key{
    private:
        
	/* An extended precision base R integer consisting of C digits*/
        char digit[C];

    public:
    	/* Default Constructor */
	Key();

	/* Initialize the Key from a character string */
        Key(char[]);

	/* Checks if the argument Key is equal to the current Key */
	bool keyEquals(Key);

	/* Compares if a key is greater than another */
	bool keyGreaterThan(Key a, Key b);
	
	/* Print the contents of the Key */
        void keyShow();

	/* Assign the argument Key to the current Key */
	void keySet(Key);

	/* Assign the Key generated from the argument string to the current Key */
	void keySetString(char[]);

	/* Add the argument Key to the current Key */
        void keyAdd(Key);

	/* Add the subset of the integers T[i] that are 
	   indexed by the bits of k and return subset sum. Do sum mod 2^N. */
        Key keySubsetSum(Key T[N]);

	/* Return the ith bit of the Key */
        int keyBit(int);
};




#endif
