CFLAGS=-Wall -Wextra -Wformat -Wformat-security -D_FORTIFY_SOURCE=2 -fstack-protector-all -pie -fPIE -Wl,-z,now -Wl,-z,relro

undefined: undefined.c
	gcc -g -o undefined undefined.c

sanitized: undefined.c
	gcc -g -fsanitize=undefined -o undefined undefined.c

hardened: undefined.c
	gcc $(CFLAGS) -g -o undefined undefined.c

clean:
	rm -f undefined
