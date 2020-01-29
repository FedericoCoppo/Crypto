CFLAGS=-Wall -Wextra -Wformat -Wformat-security -D_FORTIFY_SOURCE=2 -fstack-protector-all -pie -fPIE -Wl,-z,now -Wl,-z,relro

address: address.c
	gcc -g -o address address.c

sanitized: address.c
	gcc -g -fsanitize=address -o address address.c

hardened: address.c
	gcc $(CFLAGS) -g -o address address.c

clean:
	rm -f address
