#include"mbedtls/rsa.h"
#include"mbedtls/pkcs1.h"
#include"mbedtls/entropy.h"
#include"mbedtls/ctr_drbg.h"
#include"mbedtls/error.h"
#include<stdio.h>
#include<string.h>

#define KEY_SIZE 2048  
#define EXPONENT 65537
#define BUFFER_SIZE 1024

void print_mbedtls_error(const char*message,int ret){
char error_buf[100];
mbedtls_strerror(ret,error_buf,100);
printf("%s:%s\n",message,error_buf);
}

int main(){
int ret;
mbedtls_rsa_context rsa;
mbedtls_entropy_context entropy;
mbedtls_ctr_drbg_context ctr_drbg;
const char*pers="rsa_genkey";

unsigned char buf[BUFFER_SIZE];
unsigned char encrypted[BUFFER_SIZE];
unsigned char decrypted[BUFFER_SIZE];
size_t olen=0;

mbedtls_rsa_init(&rsa,MBEDTLS_RSA_PKCS_V15,0);
mbedtls_ctr_drbg_init(&ctr_drbg);
mbedtls_entropy_init(&entropy);

if((ret = mbedtls_ctr_drbg_seed(&ctr_drbg,mbedtls_entropy_func,&entropy,(const unsigned char*)pers,strlen(pers))) !=0){
print_mbedtls_error("mbedtls_ctr_drbg_seed",ret);
goto exit;
}

if((ret = mbedtls_rsa_gen_key(&rsa,mbedtls_crt_drbg_random,&ctr_drbg,KEY_SIZE,EXPONENT))!= 0){
print_mbedtls_error("mbedtls_rsa_gen_key",ret);
goto exit;
}

const char*message="HELLO,WORLD!";
print("original message:%s\n",message);


if((ret = mbedtls_rsa_pkcs1_encrypt(&rsa,mbedtls_crt_drbg_random,&ctr_drbg,MBEDTLS_RSA_PUBLIC,strlen(message),(const unsigned char*)message,encrypted))!= 0){
print_mbedtls_error("mbedtls_rsa_pkcs1_encrypt",ret);
goto exit;
}

printf("Encrypted message:");
for(size_t i=0;i<rsa.len;i++){
printf("%02X",encrypted[i]);
}

printf("\n");

if((ret = mbedtls_rsa_pkcs1_decrypt(&rsa,mbedtls_crt_drbg_random,&ctr_drbg,MBEDTLS_RSA_PRIVATE,&olen,encrypted,decrypted,BUFFER_SIZE))!= 0){
print_mbedtls_error("mbedtls_rsa_pkcs1_decrypt",ret);
goto exit;
}

printf("Decrypted message:%s\n",decrypted);

exit:

mbedtls_rsa_free(&rsa);
mbedtls_ctr_drbg_free(&ctr_drbg);
mbedtls_entropy_free(&entropy);

return ret;
}