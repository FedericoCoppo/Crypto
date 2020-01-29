CFLAGS=-Wall -Wextra -Wformat -Wformat-security -D_FORTIFY_SOURCE=2 -fstack-protector-all -pie -fPIE -Wl,-z,now -Wl,-z,relro

crash: crash.c
	gcc -o crash crash.c

fuzzing: crash.c
	afl-gcc -g $(CFLAGS) $(CFLAGS) -g -o crash crash.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -i inputs -o logs ./crash @@

fuzzing-6: crash.c
	export AFL_CC="/usr/bin/gcc-6"; afl-gcc $(CFLAGS) -g -o crash crash.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -i inputs -o logs ./crash @@

fuzzing-crash: crash.c
	afl-gcc -g $(CFLAGS) $(CFLAGS) -g -o crash crash.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -C -i bads -o logs ./crash @@

fuzzing-crash-6: crash.c
	export AFL_CC="/usr/bin/gcc-6"; afl-gcc $(CFLAGS) -g -o crash crash.c
	export AFL_SKIP_CPUFREQ=1; afl-fuzz -C -i bads -o logs ./crash @@

fuzzing-cmin: crash.c
	afl-gcc -g $(CFLAGS) $(CFLAGS) -g -o crash crash.c
	afl-cmin -i inputs -o min ./crash @@

fuzzing-cmin-6: crash.c
	export AFL_CC="/usr/bin/gcc-6"; afl-gcc $(CFLAGS) -g -o crash crash.c
	afl-cmin -i inputs -o min ./crash @@

fuzzing-parallel: crash.c
	afl-gcc -g $(CFLAGS) $(CFLAGS) -g -o crash crash.c
	export AFL_SKIP_CPUFREQ=1; nohup afl-fuzz -i inputs -o logs -M fuzzer0 ./crash @@ > fuzzer0.log &
	export AFL_SKIP_CPUFREQ=1; nohup afl-fuzz -i inputs -o logs -S fuzzer1 ./crash @@ > fuzzer1.log &
	export AFL_SKIP_CPUFREQ=1; nohup afl-fuzz -i inputs -o logs -S fuzzer2 ./crash @@ > fuzzer2.log &

fuzzing-parallel-6: crash.c
	export AFL_CC="/usr/bin/gcc-6"; afl-gcc $(CFLAGS) -g -o crash crash.c
	export AFL_SKIP_CPUFREQ=1; nohup afl-fuzz -i inputs -o logs -M fuzzer0 ./crash @@ > fuzzer0.log &
	export AFL_SKIP_CPUFREQ=1; nohup afl-fuzz -i inputs -o logs -S fuzzer1 ./crash @@ > fuzzer1.log &
	export AFL_SKIP_CPUFREQ=1; nohup afl-fuzz -i inputs -o logs -S fuzzer2 ./crash @@ > fuzzer2.log &

sanitized: crash.c
	gcc $(CFLAGS) -g -fsanitize=undefined -o crash crash.c

performance:
	echo performance | tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

powersave:
	echo powersave | tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

plots:
	afl-plot logs plots

clean:
	rm -fr crash logs min plots fuzzer0.log fuzzer1.log fuzzer2.log
