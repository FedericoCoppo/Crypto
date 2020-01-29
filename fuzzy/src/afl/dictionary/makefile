CFLAGS=-Wall -Wextra -Wformat -Wformat-security -D_FORTIFY_SOURCE=2 -fstack-protector-all -pie -fPIE -Wl,-z,now -Wl,-z,relro

crash: dictionary.c
	gcc -o dictionary dictionary.c

fuzzing: dictionary.c
	afl-gcc -g $(CFLAGS) $(CFLAGS) -g -o dictionary dictionary.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -i inputs -o logs ./dictionary @@

fuzzing-6: dictionary.c
	export AFL_CC="/usr/bin/gcc-6"; afl-gcc $(CFLAGS) -g -o dictionary dictionary.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -i inputs -o logs ./dictionary @@

fuzzing-dictionary: dictionary.c
	afl-gcc -g $(CFLAGS) $(CFLAGS) -g -o dictionary dictionary.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -x dictionary.dic -i inputs -o logs ./dictionary @@

fuzzing-dictionary-6: dictionary.c
	export AFL_CC="/usr/bin/gcc-6"; afl-gcc $(CFLAGS) -g -o dictionary dictionary.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -x dictionary.dic -i inputs -o logs ./dictionary @@

performance:
	echo performance | tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

powersave:
	echo powersave | tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

clean:
	rm -fr dictionary logs
