#include <openssl/rsa.h>
#include "RSA.h"

int padding = RSA_PKCS1_OAEP_PADDING;

void RsaEncrypt(unsigned char* plaintext, unsigned char* ciphertext, int length, char* filename) {
    //create RSA and encrypt
    RSA* rsa = createRSAWithFilename("public.pem", 1);
    
    int res = RSA_public_encrypt(length, plaintext, ciphertext, rsa, padding);
    
    //write encrypted data to .kem file
    FILE *kemFile = fopen(filename, "w");
    if (kemFile == NULL)
    {
       printf("Error opening file!\n");
       exit(1);
    }
    fwrite(ciphertext, res, 1, kemFile);
    fclose(kemFile);
}

void RsaDecrypt(unsigned char* ciphertext, unsigned char* plaintext, int length) {
    RSA * rsa = createRSAWithFilename("private.pem", 0);
    int  res = RSA_private_decrypt(length, ciphertext, plaintext, rsa, padding);
}

RSA * createRSAWithFilename(char * filename, int public) {
    FILE * fp = fopen(filename,"rb");
 
    if (fp == NULL) {
        printf("Unable to open file %s \n",filename);
        return NULL;    
    }

    RSA *rsa= RSA_new() ;
 
    if (public)
        rsa = PEM_read_RSA_PUBKEY(fp, &rsa,NULL, NULL);
    else
        rsa = PEM_read_RSAPrivateKey(fp, &rsa,NULL, NULL);

    fclose(fp);
    return rsa;
}