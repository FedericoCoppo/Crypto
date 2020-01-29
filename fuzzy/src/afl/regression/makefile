CFLAGS=-Wall -Wextra -Wformat -Wformat-security -D_FORTIFY_SOURCE=2 -fstack-protector-all -pie -fPIE -Wl,-z,now -Wl,-z,relro

regression: regression.c
	gcc -o regression regression.c

fuzzing: regression.c
	afl-gcc -g $(CFLAGS) $(CFLAGS) -g -o regression regression.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -i inputs -o logs ./regression @@

fuzzing-6: regression.c
	export AFL_CC="/usr/bin/gcc-6"; afl-gcc -g -o regression regression.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -m none -i inputs -o logs ./regression @@

performance:
	echo performance | tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

powersave:
	echo powersave | tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

clean:
	rm -fr regression logs
