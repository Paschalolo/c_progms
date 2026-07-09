#include <openssl/evp.h>

int main(){
	printf("OPEN SSL VERSION : %s " , OpenSSL_version(OPENSSL_VERSION_STRING));
	return 0;
}
