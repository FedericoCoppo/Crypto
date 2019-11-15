/* ============================================================================= **
 **                           OpenSSL course                                     **
 ** ============================================================================ **
 **               +++++++++++++++++++++++++++++++++++++++                        **
 **    Module:    +           certpubkey.c           +                        **
 **               +++++++++++++++++++++++++++++++++++++++                        **
 **                                                                              **
 **  Description: The program implements X.509 certificate reading and printing  **
 **               of some fields.                                                **
 **                                                                              **
 ** ============================================================================ **
 **         Edit                    Data           Authors       		  		 **
 **    First release             13/04/2018        F. Coppo                      **
 ** ============================================================================ */

#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>

// Main program 
int main() {

	const char cert_filestr[] = "./cert.crt";
	EVP_PKEY 	  *pkey = NULL;
	BIO               *certbio = NULL;
	BIO               *outbio = NULL;
	X509              *cert = NULL;
	int ret;
	char *subj;                                     
	char *issuer; 
	ASN1_INTEGER *asn1_serial = NULL;               // Used to print serial number 
                       
	/* ---------------------------------------------------------- *
	 * These function calls initialize openssl for correct work.  *
	 * ---------------------------------------------------------- */
	OpenSSL_add_all_algorithms();
	ERR_load_BIO_strings();
	ERR_load_crypto_strings();

	/* ---------------------------------------------------------- *
	 * Create the Input/Output BIO's.                             *
	 * ---------------------------------------------------------- */
	certbio = BIO_new(BIO_s_file());
	outbio  = BIO_new_fp(stdout, BIO_NOCLOSE);

	/* ---------------------------------------------------------- *
	 * Load the certificate from file (PEM).                      *
	 * ---------------------------------------------------------- */
	ret = BIO_read_filename(certbio, cert_filestr);
	if (! (cert = PEM_read_bio_X509(certbio, NULL, 0, NULL))) {
		BIO_printf(outbio, "Error loading cert into memory\n");
		exit(-1);
	}

	/* ---------------------------------------------------------- *
	 * Extract the certificate's public key data.                 *
	 * ---------------------------------------------------------- */
	if ((pkey = X509_get_pubkey(cert)) == NULL)
		BIO_printf(outbio, "Error getting public key from certificate");

	/* --------------------------------------------------------------------------------*
	 * Extract and print the certificate's version, issuer, subject and serial number  *
	 * ------------------------------------------------------------------------------- */
	if (cert != NULL)
	{
		// Cert. version	
		BIO_printf(outbio, "X509 certificate version: %ld\n\n", X509_get_version(cert) + 1);

		// Cert. issuer  
		subj = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
		if (subj == NULL)
		{
			BIO_printf(outbio, "Error getting issuer from certificate\n");
		}
		else
		{
			BIO_printf(outbio, "CERTIFICATE ISSUER:\n %s\n\n", subj);   
		}

		// Subject .
		issuer = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
		if (issuer == NULL)
		{
			BIO_printf(outbio, "Error getting subject from certificate\n");
		}
		else
		{
			BIO_printf(outbio, "CERTIFICATE'S SUBJECT:\n %s\n\n", issuer); 
		}

		// Serial number .
		asn1_serial = X509_get_serialNumber(cert);
		if (asn1_serial == NULL)
		{
			BIO_printf(outbio, "Error getting serial number from certificate\n");
		}
		else
		{
			BIO_puts(outbio,"CERTIFICATE SERIAL NUMBER:\n ");
			i2a_ASN1_INTEGER(outbio, asn1_serial);
			BIO_puts(outbio,"\n\n");
		}


		BIO_printf(outbio,"CERTIFICATE IS VALID FROM:  ");
		ASN1_TIME_print(outbio,X509_get_notBefore(cert));
		BIO_printf(outbio,"\n\n");

		BIO_printf(outbio,"CERTIFICATE IS VALID UNTIL: ");
		ASN1_TIME_print(outbio,X509_get_notAfter(cert));
		BIO_printf(outbio,"\n\n");
	}	

	/* ---------------------------------------------------------- *
	 * Print the public key information and the key in PEM format *
	 * ---------------------------------------------------------- */
	/* display the key type and size here */
	if (pkey) {

		BIO_printf(outbio,"TYPE OF KEY:\n");

		switch (EVP_PKEY_base_id(pkey)) {
		case EVP_PKEY_RSA:
			BIO_printf(outbio, "%d bit RSA Key\n\n", EVP_PKEY_bits(pkey));
			break;
		case EVP_PKEY_DSA:
			BIO_printf(outbio, "%d bit DSA Key\n\n", EVP_PKEY_bits(pkey));
			break;
		default:
			BIO_printf(outbio, "%d bit non-RSA/DSA Key\n\n", EVP_PKEY_bits(pkey));
			break;
		}


	}

	if(!PEM_write_bio_PUBKEY(outbio, pkey))
		BIO_printf(outbio, "Error writing public key data in PEM format");

	EVP_PKEY_free(pkey);
	X509_free(cert);
	BIO_free_all(certbio);
	BIO_free_all(outbio);
	free(issuer); 
	free(subj);

	exit(0);
}
