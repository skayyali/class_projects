#ifndef _RSA_H_   /* Include guard */
#define _RSA_H_

#include <openssl/rsa.h>

#include <openssl/rand.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>

void RsaEncrypt(unsigned char* plaintext, unsigned char* ciphertext, int length, char* filename);

void RsaDecrypt(unsigned char* ciphertext, unsigned char* plaintext, int length);

RSA* createRSAWithFilename(char * filename, int public);

#endif 