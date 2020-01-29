#include <fcntl.h>
#include <unistd.h>
#include <openssl/evp.h>
#include <string.h>

#define IV "0xdeadbeefdeadbeef"

int main(int argc, char **argv) {
        EVP_CIPHER_CTX *ctx;
        unsigned char key[1024],iv[1024],ibuf[1024],obuf[1024];
        int rfd, wfd,keyfd,ilen,olen,tlen;
        int l = 0;

	ctx=EVP_CIPHER_CTX_new();

        if(argc < 3) {
                printf("Usage: %s infile outfile\n",argv[0]);
                exit(128);
        }


        memcpy(iv,IV,sizeof(IV));
        key[0] = 0;

        keyfd = open(".key",O_RDONLY);
        read(keyfd,key,256);
        close(keyfd);


        EVP_CIPHER_CTX_init(ctx);
/* last parameter 1 for encrypt, 0 for decrypt */
        if(!EVP_CipherInit_ex(ctx, EVP_aes_256_cbc(),NULL,key, iv,0) ) {
        printf("Couldnt initialize cipher\n");
        return 1;
}

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
                        printf("Decryption error\n");
                        return 1;
                }

        }
        if(!EVP_CipherFinal_ex(ctx,obuf+olen,&tlen)) {
                printf("Trouble with unpadding the last block\n");
                return 1;
        }
        write(wfd,obuf+olen,tlen);
//        EVP_CIPHER_CTX_cleanup(&ctx);
        EVP_CIPHER_CTX_free(ctx);
        close(rfd);
        close(wfd);

        printf("AES 256 CBC decryption complete\n");

        return 0;
}
