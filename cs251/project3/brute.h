#ifndef _BRUTE_H_
#define _BRUTE_H_

class Brute {
    private:
    	Key subsetSum;
	Key encrypted;
	Key T[N];

    public:
	Brute(char []);
	void initializeTable();
	Key decrypt(Key);
	


};

#endif
