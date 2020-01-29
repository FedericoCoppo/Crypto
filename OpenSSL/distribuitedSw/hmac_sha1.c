#include <fcntl.h>
#include <openssl/hmac.h>
#include <unistd.h>
#include <string.h>

#define KEY "deadbeefdeadbeef"

int main(int argc,char **argv) {
        HMAC_CTX *hmac;

        int fd,n,i,len;
        unsigned char buf[1024],hmac_value[1024];

	hmac = HMAC_CTX_new();

        if(argc < 2) {
                printf("Please give a filename to compute the HMAC on\n");
                return 1;
        }

//        HMAC_CTX_init(hmac);

        HMAC_Init_ex(hmac,KEY,strlen(KEY),EVP_sha1(),NULL);


        if((fd = open(argv[1],O_RDONLY) ) == -1) {
                printf("Couldnt open input file, try again\n");
                return 1;
        }
        while((n = read(fd,buf,1024)) > 0)
                HMAC_Update(hmac, buf, n);
        HMAC_Final(hmac, hmac_value, &len);

//        HMAC_CTX_cleanup(&hmac);
	HMAC_CTX_free(hmac);        
        printf("Digest is: ");
        for(i = 0; i < len; i++) printf("%02x", hmac_value[i]);
        printf("\n");

return 0;


}

