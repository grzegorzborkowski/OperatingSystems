CC = gcc
FLAGS = -g -Wall
STATICFLAGS = crs

all: unitTest static shared clean

static: benchmark/listBenchmark.c lib/liblist.c lib/liblist.h
	$(CC) -c lib/liblist.c -o lib_static.o
	ar $(STATICFLAGS) lib_static.a lib_static.o
	$(CC) -I. benchmark/listBenchmark.c -o listBenchmarkStatic -L. -l_static

shared: lib/liblist.c lib/liblist.h benchmark/listBenchmark.c
	$(CC) -fPIC -c lib/liblist.c -o lib_shared.o
	$(CC) -shared -fPIC -o lib_shared.so lib_shared.o
	$(CC) -o listBenchmarkShared benchmark/listBenchmark.c -L. -l_shared -Wl,-rpath=`pwd`

unitTest: tests/listUnitTests.c
	$(CC) $(FLAGS) -o listUnitTests tests/listUnitTests.c
	./listUnitTests

clean:
	rm -f *.o
	rm listUnitTests

clean_all:
	rm listBenchmarkStatic
	rm listBenchmarkShared
	rm -f *.o
	rm -f *.so
	rm -f *.a
