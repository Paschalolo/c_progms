
/* This program computesthe digest if a message using any algorithm 
 * Authored by Paschal Ahanmisi 
 * Copyright 2024 - 2026 Paschal Ahanmisi 
 */ 

#include <openssl/types.h>
#include <stdio.h>
#include <openssl/evp.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include  <ctype.h>

/* COmpute the digest of an input messgae using a digest algorithm */ 
int main(int argc , char** argv ){
	char* algname ="sha256"; /* default algorithm */ 
	char *msgp = "Good morning!"; 
	EVP_MD_CTX* mdctx  ;
	const EVP_MD* md ; 
	unsigned char digest[EVP_MAX_MD_SIZE];  /*message of the digest */
	unsigned int dsgt_len ; 

	if((argc > 1 ) && strcmp(argv[1],"?")){
		fprintf(stderr , "USage  [[digest name ]] [message]\n");
		return -1;
	}
	
	if(argc >= 3 ){
		algname = argv[1]; 
		msgp = argv[2];
	}
	printf("COmpute tjhe digest of message %s \n" , msgp); 


	md = EVP_get_digestbyname(algname); 

	if(md == NULL){
		fprintf(stderr , "Unknown algortuihm \n");
		return -2; 
	}
	/* certae a new digest context */ 
	mdctx = EVP_MD_CTX_new();
	
	if (!EVP_DigestInit_ex2(mdctx, md, NULL)){
		fprintf(stderr , "EVP_digestINit_ex2() failed");
		EVP_MD_CTX_free(mdctx);
		return -2;
	}

	/* Hash the next chunk of the messgase into the digest context 
	 * calls this once
	 * */ 
	if(!EVP_DigestUpdate(mdctx,msgp,strlen(msgp))){
		fprintf(stderr , "EVP_digestUpdate() failed");
		EVP_MD_CTX_free(mdctx);
		return -4;
	}

	/* Digest is retrieved value from mdctx nad pkace int his digest 
	 * Also return thr elngth of digest */ 
	if(!EVP_DigestFinal_ex(mdctx,digest, &dsgt_len)){
		return -4;
	}
	EVP_MD_CTX_free(mdctx);
	return 0;
}
