
/* A simple encryption and decryotion program -- basic sequence of steps 
 * Authored by Paschal Ahanmisi 
 * 2022-2026
 */ 

#include <sched.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/blowfish.h>


constexpr int OPEN_SUCCESS = 1 ;

#define IVLEN 16
#define KEYLEN 16

#define INSIZE 1024
#define OUTSIZE (INSIZE + IVLEN)

/* these are shared encryption and decryption */ 
unsigned char iv[IVLEN + 1] = "0000000000000001"; 
unsigned char key[KEYLEN + 1] = "Axy3pzLk%8q#0)yH"; 

/* Print the ciphertext */ 
void print_cipher_text(unsigned char* buf , unsigned int buflen){

	unsigned int i = 0 ; 
	printf("0x");
	if(buf == NULL) return ;
	for(; i < buflen ; i++){
		printf("%02x", buf[i]);
	}
	printf("\n");
}

int encrypt(unsigned char* inbuf , int inlen , unsigned char*outbuf , int* outlen){
	EVP_CIPHER_CTX* ctx = NULL ; 
	int outlen1 , outlen2 ; 
	int totallen  = 0 ; 
	int ret ; 

	if(inbuf == NULL || outbuf == NULL || outlen == NULL){
		return -1;
	}
	*outlen = 0 ; 
	/* Create cipher text */ 
	ctx =EVP_CIPHER_CTX_new();
	if(ctx == NULL){
		fprintf(stderr , "Error encrpyt() ;\n");
		return -2;
	}

	ret = EVP_EncryptInit_ex(ctx,EVP_aes_256_cbc(), NULL , key , iv);
	if(!ret) {
		EVP_CIPHER_CTX_free(ctx);
		return -2;
	}

	outlen = 0 ; 
	if(EVP_EncryptUpdate(ctx,outbuf ,&outlen1, inbuf,inlen ) != 1){
		EVP_CIPHER_CTX_free(ctx);
		return -3 ; 
	}

	totallen = totallen + outlen1 ; 
	*outlen = totallen ; 

	outlen2 = 0 ; 
	if(EVP_EncryptFinal_ex(ctx, outbuf+totallen , &outlen2) != 1){
		EVP_CIPHER_CTX_free(ctx);
		return -4;
	}
		EVP_CIPHER_CTX_free(ctx);
		return 0;
}
