CFLAGS=-Wall -Wextra -Wformat -Wformat-security -D_FORTIFY_SOURCE=2 -fstack-protector-all -pie -fPIE -Wl,-z,now -Wl,-z,relro

bof: bof.c
	gcc -fno-pie -no-pie -o bof bof.c

hardened: bof.c
	gcc $(CFLAGS) -o bof bof.c

clean:
	rm -f bof
