CFLAGS=-Wall -Wextra -Wformat -Wformat-security -D_FORTIFY_SOURCE=2 -fstack-protector-all -pie -fPIE -Wl,-z,now -Wl,-z,relro

server: string.c
	gcc $(CFLAGS) -o string string.c

clean:
	rm -f string
