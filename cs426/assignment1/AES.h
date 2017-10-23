#ifndef _AES_H_   /* Include guard */
#define _AES_H_

#include <openssl/aes.h>
#include <openssl/rand.h> 
#include <openssl/hmac.h>
#include <openssl/buffer.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


void AesEncrypt(char* inputFile, char* outputFile, const unsigned char* enc_key, unsigned char* iv);

void AesDecrypt(char* inputFile, char* outputFile, const unsigned char* dec_key, unsigned char* iv);

#endif 