#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include </usr/include/stdlib.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define IV "0xdeadbeefdeadbeef"

int main(int argc, char **argv) {
        EVP_CIPHER_CTX *ctx;
        unsigned char key[1024],iv[1024],ibuf[1024],obuf[1024];
        int rfd, wfd,keyfd,ilen,olen,tlen;
        int l = 0;
	int fd;
	int key_size;

	ctx=EVP_CIPHER_CTX_new();

        if(argc < 3) {
                printf("Usage: %s infile outfile\n",argv[0]);
                exit(128);
        }


        memcpy(iv,IV,sizeof(IV));
        key[0] = 0;

/*      while(l < 256) {
                char b[128];
		sprintf(b,"%lu",RAND_load_file("/dev/random",128));
                strcat(key,b);
                l = strlen(key);
        }
	*/
	key_size=EVP_CIPHER_key_length(EVP_aes_256_cbc());
	RAND_bytes(key,key_size);


        keyfd = creat(".key",0644);
        write(keyfd,key,256);
        close(keyfd);

 	EVP_CIPHER_CTX_init(ctx);       
        if(!EVP_CipherInit_ex(ctx, EVP_aes_256_cbc(),NULL,key, iv,1) ) {
        printf("Couldnt initialize cipher\n");
        return 1;
}
/* 1 for encrypt, 0 for decrypt */

        if((rfd = open(argv[1],O_RDONLY) ) == -1) {
                printf("Couldnt open input file\n");
                exit(128);
        }
        if((wfd = creat(argv[2],0644) ) == -1) {
                printf("Couldn't open output file for writing\n");
                exit(128);
        }

        while((ilen = read(rfd,ibuf,1024) ) > 0) {
                if(EVP_CipherUpdate(ctx,obuf,&olen,ibuf,ilen)){
                        write(wfd,obuf,olen);
                }
                else {
                        printf("Encryption error\n");
                        return 1;
                }

        }
        if(!EVP_CipherFinal_ex(ctx,obuf+olen,&tlen)) {
                printf("Trouble with padding the last block\n");
                return 1;
        }
        write(wfd,obuf+olen,tlen);
//        EVP_CIPHER_CTX_cleanup(&ctx);
        EVP_CIPHER_CTX_free(ctx);
        close(rfd);
        close(wfd);

        printf("AES 256 CBC encryption complete\n");
        printf("Secret key is saved to file .key\n");

        return 0;
}

