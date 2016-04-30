CC = gcc
FLAGS = -c -Wall
STATICFLAGS = cr

all: static shared clean

static: liblist.c liblist.h
	$(CC) $(FLAGS) liblist.c -o liblist.o
	ar $(STATICFLAGS) liblist.a liblist.o

shared:
	$(CC) -fPIC $(FLAGS) liblist.c -o liblist_shared.o
	$(CC) -shared liblist_shared.o -o liblist_shared.so

clean:
	rm -f *.o

