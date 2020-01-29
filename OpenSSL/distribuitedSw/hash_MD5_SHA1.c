#include <fcntl.h>
#include <openssl/evp.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char **argv) {
        EVP_MD_CTX *md;
        unsigned char md_value[EVP_MAX_MD_SIZE];
        int fd,n,i,md_len;
        unsigned char buf[1024];

	md = EVP_MD_CTX_new();

        if(argc < 2) {
                printf("Please give a filename to compute the SHA-1 digest on\n");
                return 1;
        }
        OpenSSL_add_all_digests();

        EVP_MD_CTX_init(md);
        EVP_DigestInit_ex(md, EVP_sha1(), NULL);

        if((fd = open(argv[1],O_RDONLY) ) == -1) {
                printf("Couldnt open input file, try again\n");
                return 1;
        }
        while((n = read(fd,buf,1024)) > 0)
                EVP_DigestUpdate(md, buf,n);
        if(EVP_DigestFinal_ex(md, md_value, &md_len) != 1) {
                printf("Digest computation problem\n");
                return 1;
        }
//      EVP_MD_CTX_cleanup(&md);
	EVP_MD_CTX_free(md);      

        printf("Digest is: ");
        for(i = 0; i < md_len; i++) printf("%02x", md_value[i]);
        printf("\n");

return 0;
}
