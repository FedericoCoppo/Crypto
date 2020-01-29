
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/rsa.h>

#define READPUB 0
#define READSEC 1

int fexists(char *file);
void help(char *name);

void rsa_ed(int mode, char *fin, char *fout, char *pemfile)
{
	int size=0,len=0,ks=0;
	RSA *key=NULL;
	FILE *fpin=NULL, *fpout=NULL;
	unsigned char *cipher=NULL,*plain=NULL;
  		
	if (strcmp(fin, fout) == 0) {
		fprintf(stderr,"Error: input and output files must not be the same file.\n");
		exit(EXIT_FAILURE);
	}
	if (mode == 0) {
		fpin = fopen(fin, "r");
		key = (RSA *)readpemkeys(READPUB, pemfile);
       		fpout = fopen(fout, "w");
		ks = RSA_size(key);
		plain = (unsigned char *)malloc(ks * sizeof(unsigned char));
		cipher = (unsigned char*)malloc(ks * sizeof(unsigned char));
		printf("Encrypting '%s' file.\n", fin);
		while(!feof(fpin)) {
			memset(plain,'\0',ks + 1);
			memset(cipher, '\0', ks + 1);	
			len = fread(plain, 1, ks - 11, fpin);
			size = rsa_encrypt(key, plain, len, &cipher);
			fwrite(cipher, 1, size, fpout);
		}
		fclose(fpout);
		fclose(fpin);
		free(cipher);
		free(plain);
		RSA_free(key);
		printf("Done.\n");
	} else if (mode == 1) {
		fpin = fopen(fin, "r");
		key = (RSA *)readpemkeys(READSEC, pemfile);
		fpout = fopen(fout, "w");
		ks = RSA_size(key);
		cipher = (unsigned char*)malloc(ks * sizeof(unsigned char));
		plain = (unsigned char*)malloc(ks * sizeof(unsigned char));
		printf("Decrypting '%s' file.\n", fin);
		while(!feof(fpin)) {
			memset(cipher, '\0', ks);
			memset(plain, '\0', ks);
			if ((len = fread(cipher, 1, ks, fpin)) == 0)
 			break;
         		size = rsa_decrypt(key, cipher, len, &plain);
			fwrite(plain, 1, size, fpout);
       		}
		fclose(fpout);
		fclose(fpin);
		free(plain);
		free(cipher);
		RSA_free(key);
		printf("Done.\n");		
	}
	return;
}


void* readpemkeys(int type, char *pemfile)
{
  FILE *fp;
  RSA *key=NULL;
 
  if(type == READPUB) {
    if((fp = fopen(pemfile,"r")) == NULL) {
      fprintf(stderr,"Error: Public Key file doesn't exists.\n");
      exit(EXIT_FAILURE);
    }
    if((key = PEM_read_RSAPublicKey(fp,NULL,NULL,NULL)) == NULL) {
      fprintf(stderr,"Error: problems while reading Public Key.\n");
      exit(EXIT_FAILURE);
    }
    fclose(fp);
    return key;
  }
  if(type == READSEC) {
    if((fp = fopen(pemfile,"r")) == NULL) {
      fprintf(stderr,"Error: Private Key file doesn't exists.\n");
      exit(EXIT_FAILURE);
    }
    if((key = PEM_read_RSAPrivateKey(fp,NULL,NULL,NULL)) == NULL) {
      fprintf(stderr,"Error: problmes while reading Private Key.\n");
      exit(EXIT_FAILURE);
    }
    fclose(fp);
    if(RSA_check_key(key) == -1) {
      fprintf(stderr,"Error: Problems while reading RSA Private Key in '%s' file.\n",pemfile);
      exit(EXIT_FAILURE);
    } else if(RSA_check_key(key) == 0) {
      fprintf(stderr,"Error: Bad RSA Private Key readed in '%s' file.\n",pemfile);
      exit(EXIT_FAILURE);
    }
    else 
      return key; 
  }
  return key;
}

int rsa_encrypt(void *key, unsigned char *plain, int len, unsigned char **cipher)
{
  int clen=0;
  
  srand(time(NULL));
  if((clen = RSA_public_encrypt(len, plain, *cipher, (RSA*)key, RSA_PKCS1_PADDING)) == -1) {
    fprintf(stderr, "%s\n", ERR_error_string(ERR_get_error(), NULL));
    exit(EXIT_FAILURE);
  } else
    return clen;
}

int rsa_decrypt(void *key, unsigned char *cipher, int len, unsigned char **plain)
{
  int plen=0;
  
  if((plen = RSA_private_decrypt(len, cipher, *plain, (RSA*)key, RSA_PKCS1_PADDING)) == -1) {
    fprintf(stderr, "%s\n", ERR_error_string(ERR_get_error(), NULL));
    exit(EXIT_FAILURE);
  } else
    return plen;
}
