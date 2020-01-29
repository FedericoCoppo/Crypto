
#include "unisfed2.h"

int main(int argc, char *argv[])
{
	if (argc == 1 || strcmp(argv[1],"-h") == 0 || ((strcmp(argv[1],"-e") != 0 && strcmp(argv[1],"-d") != 0 && strcmp(argv[1],"-fh") != 0 && strcmp(argv[1],"-fc") != 0 && strcmp(argv[1], "-grsa") != 0)))
		help(argv[0]);
	else if (strcmp(argv[1],"-d") == 0 && (argc == 5 || argc == 6) && (strcmp(argv[2],"-idea") == 0 || strcmp(argv[2],"-des") == 0 || strcmp(argv[2],"-bf") == 0 || strcmp(argv[2], "-rsa") == 0)) {
		if (strcmp(argv[2],"-idea") == 0) {
			if (fexists(argv[3]) == 1)
//				idea_encrypt_decrypt(IDEA_DECRYPT,argv[3],argv[4]);
				;
			else fprintf(stderr,"Error: input file not found.\n");	
		} else if (strcmp(argv[2],"-des") == 0) {
			if (fexists(argv[3]) == 1) 
//				des_encrypt_decrypt(DES_DECRYPT,argv[3],argv[4]);
				;
			else fprintf(stderr,"Error: input file not found.\n");
		} else if (strcmp(argv[2],"-bf") == 0) {
			if (fexists(argv[3]) == 1) 
//				bf_encrypt_decrypt(BF_DECRYPT,argv[3],argv[4]);
				;
			else fprintf(stderr,"Error: input file not found.\n");
		} else if (strcmp(argv[2],"-rsa") == 0) {
			if (fexists(argv[3]) == 1)
				rsa_ed(1, argv[3], argv[4], argv[5]);
			else fprintf(stderr,"Error: input file not found.\n");
		} else;
	} else if (strcmp(argv[1],"-e") == 0 && (argc == 5 || argc == 6) && (strcmp(argv[2],"-idea") == 0 || strcmp(argv[2],"-des") == 0 || strcmp(argv[2],"-bf") == 0 || strcmp(argv[2], "-rsa") == 0)) {
		if (strcmp(argv[2],"-idea") == 0) {
			if (fexists(argv[3]) == 1)
//				idea_encrypt_decrypt(IDEA_ENCRYPT,argv[3],argv[4]);
				;
			else fprintf(stderr,"Error: input file not found.\n");	
		} else if (strcmp(argv[2],"-des") == 0) {
			if (fexists(argv[3]) == 1) 
//				des_encrypt_decrypt(DES_ENCRYPT,argv[3],argv[4]);
				;
			else fprintf(stderr,"Error: input file not found.\n");
		} else if (strcmp(argv[2],"-bf") == 0) {
			if (fexists(argv[3]) == 1) 
//				bf_encrypt_decrypt(BF_ENCRYPT,argv[3],argv[4]);
				;				
			else fprintf(stderr,"Error: input file not found.\n");
		} else if (strcmp(argv[2],"-rsa") == 0) {
			if (fexists(argv[3]) == 1)
				rsa_ed(0, argv[3], argv[4], argv[5]);
			else fprintf(stderr,"Error: input file not found.\n");
		} else;
	} else if (strcmp(argv[1],"-fh") == 0 && argc == 3) {
		if (fexists(argv[2]) == 1) 
//			md5hash(argv[2]);
			;
		else fprintf(stderr,"Error: input file not found.\n");
	} else if (strcmp(argv[1],"-fc") == 0 && argc == 4) {
		if (fexists(argv[2]) == 1 && fexists(argv[3]) == 1) 
//			md5cmp(argv[2],argv[3]);
			;
		else fprintf(stderr,"Error: input files not found.\n");
	} else if (strcmp(argv[1], "-grsa") == 0 && argc == 5)
//		genkey(atoi(argv[2]), argv[3], argv[4]);
		;
	else 
		help(argv[0]);
	return 0;
}

