CFLAGS=-Wall -Wextra -Wformat -Wformat-security -D_FORTIFY_SOURCE=2 -fstack-protector-all -pie -fPIE -Wl,-z,now -Wl,-z,relro

address: address.c
	gcc -o address address.c

fuzzing: address.c
	afl-gcc -g $(CFLAGS) $(CFLAGS) -g -o address address.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -i inputs -o logs ./address @@

fuzzing-6: address.c
	export AFL_CC="/usr/bin/gcc-6"; afl-gcc -o address address.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -m none -i inputs -o logs ./address @@

fuzzing-sanitized: address.c
	export AFL_USE_ASAN=1afl-gcc -g $(CFLAGS) $(CFLAGS) -g -o address address.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -i inputs -o logs ./address @@

fuzzing-sanitized-6: address.c
	export AFL_CC="/usr/bin/gcc-6" AFL_USE_ASAN=1; afl-gcc -o address address.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -m none -i inputs -o logs ./address @@

sanitized: address.c
	gcc -g -fsanitize=address -o leak address.c

performance:
	echo performance | tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

powersave:
	echo powersave | tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

clean:
	rm -fr address logs
