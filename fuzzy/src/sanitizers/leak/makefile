CFLAGS=-Wall -Wextra -Wformat -Wformat-security -D_FORTIFY_SOURCE=2 -fstack-protector-all -pie -fPIE -Wl,-z,now -Wl,-z,relro

leak: leak.c
	gcc -g -o leak leak.c

sanitized: leak.c
	gcc -g -fsanitize=leak -o leak leak.c

hardened: leak.c
	gcc $(CFLAGS) -g -o leak leak.c

clean:
	rm -f leak
