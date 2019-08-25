#!/usr/bin/python
import sys
from Crypto.PublicKey import RSA

pub_key = RSA.importKey(open("public_key.pem").read())

s = str(hex(pub_key.n))
c = "const  uint8 modulus[MODULUS_BYTE_SIZE] =\n"
c += "{ \n        "

index = 0
byte_num = 0

while byte_num < 256 :
	c += "0x"
	c += s[index + 2].upper() + s[index + 2 + 1].upper() + 'u'
	
	if byte_num < 255 :
		c += ", "
	# Increment `index` by 1
	index = index + 2
	byte_num = byte_num + 1
	
	if byte_num%16 == 0 and (byte_num!=256):
		c += "\n        "
	elif byte_num%16 == 0:
		c += "\n"	

c += "};\n"	
with open('Cal_Module.c', 'wb') as f:
    f.write(c)	
print "Generating Cal_Module.c file containing modulus:" 	
print c

c = "const  uint8 exponent[EXPONENT_BYTE_SIZE] = { "
s = str(hex(pub_key.e))

# exponent management
index = 0
byte_num = 0
while byte_num < 3 :
	c += "0x"
	if byte_num < 2:
		c += s[index + 2].upper() + s[index + 2 + 1].upper() + 'u'
	else:
		c += s[index + 2].upper() + 'u'
	
	if byte_num < 2 :
		c += ", "
	# Increment `index` by 1
	index = index + 2
	byte_num = byte_num + 1
		
c += " };"

with open('Cal_Exponent.c', 'wb') as f:
    f.write(c)	
print "Generating Cal_Exp.c file containing exponent:" 	
print c 



