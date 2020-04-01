
# Description
The program reads the Issuer, the Serial Number and Subject fields of an X.509 certificate
To Run the program:
- keep a x.509 certificate (cert.crt) 
-  Insert in the same folder the certpubkey.c file and the X.509 certificate 
- from the folder launch following commands (compile and execute the program):
      gcc -o certpubkey certpubkey.c -lcrypto -lssl -L /usr/local/lib/
     ./certpubkey
 

```
certpubkey.c
```

The program output :should be
CERTIFICATE ISSUER
CERTIFICATE SUBJECT
CERTIFICATE SERIAL NUMBER
CERTIFICATE VALIDITY (FROM, UNTIL)
TYPE OF KEY
PUBLIC KEY PRINTING
