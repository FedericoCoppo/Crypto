CFLAGS=-Wall -Wextra -Wformat -Wformat-security -D_FORTIFY_SOURCE=2 -fstack-protector-all -pie -fPIE -Wl,-z,now -Wl,-z,relro

echo: echo.c
	gcc $(CFLAGS) -o echo echo.c

sanitized: echo.c
	gcc -g -fsanitize=address -fsanitize=leak -o echo echo.c

process-monitor:
	python ../process_monitor_unix.py -c crash.log > monitor.log

clean:
	rm -f echo fuzzing.log monitor.log crash.log
