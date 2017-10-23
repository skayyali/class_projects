#include "hybrid.h"

#include <openssl/rand.h>
#include "AES.h"
#include "RSA.h"


#define MAX_BUF 1000000

void fencrypt(char* inputFile, char* keyEncFile, char* dataEncFile) {
    //generate random key and IV
    unsigned char aesKey[32] = {};
    if (!RAND_bytes(aesKey, 32)) {
        printf("Random byte generation failed\n");
    }
    
    unsigned char iv[64];
    if (!RAND_bytes(iv, 64)) {
        printf("Random byte generation failed\n");
    }
    
    unsigned char encryptedAESkey[MAX_BUF] = {};
    RsaEncrypt(aesKey, encryptedAESkey, 32, keyEncFile);

    AesEncrypt(inputFile, dataEncFile, aesKey, iv);
}


void fdecrypt(char* keyEncFile, char* dataEncFile, char* outputFile) {
    FILE *kemFile = fopen(keyEncFile, "r");
    if (kemFile == NULL) {
       printf("Error opening file!\n");
       exit(1);
    }

    //read plaintext
    char encryptedKEMfile[MAX_BUF] = {};
    int c;
    int i = 0;
    while(1) {
        c = fgetc(kemFile);
        if(feof(kemFile)){
            break;
        }
        encryptedKEMfile[i] = c;
        i++;
    }
    fclose(kemFile);

    //read iv file
    unsigned char iv[64];

    char decryptedKEMfile [MAX_BUF] = {};
    RsaDecrypt(encryptedKEMfile, decryptedKEMfile, i);

    AesDecrypt(dataEncFile, outputFile, decryptedKEMfile, iv);
}