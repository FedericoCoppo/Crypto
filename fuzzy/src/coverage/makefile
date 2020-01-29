CFLAGS=-Wall -Wextra -Wformat -Wformat-security -D_FORTIFY_SOURCE=2 -fstack-protector-all -pie -fPIE -Wl,-z,now -Wl,-z,relro

coverage: coverage.c
	gcc $(CFLAGS) -g -o coverage coverage.c

instrument: coverage.c
	gcc $(CFLAGS) -g --coverage -o coverage coverage.c

report-gcov:
	gcov coverage.c
	
report-branch-gcov:
	gcov -b coverage.c

report-lcov:
	lcov -c -o coverage.info -d .
	genhtml -o report coverage.info

clean:
	rm -fr coverage coverage.gcda coverage.gcno coverage.c.gcov coverage.info report
