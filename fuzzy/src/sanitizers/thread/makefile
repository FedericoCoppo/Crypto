CFLAGS=-Wall -Wextra -Wformat -Wformat-security -D_FORTIFY_SOURCE=2 -fstack-protector-all -pie -fPIE -Wl,-z,now -Wl,-z,relro

thread: thread.c
	gcc -g -lpthread -o thread thread.c

sanitized: thread.c
	gcc -lpthread -g -fsanitize=thread -o thread thread.c

hardened: thread.c
	gcc -lpthread $(CFLAGS) -g -o thread thread.c

clean:
	rm -f thread
