CFLAGS=-Wall -Wextra -Wformat -Wformat-security -D_FORTIFY_SOURCE=2 -fstack-protector-all -pie -fPIE -Wl,-z,now -Wl,-z,relro

crash: hang.c
	gcc -o hang hang.c

fuzzing: hang.c
	afl-gcc -g $(CFLAGS) $(CFLAGS) -g -o hang hang.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -t 1000 -i inputs -o logs ./hang @@

fuzzing-6: hang.c
	export AFL_CC="/usr/bin/gcc-6"; afl-gcc $(CFLAGS) -g -o hang hang.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -t 1000 -i inputs -o logs ./hang @@

performance:
	echo performance | tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

powersave:
	echo powersave | tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

clean:
	rm -fr hang logs
