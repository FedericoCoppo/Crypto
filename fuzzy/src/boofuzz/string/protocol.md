SUPER-SIMPLE WORD PROTOCOL
==========================

Ask the server to do some dumb word operations.
A case-sensitive textual TCP connection.

Typical work-flow:

1. authentication
2. ask stuff
3. close connection

Authentication
--------------

client:
	user <username>\n
server:
	hello <username>\n

client:
	password <password>\n
server:
	welcome <username>\n (authentication ok)
	bye <username>\n     (authentication failed)

Ask stuff
---------

client:
	length <word>\n
server:
	answer <number>\n (return the word length)

client:
	isinteger <word>\n
server:
	answer true\n  (the word is an integer)
	answer false\n (the word is not an integer)

client:
	double <word>\n
server:
	answer <word><word>\n (double <word>)

Close connection
----------------

client:
	bye <username>\n
server:
	bye <username>\n
