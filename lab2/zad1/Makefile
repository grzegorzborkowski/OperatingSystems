CC = gcc
FLAGS = -Wall -pedantic
DEPSMAIN = libs.h main.c
DEPSGENERATOR = libs.h generate.c

all: main generate

main: $(DEPSMAIN)
	$(CC) $(FLAGS) main.c -o main

generate: $(DEPSGENERATOR)
	$(CC) $(FLAGS) generate.c -o generate

tests: generate main
	./generate test_4_1000 4 1000
	cp test_4_1000 test_4_1000_copy
	./main test_4_1000 4 sys > test_4_1000_SYS_OUTPUT
	./main test_4_1000_copy 4 lib > test_4_1000_LIB_OUTPUT
	cat test_4_1000_SYS_OUTPUT >> wyniki.txt
	cat test_4_1000_LIB_OUTPUT >> wyniki.txt

	./generate test_4_10000 4 5000
	cp test_4_10000 test_4_10000_copy
	./main test_4_10000 4 sys > test_4_10000_SYS_OUTPUT
	./main test_4_10000_copy 4 lib > test_4_10000_LIB_OUTPUT
	cat test_4_10000_SYS_OUTPUT >> wyniki.txt
	cat test_4_10000_LIB_OUTPUT >> wyniki.txt

	./generate test_4_10000a 4 10000
	cp test_4_10000a test_4_10000a_copy
	./main test_4_10000a 4 sys > test_4_10000a_SYS_OUTPUT
	./main test_4_10000a_copy 4 lib > test_4_10000a_LIB_OUTPUT
	cat test_4_10000a_SYS_OUTPUT >> wyniki.txt
	cat test_4_10000a_LIB_OUTPUT >> wyniki.txt

	./generate test_512_100 512 2000
	cp test_512_100 test_512_100_copy
	./main test_512_100 512 sys > test_512_100_SYS_OUTPUT
	./main test_512_100_copy 512 lib > test_512_100_LIB_OUTPUT
	cat test_512_100_SYS_OUTPUT >> wyniki.txt
	cat test_512_100_LIB_OUTPUT >> wyniki.txt

	./generate test_512_256 512 4000
	cp test_512_256 test_512_256_copy
	./main test_512_256 512 sys > test_512_256_SYS_OUTPUT
	./main test_512_256_copy 512 lib > test_512_256_LIB_OUTPUT
	cat test_512_256_SYS_OUTPUT >> wyniki.txt
	cat test_512_256_LIB_OUTPUT >> wyniki.txt

	./generate test_4096_20 4096 2000
	cp test_4096_20 test_4096_20_copy
	./main test_4096_20 4096 sys > test_4096_20_SYS_OUTPUT
	./main test_4096_20_copy 4096 lib > test_4096_20_LIB_OUTPUT
	cat test_4096_20_SYS_OUTPUT >> wyniki.txt
	cat test_4096_20_LIB_OUTPUT >> wyniki.txt

	./generate test_4096_100 4096 5000
	cp test_4096_100 test_4096_100_copy
	./main test_4096_100 4096 sys > test_4096_100_SYS_OUTPUT
	./main test_4096_100_copy 4096 lib > test_4096_100_LIB_OUTPUT
	cat test_4096_100_SYS_OUTPUT >> wyniki.txt
	cat test_4096_100_LIB_OUTPUT >> wyniki.txt

	./generate test_8192_30 8192 2500
	cp test_8192_30 test_8192_30_copy
	./main test_8192_30 8192 sys > test_8192_30_SYS_OUTPUT
	./main test_8192_30_copy 8192 lib > test_8192_30_LIB_OUTPUT
	cat test_8192_30_SYS_OUTPUT >> wyniki.txt
	cat test_8192_30_LIB_OUTPUT >> wyniki.txt

	./generate test_8192_50 8192 5000
	cp test_8192_50 test_8192_50_copy
	./main test_8192_50 8192 sys > test_8192_50_SYS_OUTPUT
	./main test_8192_50_copy 8192 lib > test_8192_50_LIB_OUTPUT
	cat test_8192_50_SYS_OUTPUT >> wyniki.txt
	cat test_8192_50_LIB_OUTPUT >> wyniki.txt

	rm test_*

clean:
	rm main
	rm generate
	rm Makefile~
