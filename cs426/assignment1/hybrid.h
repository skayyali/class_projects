#ifndef _HYBRID_H_   /* Include guard */
#define _HYBRID_H_


void fencrypt(char* inputFile, char* keyEncFile, char* dataEncFile);

void fdecrypt(char* keyEncFile, char* dataEncFile, char* outputFile);


#endif 