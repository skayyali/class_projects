all:		unique symbol brute encrypt

unique:		unique.cc key.o
		g++ -g -lm unique.cc key.o -o unique

symbol:		symbol.h symbol.cc key.o
		g++ -g -std=c++11 -lm symbol.cc key.o -o symbol

brute:		brute.h key.o brute.cc
		g++ -g -lm brute.cc key.o -o brute

encrypt:	encrypt.cc key.o 
		g++ encrypt.cc key.o -o encrypt

key.o:		key.cc key.h
		g++ -g -c key.cc

clean:		
		rm *.o encrypt brute symbol unique
