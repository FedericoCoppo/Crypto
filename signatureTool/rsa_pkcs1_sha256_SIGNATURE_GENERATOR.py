#!/usr/bin/python
import sys
from Crypto.PublicKey import RSA
from Crypto.Signature import PKCS1_v1_5
from Crypto.Hash import SHA256
key = RSA.importKey(open("privKey.pem").read())
with open("file.bin", "rb") as binary_file:
	data = binary_file.read()
print ("Size of file to be signed (byte #):") 
print (sys.getsizeof(data))

print ("\nFile content (binary):")
print (data)
print ("\nFile content (hex)")
print (data.encode('hex'))

h = SHA256.new(data)
p = PKCS1_v1_5.new(key)
signature = p.sign(h)
signature_trim = p.sign(h)[:-1] # will give same output as openssl dgst -sign
print ("\nSignature (binary):")
print (signature_trim)
print ("\nSignature (hex)")
print (signature.encode('hex'))

