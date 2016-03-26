CC = -gcc
FLAGS = -pedantic -Wall

all: main_fork main_vfork

main_fork: main_fork.c lib.c
	$(CC) $(FLAGS) lib.c main_fork.c -o main_fork

main_vfork: main_vfork.c lib.c
	$(CC) $(FLAGS) lib.c main_vfork.c -o main_vfork

clean:
	rm main_fork
	rm main_vfork
