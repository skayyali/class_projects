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

// Reference: http://www.gurutechnologies.net/blog/aes-ctr-encryption-in-c/
// But, the code is mostly rewritten for custom purpose.

// The method for encryption and decryption are same.
void AesEncrypt(unsigned char* plaintext, char* ciphertext, int length, const unsigned char* enc_key, char* iv)
{     
    AES_KEY key;
    
    //printf ("\t\t00000000005\n");
    if (enc_key == NULL) {
        printf ("DEBUG : enc_key is the problem.");
    }
    
	//Initializing the encryption KEY
	if (AES_set_encrypt_key(enc_key, 256, &key) < 0)
    {
        printf("Could not set encryption key.");
        exit(1); 
    }
    
    
    
    unsigned char ivec[AES_BLOCK_SIZE];	 
    unsigned int num; 
    unsigned char ecount[AES_BLOCK_SIZE];
    
    //printf ("\t\t00000000006\n");
    
    /* aes_ctr128_encrypt requires 'num' and 'ecount' set to zero on the first call. */
    num = 0;
    memset(ecount, 0, AES_BLOCK_SIZE);
    
    //printf ("\t\t00000000007\n");

    /* Initialise counter in 'ivec' to 0 */
    memset(ivec + 16, 0, 16);
    
    //printf ("\t\t00000000008\n");

    /* Copy IV into 'ivec' */
    memcpy(ivec, iv, 16);
    
    //printf ("\t\t00000000009\n");
    
    // encrypt the data.
    AES_ctr128_encrypt(plaintext, ciphertext, length, &key, ivec, ecount, &num);
    //ciphertext[length] = '\0';
    
    //printf ("\t\t00000000010\n");
}

void AesDecrypt(unsigned char* ciphertext, char* plaintext, int length, const unsigned char* dec_key, char* iv)
{
    AesEncrypt(ciphertext, plaintext, length, dec_key, iv);
}

#endif 