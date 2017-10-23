#ifndef _SYMBOL_H_
#define _SYMBOL_H_

using namespace std;

class Symbol {
    private:
    	Key subsetSum;
	Key encrypted;
	Key T[N];
	map<string,Key> symTable;

    public:
	Symbol(char []);
	void initializeTable();
        Key decrypt(Key);
	void createSymTable();
};

#endif
