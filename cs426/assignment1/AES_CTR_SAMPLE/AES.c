

# include "AES.h"

#include <stdio.h>


int main ()
{
    char* key = "7E9699A56DFED880F1B189105840C94CEB7CFF6FFC5D69E4FE37DF0E431190D3";
    char* iv = "F82203B87DE07DD8E4B7581E161F375A";
    //printf ("\t\tTEST: size: %lu \n", sizeof(key));
    char * plaintext = "I am a good boy. I love music.";
    char ciphertext[256] = { '\0' };
    char dec_text[256] = { '\0' };
    
    AesEncrypt(plaintext, ciphertext, 256, key, iv);
    printf ("ciphertext : \n%s\n\n", ciphertext);
    
    AesEncrypt(ciphertext, dec_text, 256, key, iv);
    printf ("dec_text : \n%s\n\n", dec_text);
    
    return 0;
}