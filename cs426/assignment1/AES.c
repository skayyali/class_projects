#include "AES.h"

#define MAX_BUF 1000000

void AesEncrypt(char* inputFile, char* outputFile, const unsigned char* enc_key, unsigned char* iv) {
    FILE *input = fopen(inputFile, "r");
    if (input == NULL) {
       printf("Error opening file6!\n");
       exit(1);
    }
    //write iv to dem
    FILE *outFile = fopen(outputFile, "w");
    if (outFile == NULL) {
       printf("Error opening file!\n");
       exit(1);
    }
    fwrite(iv, 64, 1, outFile);


    //read plaintext
    char plaintext[MAX_BUF] = {};
    int size = 0;
    int c;
    while(1) {
    	c = fgetc(input);
    	if(feof(input))
    		break;
    	plaintext[size] = c;
    	size++;
    }
    fclose(input);

    //encrypt plaintext
    AES_KEY key;

    if (enc_key == NULL) {
        printf ("DEBUG : enc_key is the problem.");
    }
    
	if (AES_set_encrypt_key(enc_key, 256, &key) < 0) {
        printf("Could not set encryption key.");
        exit(1); 
    }

    unsigned char ivec[AES_BLOCK_SIZE];	 
    unsigned int num; 
    unsigned char ecount[AES_BLOCK_SIZE];

    num = 0;
    memset(ecount, 0, AES_BLOCK_SIZE);
    memset(ivec + 8, 0, 8);
    memcpy(ivec, iv, 8);

    unsigned char my_data[16], output[16];
    int i;
    char ciphertext[MAX_BUF] = {};
    int counter = 0;
    for (i = 1; i < (double)size/16+1; i++) {
        memset(my_data, 0, 16);
        memcpy(my_data, plaintext+((i-1)*16), 16);
        AES_ctr128_encrypt((unsigned char*)my_data, (unsigned char*)output, 16, &key, ivec, ecount, &num);
        memcpy(ciphertext+((i-1)*16), output, 16);
        counter++;
    }
    fwrite(ciphertext, size, 1, outFile);
    fclose(outFile);
}

void AesDecrypt(char* inputFile, char* outputFile, const unsigned char* dec_key, unsigned char* iv) {
    //AesEncrypt(inputFile, outputFile, dec_key, iv);
    FILE *input = fopen(inputFile, "r");
    if (input == NULL) {
       printf("Error opening file6!\n");
       exit(1);
    }
    //read iv from dem
    fread(iv, 64, 1, input);


    //read encrypted file
    char plaintext[MAX_BUF] = {};
    int size = 0;
    int c;
    while(1) {
        c = fgetc(input);
        if(feof(input))
            break;
        plaintext[size] = c;
        size++;
    }
    fclose(input);

    //decrypt plaintext (ciphertext)
    AES_KEY key;

    if (dec_key == NULL) {
        printf ("DEBUG : dec_key is the problem.");
    }
    
    if (AES_set_encrypt_key(dec_key, 256, &key) < 0) {
        printf("Could not set encryption key.");
        exit(1); 
    }

    unsigned char ivec[AES_BLOCK_SIZE];  
    unsigned int num; 
    unsigned char ecount[AES_BLOCK_SIZE];

    num = 0;
    memset(ecount, 0, AES_BLOCK_SIZE);
    memset(ivec + 8, 0, 8);
    memcpy(ivec, iv, 8);

    unsigned char my_data[16], output[16];
    int i;
    char ciphertext[MAX_BUF] = {};
    int counter = 0;
    
    for (i = 1; i < (double)size/16+1; i++) {
        memset(my_data, 0, 16);
        memcpy(my_data, plaintext+((i-1)*16), 16);
        AES_ctr128_encrypt((unsigned char*)my_data, (unsigned char*)output, 16, &key, ivec, ecount, &num);
        memcpy(ciphertext+((i-1)*16), output, 16);
        counter++;
    }

    //print .output file
    FILE *outFile = fopen(outputFile, "w");
    if (outFile == NULL) {
       printf("Error opening file!\n");
       exit(1);
    }
    fwrite(ciphertext, size, 1, outFile);
    fclose(outFile);
}