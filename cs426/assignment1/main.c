#include "hybrid.h"
#include <stdio.h>
#include <string.h>


int main() { //TEST MAIN
    fencrypt("input/1.txt", "test.kem", "test.dem");
    fdecrypt("test.kem", "test.dem", "output/1.output");

    return 0;
}

/*
int main(int argc, char* argv[]) {
    if ( !strcmp(argv[1], "enc") ) {
        fencrypt(argv[2], argv[3], argv[4]);
    }
    else if ( !strcmp(argv[1], "dec") ) {
        fdecrypt(argv[2], argv[3], argv[4]);
    }
    else {
        printf("Invalid option '%s'", argv[1]);
        return 1;
    }
    return 0;
}*/