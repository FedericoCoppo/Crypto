#!/bin/bash
echo '****starting sign  ******'
cp file.bin fileSigned.bin
binaryfile=fileSigned.bin
openssl dgst -sha256 -sign private.pem -out sign $binaryfile
cat sign >> $binaryfile
rm sign
echo '**** file signed  ******'