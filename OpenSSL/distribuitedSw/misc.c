

void help(char *name)
{
	printf("Usage:\n");
	printf("%s -h\t:displays this help\n",name);
	printf("%s -e <-rsa> <file_to_crypt> <file_output> [rsa_pub.pem]]\t:encrypts file_to_crypt with choosen cipher.\n",name);
	printf("%s -d <-rsa> <file_to_decrypt> <file_output> [rsa_sec.pem]\t:decrypts file_to_decrypt with choosen cipher.\n",name);
	return;
}

/*
 * fexists() checks for the existence of a given file.
 * return 0 if the file doesn't exist and 1 if it exists.
 */
int fexists(char *file)
{	
	FILE *fp;
	if ((fp = fopen(file,"r")) == NULL) {
		return 0;
	} else {
		fclose(fp);
		return 1;
	}
}
